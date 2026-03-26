# Interleaving Pipeline Checking

## Project-mode interleaving analysis

Project mode takes:
- a project root to collect all `*.c` files recursively
- a list of source files that define the interleaving functions

Example:

```sh
goto-cc \
  --interleaving-project-root check-src/t_isr_multifile \
  --interleaving-source-files check-src/t_isr_multifile/isr_define/isr.c \
  --interleaving-output check-src/t_isr_multifile/interleaving_harness.json \
  -o check-src/t_isr_multifile/t_isr_multifile.out
```

`--interleaving-source-files` is required. It is the source of truth for which
functions are treated as interleaving functions.

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

Project-mode JSON groups candidate insertion lines by file and excludes the
interleaving source files themselves from insertion candidates:

```json
[
  {
    "name": "isr1",
    "write_global_var": ["x", "flag"],
    "line_added_block_with_file": [
      { "file": "src/main.c", "line": [27, 36] },
      { "file": "src/task.c", "line": [31, 44] }
    ]
  }
]
```

## Project-mode injection with `aib`

`aib` now consumes the grouped-by-file JSON above and rewrites a full project
tree.

Usage:

```sh
aib \
  check-src/t_isr_multifile \
  check-src/t_isr_multifile/interleaving_harness.json \
  check-src/t_isr_multifile_injected
```

This command:
- reads `interleaving_harness.json`
- copies the whole `check-src/t_isr_multifile` tree to
  `check-src/t_isr_multifile_injected`
- injects `ileave_block` only into files listed in
  `line_added_block_with_file`

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

## End-to-end example

```sh
goto-cc \
  --interleaving-project-root check-src/t_isr_multifile \
  --interleaving-source-files check-src/t_isr_multifile/isr_define/isr.c \
  --interleaving-output check-src/t_isr_multifile/interleaving_harness.json \
  -o check-src/t_isr_multifile/t_isr_multifile.out

aib \
  check-src/t_isr_multifile \
  check-src/t_isr_multifile/interleaving_harness.json \
  check-src/t_isr_multifile_injected
```
