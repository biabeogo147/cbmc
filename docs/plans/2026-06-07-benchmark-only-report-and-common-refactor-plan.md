# Benchmark-only report and common refactor plan

## Goal

Refactor the benchmark pipeline so generated Markdown benchmark output has a single source of truth: `check-src/benchmark.md`.

`check-src/uncomparable.md` will be deleted because every measured case, including output mismatches and diagnostic cases, must be represented inside `benchmark.md`. `check-src/no-injection-failures.md` will also be merged into `benchmark.md` because the new rule is that common scripts must not write benchmark results to any Markdown file other than `benchmark.md`.

Static documentation may remain in `check-src/README.md`. Generated result Markdown must be only `check-src/benchmark.md`.

## Target end state

- `check-src/benchmark.md` contains:
  - full performance comparison for every measured case;
  - stock output and improved output;
  - correctness verdict when outputs differ;
  - reason/evidence for which side is correct;
  - no-injection failures and global-effect diagnostics;
  - timeout, memory-limit, unsupported-concurrency, and missing-result diagnostics.
- `check-src/uncomparable.md` is removed.
- `check-src/no-injection-failures.md` is removed after its useful content is folded into `benchmark.md`.
- `check-src/README.md` documents the pipeline deeply enough to explain every step and every script in `check-src/benchmarks/common`.
- `check-src/benchmarks/common` scripts write CSV, logs, or `benchmark.md`; they do not write any other Markdown report.

## Phase 1 - Report ownership cleanup

1. Delete `check-src/uncomparable.md`.
2. Delete `check-src/no-injection-failures.md` after moving its diagnostic content into `benchmark.md`.
3. Update all references in `check-src/README.md`, tests, scripts, and plan/docs so they point to `benchmark.md` only for generated Markdown results.
4. Rename user-facing wording from "uncomparable" to benchmark-native concepts:
   - `output_mismatch`;
   - `unsupported_concurrency`;
   - `stock_timeout`;
   - `improved_timeout`;
   - `stock_memory_limit`;
   - `improved_memory_limit`;
   - `no_injection_candidate`;
   - `missing_variant_result`;
   - `not_run_or_disabled`.

Acceptance checks:

- `rg "uncomparable.md|no-injection-failures.md" check-src docs` only finds historical plan text if any, not active pipeline docs or code.
- `check-src` has no generated Markdown report besides `benchmark.md`.

## Phase 2 - Refactor `report_benchmark.py`

1. Remove the dual-report model:
   - remove `--uncomparable-out`;
   - remove `report_kind`;
   - remove the separate uncomparable report builder path.
2. Make `benchmark.md` the complete report:
   - keep one row per benchmark case;
   - include performance even when outputs differ;
   - include correctness columns and evidence notes;
   - include diagnostic sections for cases that cannot produce a fair numeric comparison.
3. Fold the old `uncomparable-correctness` details into benchmark sections:
   - summary table by reason;
   - per-case diagnostic tables;
   - evidence links/log paths where available.
4. Fold no-injection findings into `benchmark.md`:
   - classify true no-injection cases separately from false no-injection failures;
   - explain the global-variable criterion used by the scan.

Acceptance checks:

- Running `python3 check-src/benchmarks/common/report_benchmark.py` writes only `check-src/benchmark.md`.
- The generated benchmark still includes speed/RAM deltas for output-mismatch cases.
- No code path in `report_benchmark.py` writes `uncomparable.md` or `no-injection-failures.md`.

## Phase 3 - Refactor audit helpers in `common`

1. Replace the old `uncomparable_audit.py` responsibility with a benchmark diagnostic inventory that is not tied to a Markdown file.
   - Preferred target: rename/refactor to `benchmark_inventory.py`.
   - It should read suite JSON and result CSV files directly.
   - It should write CSV diagnostics only, for example under `check-src/benchmarks/results/audit/`.
2. Update import users:
   - `run_evidence_case.py`;
   - `outcome_mismatch_audit.py`;
   - `report_benchmark.py`.
3. Refactor `global_effect_scan.py`:
   - remove `DEFAULT_REPORT`;
   - remove Markdown writer functions;
   - remove `--report-out`;
   - keep CSV output for `report_benchmark.py` to consume.
4. Refactor `candidate_scan.py`:
   - remove default Markdown output;
   - keep machine-readable CSV/JSON output only unless a caller explicitly asks for non-report text.
5. Verify helper scripts that already avoid Markdown generation:
   - `corpus_inventory.py`;
   - `normalize_case.py`;
   - `split_improved_case.py`;
   - `atomic_wrap_functions.py`.

Acceptance checks:

