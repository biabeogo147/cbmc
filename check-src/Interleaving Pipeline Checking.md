# Interleaving Pipeline Checking

## Project-mode interleaving analysis

Project mode takes:
- a project root to relativize/filter reported paths
- a list of source files that define the interleaving functions

Example:

```sh
goto-cc \
  check-src/t_isr_multifile/harness.c \
  check-src/t_isr_multifile/harness_unity.c \
  check-src/t_isr_multifile/isr_define/isr.c \
  check-src/t_isr_multifile/task_define/task.c \
  --interleaving-project-root check-src/t_isr_multifile \
  --interleaving-source-files check-src/t_isr_multifile/isr_define/isr.c \
  --interleaving-output check-src/t_isr_multifile/interleaving_harness.json \
  -o check-src/t_isr_multifile/t_isr_multifile.out
```

`--interleaving-source-files` is required. It is the source of truth for which
functions are treated as interleaving functions.

`goto-cc` still compiles only the source files explicitly passed on the command
line. `--interleaving-project-root` does not recursively add `*.c` files to the
build; it is used only to scope report paths and candidate locations.

If an interleaving source file is not part of the current build inputs, the
build still follows normal `goto-cc` behavior. In that case the emitted
manifest may contain an empty `interleaving` array because analysis only
observes the already-built goto model.

If a goto binary already exists, the same analysis can run through
`goto-instrument`:

```sh
goto-instrument \
  --interleaving-project-root check-src/t_isr_multifile \
  --interleaving-source-files check-src/t_isr_multifile/isr_define/isr.c \
  --interleaving-output check-src/t_isr_multifile/interleaving_harness.json \
  check-src/t_isr_multifile/t_isr_multifile.out \
  check-src/t_isr_multifile/t_isr_multifile_optimized.out
```

Project-mode JSON is now a manifest object with:
- `project.project_root`
- `project.interleaving_source_files`
- `project.translation_units`
- `interleaving`

`project.translation_units` reflects the effective source files from the
current build command, not a recursive scan of `project_root`.

The `interleaving` section still groups candidate insertion lines by file and
excludes the interleaving source files themselves from insertion candidates:

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
      "write_global_var": ["x", "flag"],
      "line_added_block_with_file": [
        { "file": "src/main.c", "line": [27, 36] },
        { "file": "src/task.c", "line": [31, 44] }
      ]
    }
  ]
}
```

## Project-mode injection with `aib`

`aib` now consumes the manifest above and rewrites a full project tree.

Usage:

```sh
aib \
  check-src/t_isr_multifile \
  check-src/t_isr_multifile/interleaving_harness.json \
  check-src/t_isr_multifile_injected \
  check-src/t_isr_multifile_injected/interleaving_harness_injected.json
```

This command:
- reads `interleaving_harness.json`
- copies the whole `check-src/t_isr_multifile` tree to
  `check-src/t_isr_multifile_injected`
- injects `ileave_block` only into files listed in
  `interleaving[*].line_added_block_with_file`
- validates that `project.project_root` matches the CLI `project_root`
- if `check-src/t_isr_multifile/.aibignore` exists, excludes matched paths from
  copy, injection, and helper scans such as interleaving call prototype
  detection
- writes an effective manifest to
  `check-src/t_isr_multifile_injected/interleaving_harness_injected.json`
  so downstream compile/check steps can use metadata that matches the rewritten
  tree

If the input manifest itself was stored inside the original project tree, that
file is still copied as a normal project artifact. Downstream steps should use
the explicit `output_config.json` path passed to `aib`, not the copied original
manifest under its old relative path. `output_config.json` must be inside
`output_root`.

The injected block is a sequence of nondeterministic interleaving calls placed
immediately before each target line:

```c
if (nondet_bool()) isr1(0);
if (nondet_bool()) isr2(0);
```

For the `t_isr_multifile` sample, the expected rewritten files are:
- `check-src/t_isr_multifile_injected/harness.c`
- `check-src/t_isr_multifile_injected/task_define/task.c`

The ISR source file is copied unchanged:
- `check-src/t_isr_multifile_injected/isr_define/isr.c`

`output_root` must not already exist. `aib` fails early if that directory is
already present.

## Optional `.aibignore`

`aib` looks for an optional file at `<project_root>/.aibignore`.

Rules are matched relative to `project_root`.
Supported first-version syntax:
- blank lines
- comment lines starting with `#`
- exact file paths such as `harness.i`
- directory-prefix rules with a trailing slash such as `tmp_ignore/`

Ignored paths are:
- not copied to `output_root`
- not injected even if they appear in helper traversals
- not opened during helper scans such as prototype detection for choosing
  `isr()` or `isr(0)`

If the manifest references a file that is ignored by `.aibignore`, `aib` fails
fast instead of silently skipping it.

If `.aibignore` excludes an interleaving source file from
`project.interleaving_source_files`, `aib` also fails fast. Ignored
`translation_units` are filtered out of the effective manifest in `output_root`.

Example:

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

Unsupported in this version:
- negation rules such as `!task_define/task.c`
- wildcard rules such as `*.i`
- full gitignore-compatible semantics

## End-to-end example

```sh
goto-cc \
  check-src/t_isr_multifile/harness.c \
  check-src/t_isr_multifile/harness_unity.c \
  check-src/t_isr_multifile/isr_define/isr.c \
  check-src/t_isr_multifile/task_define/task.c \
  --interleaving-project-root check-src/t_isr_multifile \
  --interleaving-source-files check-src/t_isr_multifile/isr_define/isr.c \
  --interleaving-output check-src/t_isr_multifile/interleaving_harness.json \
  -o check-src/t_isr_multifile/t_isr_multifile.out

aib \
  check-src/t_isr_multifile \
  check-src/t_isr_multifile/interleaving_harness.json \
  check-src/t_isr_multifile_injected \
  check-src/t_isr_multifile_injected/interleaving_harness_injected.json
```

After that, you can reuse `project.translation_units` from the same
effective manifest you wrote into `output_root` when you manually compile the
injected project for CBMC, instead of calling `find *.c` again.

## Manual CBMC run from `translation_units`

Once `aib` has produced an injected project tree, do not compile the original
project sources again. Instead, read `project.translation_units` from the
effective manifest in the injected `output_root`, then resolve each relative
path under that same `output_root`.

For the sample output manifest
`check-src/t_isr_multifile_injected/interleaving_harness_injected.json`:

```json
"translation_units": [
  "harness.c",
  "isr_define/isr.c",
  "task_define/task.c"
]
```

and `output_root = check-src/t_isr_multifile_injected`, compile these files:
- `check-src/t_isr_multifile_injected/harness.c`
- `check-src/t_isr_multifile_injected/isr_define/isr.c`
- `check-src/t_isr_multifile_injected/task_define/task.c`

Example:

```sh
goto-cc \
  check-src/t_isr_multifile_injected/harness.c \
  check-src/t_isr_multifile_injected/isr_define/isr.c \
  check-src/t_isr_multifile_injected/task_define/task.c \
  -o check-src/t_isr_multifile_injected/t_isr_multifile_injected.out

cbmc \
  check-src/t_isr_multifile_injected/t_isr_multifile_injected.out \
  --function main
```

Notes:
- `translation_units` are stored relative to `project_root`
- after `aib`, use the manifest inside `output_root`, not the original input
  manifest; use the exact `output_config.json` path passed to `aib`
- for manual compilation, prepend `output_root` to each entry
- if your entry point is not `main`, replace `--function main` with the desired
  harness or entry function
- if the program has loops, add the unwind bound you want, for example
  `--unwind 10`
