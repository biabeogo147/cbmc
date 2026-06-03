# Benchmark Pipeline

This document explains how a benchmark case moves from source code to raw CSV
rows. It also documents the current measurement limitations, because the
existing time and RAM numbers are useful for rough comparison but are not yet a
precise performance profiler.

## Inputs

A benchmark run starts from three inputs:

| Input | Location | Purpose |
| --- | --- | --- |
| Source corpus | `check-src/benchmark-sources/` or `check-src/simple-benchmarks/` | C source files, headers, harnesses, and per-variant modeling. |
| Suite manifest | `check-src/benchmarks/suites/*.json` | Declares cases, variants, source roots, compile file lists, ISR files, entry function, unwind, timeout, and memory limit. |
| Tool paths | Environment variables from `common/env.sh` | Select stock `cbmc`/`goto-cc`, improved `cbmc`/`goto-cc`, `aib`, `WORK`, `RESULTS_DIR`, and `PYTHON`. |

The active entry points are:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/<suite>.json
bash check-src/benchmarks/run_all.sh
python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/<suite>.json
```

`run_all.sh` scans `suites/*.json` and only runs suite files with top-level
`"enabled": true`.

## Manifest Resolution

For each enabled case, `runner.py` reads these fields:

| Field | Effect |
| --- | --- |
| `variants` | Controls which flows run, for example `stock_cprover_async` and `improved_pipeline`. |
| `root` | Default source root if a variant-specific root is not present. |
| `variant_roots` | Per-variant source root, normally `stock-cprover-async` versus `improved-pipeline`. |
| `sources` | Compile units passed to `goto-cc`. |
| `variant_sources` | Variant-specific compile units, used when improved source is split differently. |
| `include_dirs` | Include paths passed to `goto-cc` as `-I...`. |
| `variant_include_dirs` | Variant-specific include paths, used when improved keeps ISR headers or included source under `isr_define/`. |
| `isr_sources` | Files passed to improved `goto-cc --interleaving-source-files`. |
| `variant_isr_sources` | Variant-specific ISR files. |
| `isr_functions` | ISR/task entry names used to filter generated interleaving candidates. |
| `entry_function` | Function passed to `cbmc --function`. |
| `properties` | Optional property IDs passed to `cbmc --property`. |
| `unwind` | Value passed to `cbmc --unwind`. |
| `cbmc_args` | Extra CBMC arguments applied to all variants of one case. |
| `variant_cbmc_args` | Variant-specific CBMC arguments, for example OSEK `--osek-oil` paths. |
| `timeout_sec` | Per-command wall-clock timeout. |
| `memory_limit_mb` | Per-command RSS kill threshold as observed by the runner. |

Before running, `validate_manifest()` checks that enabled case roots, source
files, include dirs, and ISR metadata exist.

## Suite JSON Configuration

Create one JSON file per benchmark family under:

```text
check-src/benchmarks/suites/<suite-name>.json
```

Minimal runnable shape:

```json
{
  "suite_name": "my-suite",
  "description": "Short description of the benchmark family.",
  "enabled": true,
  "runs": 5,
  "warmups": 1,
  "variants": ["stock_cprover_async", "improved_pipeline"],
  "cases": [
    {
      "name": "my-case",
      "enabled": true,
      "root": "check-src/benchmark-sources/my-corpus/my-case/improved-pipeline",
      "variant_roots": {
        "stock_cprover_async": "check-src/benchmark-sources/my-corpus/my-case/stock-cprover-async",
        "improved_pipeline": "check-src/benchmark-sources/my-corpus/my-case/improved-pipeline"
      },
      "sources": ["main.c", "driver.c"],
      "variant_sources": {
        "improved_pipeline": ["main.c", "isr_define/isr.c"]
      },
      "include_dirs": [".", "include"],
      "variant_include_dirs": {
        "improved_pipeline": [".", "include", "isr_define"]
      },
      "isr_sources": ["main.c"],
      "variant_isr_sources": {
        "improved_pipeline": ["isr_define/isr.c"]
      },
      "isr_functions": ["timer_isr"],
      "entry_function": "main",
      "properties": [],
      "unwind": 3,
      "defines": [],
      "cbmc_args": [],
      "variant_cbmc_args": {},
      "expected_result": "same-result",
      "timeout_sec": 600,
      "memory_limit_mb": 8192
    }
  ]
}
```

### Top-Level Fields

| Field | Required | Example | How to choose it |
| --- | --- | --- | --- |
| `suite_name` | Yes | `"intabs-large"` | Stable suite id. It becomes `results/<suite_name>.csv` and the report heading. |
| `description` | Yes | `"Large IntAbs interrupt benchmark cases."` | Human-readable context for the suite. |
| `enabled` | Yes | `true` | `run_all.sh` only runs suites with `enabled: true`. |
| `runs` | No | `5` | Number of measured runs. Use `5` for benchmark data; use `1` for smoke checks. |
| `warmups` | No | `1` | Warmup runs written to CSV but ignored by the report. |
| `variants` | No | `["stock_cprover_async", "improved_pipeline"]` | Supported values are exactly these two variants. Keep this order for stock-vs-improved comparisons. |
| `cases` | Yes | `[...]` | List of benchmark cases. Each case produces rows in the suite CSV. |

### Case Fields

| Field | Required | Example | How to choose it |
| --- | --- | --- | --- |
| `name` | Yes | `"wdt-pci-3"` | Stable case id. It appears in console output, CSV, logs, and report headings. |
| `enabled` | No | `true` | Set `false` to keep a staged case documented but skipped. |
| `reason` | No | `"Needs harness normalization."` | Explain why a disabled case is not runnable yet. |
| `root` | Yes | `"check-src/benchmark-sources/.../improved-pipeline"` | Default source root. Usually point it to the improved root because `variant_roots` overrides stock. |
| `variant_roots` | Strongly recommended | See example | Use separate roots when stock uses C_ASYNC_PROVER modeling and improved uses the interleaving pipeline model. |
| `sources` | Yes | `["main.c", "driver.c"]` | Compile units passed to `goto-cc`, relative to the selected variant root. Include only files that should be compiled directly. |
| `variant_sources` | No | `{ "improved_pipeline": ["main.c", "isr_define/isr.c"] }` | Use when one variant needs a different compile list, for example split ISR files in the improved case. For include-based splits, keep only `main.c` here and put the included ISR file in `variant_isr_sources`. |
| `include_dirs` | Yes | `[".", "include"]` | Include directories relative to each selected variant root. |
| `variant_include_dirs` | No | `{ "improved_pipeline": [".", "isr_define"] }` | Use when include directories differ by variant. |
| `isr_sources` | Yes | `["main.c"]` | Default files containing ISR/task functions. Improved `goto-cc` receives variant-specific overrides through `--interleaving-source-files`. |
| `variant_isr_sources` | No | `{ "improved_pipeline": ["isr_define/isr.c"] }` | Use when ISR files differ by variant. Headline improved cases should use `isr_define/isr.c` or an explicitly documented deeper `isr_define/` path. |
| `isr_functions` | Yes | `["timer_isr", "uart_isr"]` | Function names used to filter improved interleaving candidates. These functions should be atomic in the benchmark source. |
| `entry_function` | Yes | `"main"` | Function passed to `cbmc --function`. |
| `properties` | No | `["main.assertion.1"]` | Optional property ids passed to `cbmc --property`. Empty means CBMC uses its default selected checks. |
| `unwind` | Yes | `3` | Bound passed to `cbmc --unwind`. Keep equal between stock and improved. |
| `defines` | No | `["CONFIG_X=1"]` | Macro definitions passed to `goto-cc` as `-D...`. |
| `cbmc_args` | No | `["--unwinding-assertions"]` | Extra CBMC arguments shared by stock and improved. |
| `variant_cbmc_args` | No | `{ "improved_pipeline": ["--os-api", "osek", "--osek-oil", "app.oil"] }` | Extra CBMC arguments for one variant. Relative path values for `--osek-oil` are resolved under the variant run root. |
| `expected_result` | No | `"same-result"` | Documentation only; report comparability is based on actual verification summaries. |
| `expected_summary` | No | `"pending"` | Documentation hint for later review. |
| `case_origin` | No | `"check-src/benchmark-sources/.../upstream/file.c"` | Traceability back to upstream corpus source. |
| `min_compile_loc` | No | `500` | Optional validation gate. Enabled case fails validation if a variant compiles fewer LOC than this. |
| `timeout_sec` | Yes | `600` | Per-command timeout for compile, manifest, inject, and verify phases. |
| `memory_limit_mb` | Yes | `8192` | Per-command RSS threshold sampled by the runner. |

### Source Layout Recommendation

For large comparable cases, use this layout:

```text
check-src/benchmark-sources/<corpus>/cases/<case>/
  stock-cprover-async/
    main.c
    ...
  improved-pipeline/
    main.c
    isr_define/
      isr.c
      isr.h
    ...
  CASE.md
```

The stock root should model interrupts in the style stock CBMC expects. The
improved root should keep ISR/task entry functions visible to the interleaving
pipeline and atomic where required by the benchmark model.

For monolithic upstream files with heavy `static` state, keep `main.c` as the
only direct compile source and include the extracted ISR source at the original
definition point:

```c
#include "isr_define/isr.c"
```

In that layout, `variant_sources.improved_pipeline` remains `["main.c"]`, while
`variant_isr_sources.improved_pipeline` is `["isr_define/isr.c"]`.

### Common Configuration Patterns

Use the same compile list for both variants:

```json
"sources": ["main.c", "driver.c"]
```

Use a split improved ISR source:

```json
"sources": ["main.c"],
"variant_sources": {
  "improved_pipeline": ["main.c", "isr.c"]
},
"isr_sources": ["main.c"],
"variant_isr_sources": {
  "improved_pipeline": ["isr.c"]
}
```

Run one case while iterating:

```bash
bash check-src/benchmarks/run_suite.sh \
  check-src/benchmarks/suites/my-suite.json \
  --case my-case
```

Run only one variant while debugging setup:

```bash
python3 check-src/benchmarks/common/runner.py \
  check-src/benchmarks/suites/my-suite.json \
  --case my-case \
  --variant improved_pipeline
```

Dry-run names and path validation:

```bash
bash check-src/benchmarks/run_suite.sh \
  check-src/benchmarks/suites/my-suite.json \
  --dry-run
```

## Work Directory Layout

Each measured or warmup run uses a fresh directory:

```text
$WORK/<suite>/<case>/<run_kind>-<run_id>/
```

Common generated paths:

| Path | Meaning |
| --- | --- |
| `stock_cprover_async/` | Copied stock source tree. |
| `improved_pipeline_original/` | Copied improved source tree before AIB injection. |
| `improved_pipeline/` | Improved source tree after AIB injection, or a copy of original when there are no candidates. |
| `*.out` | GOTO binary generated by `goto-cc`. |
| `*_interleaving_pipeline.json` | Raw interleaving manifest emitted by improved `goto-cc`. |
| `*_interleaving_pipeline.filtered.json` | Manifest filtered to configured `isr_functions` and usable source locations. |
| `interleaving_pipeline_injected.json` | Manifest emitted by `aib` for the injected tree. |
| `$WORK/logs/*.log` | Full stdout/stderr for each measured command. |

The `prepare` CSV row records source-copy metadata only. It does not measure
copy time or copy memory.

## Preferred Stock Flow

Variant: `stock_cprover_async`

This is the baseline used for stock CBMC when source code has already been
modeled with `__CPROVER_ASYNC_*` or C_ASYNC_PROVER-style concurrency.

Pipeline:

1. Copy the stock variant source root into:

   ```text
   $WORK/<suite>/<case>/<run_kind>-<run_id>/stock_cprover_async/
   ```

2. Write a `prepare` CSV row:

   ```text
   phase=prepare, run_kind=prepare, summary=source_root=<variant root>
   ```

3. Compile with stock `goto-cc`:

   ```bash
   $STOCK_GOTOCC -I<include_dirs> -D<defines> <sources> -o stock_cprover_async.out
   ```

   CSV row:

   ```text
   variant=stock_cprover_async, phase=compile
   ```

4. If compile exits `0`, verify with stock `cbmc`:

   ```bash
   $STOCK_CBMC stock_cprover_async.out --function <entry_function> --unwind <unwind> [--property ...]
   ```

   CSV row:

   ```text
   variant=stock_cprover_async, phase=verify
   ```

## Improved Pipeline Flow

Variant: `improved_pipeline`

This is the improved CBMC/AIB pipeline under evaluation.

Pipeline:

1. Copy the improved variant source root into:

   ```text
   $WORK/<suite>/<case>/<run_kind>-<run_id>/improved_pipeline_original/
   ```

2. Generate the interleaving manifest with improved `goto-cc`:

   ```bash
   $IMPROVED_GOTOCC \
     -I<include_dirs> -D<defines> <variant_sources> \
     --interleaving-project-root <improved_pipeline_original> \
     --interleaving-source-files <variant_isr_sources> \
     --interleaving-output improved_pipeline_interleaving_pipeline.json \
     -o improved_pipeline_manifest.out
   ```

   CSV row:

   ```text
   variant=improved_pipeline, phase=manifest
   ```

3. Filter the generated manifest:

   - Keep only entries whose `name` is listed in `isr_functions`.
   - Keep only entries with usable `line_added_block_with_file` records.
   - Write `improved_pipeline_interleaving_pipeline.filtered.json`.

   This filter step is not measured as its own CSV phase.

4. Inject ISR calls with `aib` when candidates exist:

   ```bash
   $AIB \
     <improved_pipeline_original> \
     improved_pipeline_interleaving_pipeline.filtered.json \
     <improved_pipeline> \
     <improved_pipeline>/interleaving_pipeline_injected.json
   ```

   CSV row:

   ```text
   variant=improved_pipeline, phase=inject
   ```

   If the filtered manifest has no candidates, the runner copies
   `improved_pipeline_original/` to `improved_pipeline/` and writes:

   ```text
   phase=inject, summary=NO_INJECTION_CANDIDATES, time_ms=0, max_rss_mb=0.0
   ```

5. Compile the injected improved source from the injected manifest:

   ```bash
   # Read project.translation_units from:
   # <improved_pipeline>/interleaving_pipeline_injected.json
   $IMPROVED_GOTOCC -I<variant_include_dirs> -D<defines> <injected_translation_units> -o improved_pipeline.out
   ```

   The runner resolves every injected translation unit under
   `<improved_pipeline>/`. It does not reuse the original suite `sources` list
   after `aib`, because `aib` may filter ignored files or rewrite the effective
   project manifest.

   CSV row:

   ```text
   variant=improved_pipeline, phase=compile
   ```

6. If compile exits `0`, verify with improved `cbmc`:

   ```bash
   $IMPROVED_CBMC improved_pipeline.out \
     --function <entry_function> \
     --no-standard-checks \
     --unwind <unwind> \
     [--property ...]
   ```

   CSV row:

   ```text
   variant=improved_pipeline, phase=verify
   ```

## CSV Output

Each suite overwrites one CSV file:

```text
check-src/benchmarks/results/<suite_name>.csv
```

Columns:

| Column | Meaning |
| --- | --- |
| `benchmark` | Suite name from `suite_name`. |
| `case` | Case name from manifest. |
| `variant` | Variant name, for example `stock_cprover_async` or `improved_pipeline`. |
| `phase` | `prepare`, `compile`, `verify`, `manifest`, or `inject`. |
| `run` | Run id within `run_kind`. |
| `run_kind` | `warmup`, `measure`, or `prepare`. |
| `exit_code` | Process exit code. CBMC commonly uses `10` for verification failure. |
| `time_ms` | Wall-clock elapsed time measured around one subprocess. |
| `max_rss_kb` | Maximum sampled `VmRSS` for the subprocess PID. |
| `max_rss_mb` | `max_rss_kb / 1024`. |
| `summary` | Short status extracted from the log, such as `VERIFICATION SUCCESSFUL`, `VERIFICATION FAILED`, `CBMC_UNSUPPORTED_CONCURRENCY`, `TIMEOUT_AFTER_*`, or `MEMORY_LIMIT_EXCEEDED_*`. |

Warmup rows are written to CSV but ignored by `report_benchmark.py`.

## Markdown Reports

After CSVs exist, generate:

```bash
python3 check-src/benchmarks/common/report_benchmark.py
```

The report generator reads:

1. `check-src/benchmarks/results/*.csv`
2. `check-src/benchmarks/suites/*.json`
3. `check-src/benchmark-sources/INVENTORY.md`

It writes two files:

| File | Content |
| --- | --- |
| `check-src/benchmark.md` | Cases whose stock and improved verification outcomes are comparable. |
| `check-src/uncomparable.md` | Cases that cannot be compared directly, such as unsupported concurrency, different verification outcomes, missing measured rows, or no injection candidates. |

Both reports use medians across measured runs. The generator sends a case to
`uncomparable.md` when:

- stock and improved verification outcomes differ
- stock CBMC reports unsupported concurrency
- a timeout or memory limit is hit
- the improved variant has `NO_INJECTION_CANDIDATES`
- one variant is missing measured rows

Comparable cases can still be non-headline. In that situation the case remains
in `benchmark.md`, but the report does not print headline speed/RAM deltas.

## Current Measurement Limitations

The current CSV `time_ms` and `max_rss_mb` are not precise profiler numbers.
They are best treated as coarse, phase-level observations.

Known limitations:

| Limitation | Why it matters |
| --- | --- |
| Parent PID RSS only | `runner.py` samples `/proc/<pid>/status` for the direct subprocess. If `cbmc`, `goto-cc`, or a wrapper starts child processes, child RSS is not included. |
| Polling every 20 ms | Short memory spikes between polls can be missed. |
| Wall-clock time only | `time_ms` includes scheduling noise and filesystem overhead inside the measured command, but does not report CPU time. |
| Prepare/copy time excluded | Source copy and directory setup are represented by `prepare` rows with `time_ms=0`. |
| Manifest filtering unmeasured | Filtering the JSON between manifest and AIB is not a separate measured phase. |
| `NO_INJECTION_CANDIDATES` has zero inject cost | In that path the runner still copies the source tree, but the CSV inject row records zero because no external command is measured. |
| Phase totals are not semantically identical | Stock usually has compile + verify. Improved has manifest + inject + compile + verify. The report adds them for full measured time, but the extra phases are part of the improved pipeline cost. |
| Docker/container noise | Results depend on host load, Docker Desktop/WSL behavior, filesystem mount performance, CPU frequency scaling, and available memory. |
| No solver-level metrics | CSV does not record SAT/SMT solver time, equation size, number of claims, or symbolic execution stats. |
| Memory kill threshold is approximate | The runner kills based on sampled RSS, so fast overshoots may be missed. |

For more accurate RAM measurement, the benchmark should be refactored to use a
process-tree-aware sampler or cgroup/container peak memory counters. For more
accurate time measurement, it should record wall-clock and CPU time separately,
pin or limit CPU resources, isolate the Docker container, and keep raw tool
statistics in machine-readable form.

## Recommended Future Measurement Refactor

The next measurement refactor should make these changes:

1. Run each measured command through a small native measurement wrapper.
2. Track the whole process tree, not only the direct subprocess PID.
3. Sample both RSS and high-water memory when available.
4. Record wall-clock time, user CPU time, and system CPU time.
5. Store command line, tool version, CPU count, memory limit, Docker image, and
   host/container metadata in each CSV or a sidecar JSON file.
6. Split currently hidden work into explicit phases, especially manifest
   filtering and no-candidate copy.
7. Keep raw CBMC/goto-cc/AIB logs and parse additional tool stats into separate
   columns instead of relying only on summary text.