- `rg "write_.*markdown|Markdown|\.md|md-out|report-out" check-src/benchmarks/common` shows only README/help text that does not create generated Markdown, plus `report_benchmark.py` writing `benchmark.md`.
- Audit helpers produce CSV/log artifacts only.

## Phase 4 - Deep README pipeline documentation

Rewrite the README pipeline section around the real execution graph:

```text
suite JSON
  -> run_suite.sh or run_all.sh
  -> common/env.sh
  -> common/runner.py
  -> stock_cprover_async:
       copy source
       -> goto-cc
       -> cbmc with C_ASYNC_PROVER model
  -> improved_pipeline:
       copy source
       -> goto-cc interleaving manifest
       -> AIB inject
       -> goto-cc
       -> cbmc
  -> results/<suite>.csv
  -> audit CSV/log helpers
  -> report_benchmark.py
  -> benchmark.md
```

The README must explain every file currently in `check-src/benchmarks/common`:

- `env.sh`: resolves benchmark paths, CBMC binaries, Docker/container defaults, timeout and memory knobs.
- `runner.py`: validates suite JSON, copies sources, runs both variants, measures wall time/RSS, normalizes exit status, and writes result CSV.
- `report_benchmark.py`: joins raw CSV, suite metadata, correctness audits, and diagnostic CSVs into `benchmark.md`.
- `benchmark_inventory.py` or the retained audit inventory helper: builds diagnostic inventory from suites/results without reading Markdown.
- `outcome_mismatch_audit.py`: records correctness evidence for cases where stock and improved outputs differ.
- `global_effect_scan.py`: checks whether a no-injection case is valid by testing whether ISR-side global effects can affect `main`.
- `run_evidence_case.py`: runs a focused evidence case and stores logs/CSV evidence for audit review.
- `atomic_wrap_functions.py`: wraps ISR functions so benchmark modeling respects atomic ISR execution.
- `candidate_scan.py`: finds candidate source files/functions for ISR injection or case expansion.
- `corpus_inventory.py`: inventories upstream benchmark source material.
- `normalize_case.py`: normalizes imported cases into the local benchmark case layout.
- `split_improved_case.py`: separates improved-pipeline sources from stock C_ASYNC_PROVER modeling where required.

Acceptance checks:

- README no longer says the pipeline outputs `benchmark.md + uncomparable.md`.
- README describes both stock and improved modeling accurately.
- README clearly distinguishes generated artifacts:
  - Markdown: `check-src/benchmark.md` only;
  - CSV: raw benchmark and audit results;
  - logs: evidence/debug artifacts.

## Phase 5 - Tests and safeguards

1. Update `check-src/benchmarks/tests/selftest.ps1`:
   - expected Markdown files under `check-src`: `README.md` and `benchmark.md`;
   - reject `uncomparable.md`;
   - reject `no-injection-failures.md`;
   - reject any common script that writes another Markdown report.
2. Add or update tests for `report_benchmark.py` behavior:
   - output-mismatch cases still appear in benchmark performance tables;
   - diagnostic cases are included in benchmark;
   - only one Markdown output path is accepted.
3. Add a lightweight static check for README pipeline wording:
   - it must end in `benchmark.md`;
   - it must mention the common helper scripts.

Acceptance checks:

- `powershell -ExecutionPolicy Bypass -File check-src/benchmarks/tests/selftest.ps1` passes.
- Python compile check passes for `check-src/benchmarks/common/*.py`.

## Phase 6 - Regenerate benchmark and verify

Run the full Docker-backed pipeline after the refactor:

```sh
bash check-src/benchmarks/run_all.sh
python3 check-src/benchmarks/common/benchmark_inventory.py --inventory-only
python3 check-src/benchmarks/common/global_effect_scan.py
python3 check-src/benchmarks/common/outcome_mismatch_audit.py
python3 check-src/benchmarks/common/report_benchmark.py
```

If the audit inventory helper keeps the old filename during migration, use the new behavior but do not let it read or write `uncomparable.md`.

Final verification:

- `check-src/benchmark.md` is regenerated and contains all comparison plus diagnostic content.
- `check-src/uncomparable.md` does not exist.
- `check-src/no-injection-failures.md` does not exist.
- `rg "uncomparable.md|no-injection-failures.md" check-src` has no active references.
- `python3 -m py_compile check-src/benchmarks/common/*.py` passes in Docker.
- `git diff --check` passes.

## Risks

- Renaming `uncomparable_audit.py` may touch several scripts. If the rename creates too much churn, keep the filename temporarily but remove all Markdown dependency and update the public wording to "benchmark diagnostic inventory".
- Some historical docs in `docs/plans` may still mention old report files. Active user-facing docs should be cleaned; historical plan files can remain unless they confuse README links.
- Since benchmark output is generated, the refactor should avoid hand-editing large report tables except where needed to validate the new format.
