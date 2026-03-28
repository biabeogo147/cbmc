# interleaving-analysis

`interleaving-analysis` is the analysis-side half of the current interleaving
pipeline.

Its job is to inspect an already-built `goto_model`, identify which functions
should be treated as interleaving functions, compute which global variables
those functions may write, and then report source lines in the rest of the
project that are plausible insertion points for nondeterministic interleaving
calls.

This module does not rewrite source files. It only emits metadata. The rewrite
step is handled later by `aib` in `src/lib-interleaving-block`.

## Where this module fits in the pipeline

Today the pipeline is intentionally split into two stages:

1. `interleaving-analysis` runs inside `goto-cc` or `goto-instrument`
2. the analysis emits a JSON manifest
3. `aib` consumes that manifest and rewrites a copied source tree
4. CBMC or later compile/check steps operate on the rewritten tree

In other words:

```text
source files
  -> goto-cc / goto-instrument
  -> interleaving-analysis
  -> interleaving manifest JSON
  -> aib
  -> rewritten project tree
  -> goto-cc / cbmc on rewritten sources
```

This split is important for maintenance:

- `interleaving-analysis` is responsible for analysis only
- `aib` is responsible for source-to-source transformation only
- the manifest is the contract between the two halves

## What the module is responsible for

The current implementation is responsible for:

- resolving target interleaving functions from
  `project.interleaving_source_files`
- collecting the set of global variables written by each target function
- scanning the rest of the goto model for instructions that read or write
  those globals
- grouping matching source lines by file
- writing a project-mode JSON manifest

The current implementation is not responsible for:

- rewriting any C source files
- compiling additional translation units that were not part of the current
  build
- recursively discovering all files under `project_root`
- proving that a reported line is the optimal or only insertion point
- modelling scheduler behavior or exploring concrete interleavings by itself

## Build integration

This module is built as a CBMC library target:

```cmake
add_library(interleaving-analysis-lib ...)
```

It is not a standalone executable. It is linked into CBMC components such as:

- `goto-cc`
- `goto-instrument`

Current dependencies from `CMakeLists.txt` are:

- `goto-programs`
- `pointer-analysis`
- `analyses`
- `langapi`
- `util`

## Main entry points

The main public API lives in `interleaving_analysis.h`.

### `interleaving_configt`

This struct controls the analysis run:

- `interleaving_source_files`
  source files whose functions are treated as interleaving functions
- `translation_units`
  effective build inputs to record in the manifest
- `project_root_path`
  used for path relativization and candidate filtering
- `json_output_path`
  output manifest path, defaulting to `interleaving_manifest.json`

### `analyze_interleavings(...)`

Runs the analysis and returns an in-memory `interleaving_resultt`.

### `write_interleaving_report(...)`

Serializes an `interleaving_resultt` into the JSON manifest expected by `aib`.

### `run_interleaving_analysis(...)`

Convenience wrapper that runs the analysis and writes the report.

## Output manifest contract

The output format is the project-mode manifest shared with `aib`.

Example:

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

The fields have the following meaning:

- `project.project_root`
  the configured root used when relativizing paths in the report
- `project.interleaving_source_files`
  the requested interleaving source files, written relative to `project_root`
  when possible
- `project.translation_units`
  the effective build inputs associated with the current goto model
- `interleaving[*].name`
  a function identifier from the goto model
- `interleaving[*].write_global_var`
  global symbols that the target function may write
- `interleaving[*].line_added_block_with_file`
  source locations where `aib` may inject nondeterministic calls to that
  function

The manifest is the compatibility boundary with `aib`. If this schema changes,
`aib` must be updated in lockstep.

## High-level algorithm

The current implementation in `interleaving_analysis.cpp` follows this flow.

### 1. Normalize project metadata

The analysis normalizes configured paths to absolute, lexically-normalized
paths. This is used to:

- compare source files robustly
- keep file matching consistent across the build
- later convert reported paths back to paths relative to `project_root`

If `translation_units` were not provided in the config, the analysis derives
them from the current goto model by collecting body-available functions whose
source file:

- exists
- ends in `.c`
- is under `project_root` if a root was provided

### 2. Resolve target interleaving functions

`resolve_target_function_ids(...)` scans all body-available functions in the
goto model and keeps the ones whose defining source file is listed in
`interleaving_source_files`.

Important properties:

- `--interleaving-source-files` is the source of truth for which functions are
  treated as interleaving functions
- only functions already present in the current goto model can be selected
- if a listed source file was not part of the build, no function from it can be
  analyzed
- the resulting function IDs are sorted for deterministic output

