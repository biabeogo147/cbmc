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
./cmake-build-debug-docker/bin/aib project_root config.json output_root
# or
./build/bin/aib project_root config.json output_root
```

`aib` now expects the project-mode JSON emitted by `interleaving-analysis`, for
example:

```json
[
  {
    "name": "isr1",
    "write_global_var": ["enable_irq_1", "x"],
    "line_added_block_with_file": [
      { "file": "harness.c", "line": [10] },
      { "file": "task_define/task.c", "line": [5, 9] }
    ]
  }
]
```

The tool copies the entire project tree from `project_root` to `output_root`.
For files listed in `line_added_block_with_file`, it injects nondeterministic
interleaving calls immediately before the target lines:

```c
if (nondet_bool()) isr1(0);
if (nondet_bool()) isr2(0);
```

Example:

```bash
./build/bin/aib \
  check-src/t_isr_multifile \
  check-src/t_isr_multifile/interleaving_harness.json \
  out/t_isr_multifile_injected
```

`output_root` must not already exist.
