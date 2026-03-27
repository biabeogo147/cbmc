# aib (interleaving block injector)

Build standalone (without full CBMC build):

```bash
g++ -std=c++17 -O2 -o aib src/lib-interleaving-block/aib.cpp
```

Build via CMake target (binary at `build/bin/aib`):

```bash
cmake -S . -B build
cmake --build build --target aib
```

If you use CLion with Docker toolchain, build in CLion's Docker build directory
(the workspace in this environment uses `cmake-build-debug-docker/`):

```bash
cmake -S . -B cmake-build-debug-docker
cmake --build cmake-build-debug-docker --target aib
```


If CLion reload does not show `aib` (usually due missing CBMC dependencies such as
`flex`/`bison` in the selected toolchain), use a dedicated CMake profile with:

```bash
cmake -S . -B cmake-build-debug-docker -DAIB_ONLY=ON
cmake --build cmake-build-debug-docker --target aib
```

This config builds only `aib` and skips the full CBMC tree.

Expected binary path in that setup:

```bash
./cmake-build-debug-docker/bin/aib
```

Usage:

```bash
./cmake-build-debug-docker/bin/aib project_root input_config.json output_root output_config.json
# or
./build/bin/aib project_root input_config.json output_root output_config.json
```

`aib` now expects the project-mode JSON emitted by `interleaving-analysis`, for
example:

```json
{
  "project": {
    "project_root": "check-src/t_isr_multifile",
    "interleaving_source_files": ["isr_define/isr.c"],
    "translation_units": [
      "harness.c",
      "harness_unity.c",
      "isr_define/isr.c",
      "task_define/task.c"
    ]
  },
  "interleaving": [
    {
      "name": "isr1",
      "write_global_var": ["enable_irq_1", "x"],
      "line_added_block_with_file": [
        { "file": "harness.c", "line": [10] },
        { "file": "task_define/task.c", "line": [5, 9] }
      ]
    }
  ]
}
```

In this manifest, `project.translation_units` should match the effective source
files from the `goto-cc` command that produced the JSON. `project_root` is used
for path relativization and candidate filtering; it does not imply recursive
source discovery during `goto-cc`.

If `project.interleaving_source_files` points to a source file that was not
part of the current build, `goto-cc` still preserves normal compile behavior.
In that case the emitted manifest can have an empty `interleaving` array while
still recording the requested source-file metadata and effective build inputs.

The tool copies the entire project tree from `project_root` to `output_root`.
For files listed in `line_added_block_with_file`, it injects nondeterministic
interleaving calls immediately before the target lines:

```c
if (nondet_bool()) isr1(0);
if (nondet_bool()) isr2(0);
```

For rewritten C files, `aib` also inserts a small forward-declaration block near
the top of the file so the injected calls do not rely on implicit declarations.
That block currently includes:
- `extern _Bool nondet_bool(void);`
- one declaration per injected interleaving function, such as
  `void *isr1(void *arg);`

Example:

```bash
./build/bin/aib \
  check-src/t_isr_multifile \
  check-src/t_isr_multifile/interleaving_harness.json \
  out/t_isr_multifile_injected \
  out/t_isr_multifile_injected/interleaving_harness_injected.json
```

`aib` validates that the CLI `project_root` matches `project.project_root` in
the input config.

The input manifest is not modified in place. After a successful run, `aib`
writes an effective manifest to the explicit `output_config.json` path you
provided. That path must stay inside `output_root`. Downstream compile/check
steps should use that output manifest, because it reflects the rewritten tree
after `.aibignore` filtering.

`.aibignore` is optional. If present, it must live at
`<project_root>/.aibignore`. Matched paths are:
- not copied to `output_root`
- not eligible for injection
- not used during helper scans such as prototype detection for deciding between
  `isr()` and `isr(0)`

Rules are matched against relative paths under `project_root`.
Supported first-version syntax:
- blank lines
- comments starting with `#`
- exact file paths such as `harness.i`
- directory prefixes with a trailing slash such as `tmp_ignore/`

Unsupported in this version:
- negation rules such as `!foo.c`
- wildcard matching such as `*.i`
- gitignore-compatible semantics

If the manifest references a file that is ignored by `.aibignore`, `aib` fails
fast instead of silently skipping it.

If the manifest references an interleaving source file that is ignored by
`.aibignore`, `aib` also fails fast. Ignored `translation_units` are filtered
out of the effective manifest written to `output_root`.

Example `.aibignore`:

```text
# generated or derived source artifacts
harness.i
harness_added_ileave.i
harness_unity.c

# environment-specific project scaffolding
Dockerfile
docker-compose.yml
t_isr_multifile.out

# the effective manifest will be rewritten into output_root
interleaving_harness.json
```

`output_root` must not already exist.