This means the analysis never expands the build. It only inspects what is
already in the goto model.

### 3. Compute written globals for each target function

`build_function_write_map(...)` iterates over every instruction in each target
interleaving function and constructs an `rw_set_loct` for that instruction.

For each write entry in the per-instruction RW set, the analysis keeps only
entries that satisfy `is_global_written_symbol(...)`.

A symbol is currently treated as a relevant global write when all of the
following hold:

- the symbol lookup succeeds
- it has static lifetime
- it is not local to a function
- it is not a type symbol
- it is not auxiliary
- it is not code

The resulting data structure is:

- internal map:
  `function_id -> set of global variable identifiers written by that function`
- manifest data:
  `interleaving[*].write_global_var`

### 4. Scan the rest of the program for conflicts

`record_candidate_lines(...)` then scans all functions in the goto model again,
but skips:

- functions without bodies
- functions whose name starts with `__CPROVER`
- the target interleaving functions themselves
- any function whose source file is itself listed in
  `interleaving_source_files`

For each instruction in the remaining functions, the analysis computes another
`rw_set_loct` and checks whether that instruction conflicts with the set of
globals written by each interleaving function.

The conflict rule is intentionally simple:

- if the instruction reads a global written by the interleaving function,
  record the line
- otherwise, if the instruction writes a global written by the interleaving
  function, record the line

This is therefore a write-centric conflict test:

- interleaving-function writes versus code reads
- interleaving-function writes versus code writes

The current implementation does not separately track globals read-only by the
interleaving function for this candidate search.

### 5. Record source lines

If a conflict is found, the analysis reads:

- `instruction->source_location().get_file()`
- `instruction->source_location().get_line()`

and records the line under:

- the current interleaving function
- the relative file path used in the report

Candidate locations are stored in sets, so duplicate hits on the same file and
line collapse naturally.

When `project_root_path` is set, candidate locations are currently recorded only
for source files that:

- end in `.c`
- are equal to or underneath `project_root_path`

When no project root is set, the file-extension and root filter are not
applied.

### 6. Write the JSON report

`write_interleaving_report(...)` writes the final JSON manually using an
`std::ofstream`.

Important maintenance detail:

- JSON emission is hand-written, not delegated to a JSON library
- any schema change must update both the writer here and the reader in `aib`

## The RW-set layer

`rw_set.h` and `rw_set.cpp` provide the read/write footprint analysis used by
this module and also reused by other parts of CBMC.

For interleaving analysis, the key class is `rw_set_loct`, which computes the
read and write set for one goto instruction at a time.

### What `rw_set_loct` stores

Each RW-set entry includes:

- `symbol_expr`
- `object`
- `guard`

The main containers are:

- `r_entries`
- `w_entries`

These are keyed by object identifier, so a given object appears at most once in
each set per instruction.

### Which instructions are handled

At the top level, `_rw_set_loct::compute()` currently handles:

- assignments
- `goto`
- `assume`
- `assert`
- function calls

For function calls it:

- reads the callee expression
- reads all call arguments
- writes the call LHS if there is one

Other instruction kinds are currently ignored by this instruction-level entry
point.

### Which expression shapes are handled

`read_write_rec(...)` recursively handles:

- `symbol`
- `member`
- `index`
- `dereference`
- `typecast`
- `address_of`
- `if`
- generic recursive descent over remaining operands

Notable details:

- member access appends `.field` suffixes
- array indexing appends `[]` suffixes and also reads the index expression
- dereferences trigger CBMC dereference/value-set processing before continuing
- `if` expressions track path conditions through guard conjunctions

### Pointer and alias handling

This layer relies on CBMC pointer analysis infrastructure:

- `value_set_analysist`
- `dereference(...)`

So the RW sets are conservative approximations based on the available value-set
information in the current goto model.

There is also conditional support for `LOCAL_MAY` alias handling in the code,
but that path depends on build-time configuration.

### Why `rw_set` matters here

The correctness of candidate discovery depends directly on what `rw_set_loct`
classifies as reads and writes.

If future maintainers need to change interleaving candidate precision, the
first place to inspect is usually:

- whether the right instruction kinds are covered
- how dereferences are resolved
- whether the global-write filter is too strict or too loose
- whether the conflict rule should include more than target-function writes

## Path handling and report scoping

Path logic is a core part of this module because the emitted manifest must be
stable enough for `aib` and later project-relative tooling to consume.

Current behavior:

- configured paths are normalized to absolute normalized paths for matching
- report paths are relativized against `project_root` when possible
- if `project_root` is empty, report paths remain normalized paths

`project_root` is used for:

- path relativization in the manifest
- filtering candidate source files
- filtering derived translation units when they are collected from the goto
  model

`project_root` is not used for:

- recursive build discovery
- implicitly adding more source files to `goto-cc`
- changing which functions exist in the goto model

## Integration points

### `goto-cc`

`goto-cc` invokes `run_interleaving_analysis(...)` when
`--interleaving-source-files` is present.

In this path:

- `translation_units` are explicitly set from the effective build inputs passed
  to `goto-cc`
- the analysis runs after the goto model has been assembled
- the normal object/goto output is still produced

### `goto-instrument`

`goto-instrument` can run the same analysis on an existing goto binary.

In this path:

- the same config flags are available
- `translation_units` may need to be re-derived from the goto model if they are
  not explicitly supplied

This makes `goto-instrument` a useful re-analysis path after a goto binary
already exists.

## Important invariants and assumptions

The current implementation assumes:

- `--interleaving-source-files` is provided whenever interleaving analysis is
  requested
- only functions present in the current goto model can be analyzed
- candidate insertion lines should not come from the interleaving source files
  themselves
- global writes are the relevant signal for interleaving conflict discovery
- source locations on goto instructions are meaningful enough to map back to
  project files and line numbers

These assumptions are reflected both in code and in the manifest consumed by
`aib`.

## Known limitations

The current implementation has some deliberate simplifications that future
maintainers should keep in mind:

- it is source-file driven, not attribute driven
- it only discovers target functions that already exist in the goto model
- it focuses on globals written by target functions, not all shared-memory
  behavior
- candidate discovery is per instruction and source-location driven, so missing
  or coarse source locations reduce precision
- candidate recording under `project_root` is currently restricted to `.c`
  files
- JSON parsing and writing across the pipeline are hand-written
- there is no explicit schema version field in the manifest

None of these are necessarily wrong, but they are important constraints for
maintenance and future extensions.

## Relationship with `aib`

`interleaving-analysis` and `aib` are designed to be changed together when the
manifest contract changes.

Current division of responsibility:

- `interleaving-analysis` decides where interleaving calls may be inserted
- `aib` decides how those calls are materialized in copied source files

If you change any of the following here, inspect `src/lib-interleaving-block`
as well:

- manifest field names
- path semantics
- how files are relativized
- whether empty `interleaving` arrays are valid
- what `translation_units` means

## CLI usage

There is no standalone `interleaving-analysis` binary. Use it through
`goto-cc` or `goto-instrument`.

### `goto-cc`

Example:

```bash
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

Meaning of the flags:

- `--interleaving-project-root`
  project root used for path scoping and path relativization
- `--interleaving-source-files`
  comma-separated source files defining the interleaving functions
- `--interleaving-output`
  output JSON manifest path

Important behavior:

- `--interleaving-source-files` is required if interleaving analysis is used
- the listed files do not add themselves to the build automatically
- `goto-cc` still only compiles the source files explicitly named on the CLI
- if an interleaving source file was not part of the build, the manifest may
  contain an empty `interleaving` array

### `goto-instrument`

If a goto binary already exists, the same analysis can be run with
`goto-instrument`:

```bash
goto-instrument \
  --interleaving-project-root check-src/t_isr_multifile \
  --interleaving-source-files check-src/t_isr_multifile/isr_define/isr.c \
  --interleaving-output check-src/t_isr_multifile/interleaving_harness.json \
  check-src/t_isr_multifile/t_isr_multifile.out \
  check-src/t_isr_multifile/t_isr_multifile_optimized.out
```

The help text currently describes these flags as:

- `--interleaving-project-root <dir>`
  project root for interleaving report path scoping
- `--interleaving-source-files <f1.c,f2.c>`
  source files defining interleaving functions
- `--interleaving-output <file>`
  write interleaving metadata to the given file

### Typical end-to-end flow

The expected project-mode flow is:

1. run `goto-cc` or `goto-instrument` with the interleaving flags
2. inspect the emitted manifest
3. pass that manifest to `aib`
4. compile the rewritten project tree described by the `aib` output manifest
5. run CBMC on the rewritten goto binary

## Maintenance checklist

When modifying this module, check all of the following:

- does the manifest schema still match what `aib` expects
- are path normalization and path relativization still consistent
- do candidate locations still exclude interleaving source files by design
- is the global-write filter still the intended one
- do `goto-cc` and `goto-instrument` still pass the expected config
- do examples and docs still reflect the exact CLI behavior

Keeping this README accurate is especially important because this module has no
standalone CLI of its own, so most users learn its behavior indirectly through
the surrounding pipeline.
