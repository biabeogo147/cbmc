# Uncomparable Correctness Audit Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Audit every correctness-sensitive case in `check-src/uncomparable.md`, decide whether stock CBMC or the improved interleaving pipeline gives the correct answer, and verify every `NO_INJECTION_CANDIDATES` result against the ISR/global-variable rule.

**Architecture:** Build a small evidence pipeline around the existing benchmark runner instead of judging from summary labels alone. The audit will parse report/CSV/manifest data, rerun selected cases in Docker with trace-friendly settings, perform a conservative ISR-to-main global-impact scan, then write a verdict table that drives source fixes, manifest fixes, or report reclassification.

**Tech Stack:** Python benchmark helpers, suite JSON manifests, CBMC/goto-cc/aib, Docker benchmark image, Markdown reports, CSV evidence logs.

---

## Current Audit Scope

The current `check-src/uncomparable.md` has these correctness-sensitive groups:

| Group | Report rows | Primary question |
| --- | ---: | --- |
| `Verification Failed vs Successful` | 7 | Is stock finding a real bug, or is improved correctly proving the normalized model? |
| `Verification Successful vs Failed` | 4 | Is improved injecting a real ISR behavior, or creating a false counterexample? |
| `Verification Failed vs Exit 6` | 9 | Is improved exiting because the model/pipeline is invalid, or because the stock failure is outside the improved model? |
| `No Injection Candidates` | 7 | Is it true that no ISR writes a global variable reachable from `main`? |

Important: the `Failed vs Exit 6` group contains duplicate diagnostic rows for the same four Logger2 logical cases under both `icbmc-timeout-30m` and `icbmc-timeout-30m-logger-stable`. The audit must deduplicate by source roots before deciding coverage.

The `No Injection Candidates` audit must also inspect mixed-reason cases where improved injection reports no candidates but the report category is dominated by another reason, especially the blink timeout/high-memory diagnostic cases.

## Correctness Standard

Do not decide correctness from case names alone, even when a case includes `bug`.

A variant is considered correct only when the audit can show one of these:

| Verdict | Required evidence |
| --- | --- |
| `stock_correct` | Stock counterexample trace reaches the checked assertion through a feasible stock C_ASYNC_PROVER ISR model, and the improved source should model the same ISR/global behavior but misses it or exits before verification. |
| `improved_correct` | Improved trace/proof matches the normalized source contract, and stock failure comes from over-approximate or incompatible C_ASYNC_PROVER modeling. |
| `both_models_different` | Stock and improved sources are not semantically equivalent; neither result can be used for speed/RAM comparison until source normalization is fixed. |
| `both_need_fix` | One or both variants fail to compile/verify for modeling or tooling reasons that prevent a correctness decision. |
| `no_injection_true` | Every ISR has an empty intersection between globals it may write and globals reachable from `main`. |
| `no_injection_false` | At least one ISR writes a global reachable from `main`, so the improved pipeline should have injection candidates. |

For `NO_INJECTION_CANDIDATES`, the rule is strict:

```text
NO_INJECTION_CANDIDATES is valid iff:
  ISR-written globals intersect main-reachable globals == empty set
```

If this intersection is non-empty, the case is not a valid "no injection" case; it is a pipeline/source-normalization bug.

## Files To Create Or Modify

| File | Change |
| --- | --- |
| `check-src/benchmarks/common/uncomparable_audit.py` | Create helper that reads CSV, suite JSON, and `uncomparable.md` categories, then emits a normalized audit inventory. |
| `check-src/benchmarks/common/global_effect_scan.py` | Create conservative source scanner for ISR-written globals and main-reachable globals. |
| `check-src/benchmarks/common/run_evidence_case.py` | Create optional wrapper around `runner.py --case` for trace/evidence reruns without changing normal benchmark CSVs. |
| `check-src/benchmarks/tests/selftest.ps1` | Add structural tests for the audit inventory and scanner fixtures. |
| `check-src/uncomparable-correctness.md` | Create final human-readable verdict report. |
| `check-src/uncomparable.md` | Update only after verdicts are known, adding links/status where useful. |
| `check-src/benchmark.md` | Update only after rerun confirms a previously uncomparable case is now comparable. |

Do not overwrite benchmark headline CSVs during audit reruns. Use a separate evidence output directory, for example:

```text
check-src/benchmarks/results/audit/
check-src/benchmarks/work/audit/
```

## Phase 0: Baseline Inventory And Deduplication

**Scope:** No source changes. Build a reliable list of logical cases to audit.

- [x] Parse `check-src/uncomparable.md` and extract case rows from these groups: `Verification Failed vs Successful`, `Verification Successful vs Failed`, `Verification Failed vs Exit 6`, and all rows whose improved phase summary contains `NO_INJECTION_CANDIDATES`.
- [x] Join every extracted row with its suite manifest entry from `check-src/benchmarks/suites/*.json`.
- [x] Deduplicate diagnostic repeats by `(stock variant root, improved variant root, entry function, properties, unwind)`.
- [x] Emit `check-src/benchmarks/results/audit/uncomparable-inventory.csv` with:

```text
category,suite,case,logical_case_id,stock_root,improved_root,entry_function,properties,unwind,stock_summary,improved_summary,needs_no_injection_audit
```

- [x] Add a selftest fixture proving duplicate Logger2 diagnostic rows collapse to one logical audit item.
- [x] Run:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/uncomparable_audit.py --inventory-only"
```

**Exit criteria:**

- The audit scope is explicit.
- Duplicate diagnostic rows are not counted as independent correctness bugs.
- Every audit item points to concrete stock/improved source roots.

## Phase 1: Evidence Rerun Tooling

**Scope:** Add repeatable evidence collection without changing normal benchmark behavior.

- [x] Add `run_evidence_case.py` that accepts:

```text
--suite check-src/benchmarks/suites/<suite>.json
--case <case-name>
--variant stock_cprover_async|improved_pipeline|both
--trace
--results-dir check-src/benchmarks/results/audit
--work check-src/benchmarks/work/audit
```

- [x] The wrapper should call `runner.py --case <case>` with a copied temporary manifest that adds trace-friendly CBMC args, such as:

```text
--trace
--stop-on-fail
--json-ui
```

Use `--json-ui` only when supported by the local CBMC version; otherwise keep plain logs and record the fallback.

- [x] Store all logs under:

```text
check-src/benchmarks/work/audit/logs/
```

- [x] Add evidence metadata rows:

```text
logical_case_id,suite,case,variant,phase,exit_code,summary,log_path,trace_path,verdict_hint
```

- [x] Verify the wrapper on one small case from `local-smoke` and one IntAbs case.

**Exit criteria:**

- Any uncomparable case can be rerun by suite/case in Docker.
- Counterexample/proof logs are preserved separately from headline benchmark CSVs.

## Phase 2: No Injection Candidates Audit

**Scope:** Decide whether each `NO_INJECTION_CANDIDATES` result is true or false.

Primary cases from the report:

| Suite | Cases |
| --- | --- |
| `icbmc-large` | `blink`, `blink-bug`, `blink-bug-conc`, `blink-conc`, `rc-core`, `rc-core-bug` |
| `intabs-large` | `rcmain` |

Also inspect mixed-reason cases where improved injection reports no candidates:

| Suite | Cases |
| --- | --- |
| `icbmc-timeout-30m`, `icbmc-timeout-30m-blink-highmem` | `blink-seq`, `blink-bug-seq` |

- [x] Implement `global_effect_scan.py`.
- [x] For every case, load `variant_isr_sources.improved_pipeline`, `isr_functions`, `sources`, and `entry_function`.
- [x] Identify file-scope globals conservatively:
  - include scalar, array, struct, enum-backed, and pointer globals;
  - ignore function declarations, typedefs, and local variables;
  - mark uncertain declarations as `unknown_global`.
- [x] Compute `isr_written_globals` from assignments, increments/decrements, compound assignments, address-taken writes, and obvious helper calls from each ISR.
- [x] Compute `main_reachable_globals` from `main`/entry function and direct callees in the same translation unit. If the call graph is incomplete, mark the result `needs_manual_review`.
- [x] Compute:

```text
candidate_globals = isr_written_globals ∩ main_reachable_globals
```

- [x] Classify:
  - empty intersection and no unknown writes: `no_injection_true`;
  - non-empty intersection: `no_injection_false`;
  - unknown pointer/write/call behavior: `needs_manual_review`.
- [x] For every `no_injection_false`, record the exact ISR function, global name, and main-reachable use site.
- [x] Rerun the improved pipeline for false/unknown cases and inspect the emitted interleaving manifest before filtering:

```text
*_interleaving_pipeline.json
*_interleaving_pipeline.filtered.json
```

**Exit criteria:**

- Every `NO_INJECTION_CANDIDATES` case has a verdict.
- False cases become source/pipeline fix tasks, not benchmark results.
- True cases can be moved to a clearer report category such as `No ISR/Main Global Intersection`.

## Phase 3: Local And OSEK Outcome Mismatches

**Scope:** Audit the smallest mismatches first because their traces are easiest to inspect.

Cases:

| Group | Suite | Cases |
| --- | --- | --- |
| `Verification Successful vs Failed` | `local-smoke` | `t-isr-multifile` |
| `Verification Successful vs Failed` | `osek-local` | `osek-event-interleaving`, `osek-priority-interleaving` |

- [x] Rerun stock and improved variants with evidence tracing.
- [x] Inspect whether the improved injected ISR call corresponds to an ISR that can run in the original benchmark model.
- [x] Inspect the failing property line and trace variable values.
- [x] Compare against the simple benchmark documentation under `check-src/simple-benchmarks/**/how-to-check-with-cbmc.md` and `Interleaving Pipeline Checking.md`.
- [x] Decide:
  - improved correct and stock model too weak;
  - stock correct and improved over-injects;
  - source variants are not equivalent and need normalization.
- [x] If the source variants are not equivalent, fix the source layout before benchmarking again.

**Exit criteria:**

- Local/OSEK mismatches have a clear verdict and action.
- These cases either become comparable after source fix or remain explicitly documented as intentional modeling differences.

## Phase 4: IntAbs Verification Outcome Mismatches

**Scope:** Audit IntAbs watchdog cases with `Failed vs Successful`, `Successful vs Failed`, and `Failed vs Exit 6`.

Cases:

| Group | Suite | Cases |
| --- | --- | --- |
| `Verification Failed vs Successful` | `intabs-large` | `i8xx-tco-1`, `i8xx-tco-2`, `i8xx-tco-3`, `i8xx-tco-src-2`, `i8xx-tco-src-3`, `wdt-pci-1`, `wdt-pci-src-1` |
| `Verification Successful vs Failed` | `intabs-large` | `sc520wdt-2` |
| `Verification Failed vs Exit 6` | `intabs-large` | `wdt-pci-2` |

- [x] Rerun each case with stock/improved evidence logs.
- [x] Read the original upstream IntAbs source next to the normalized stock/improved roots.
- [x] Identify the checked assertion/property and its intended bug status from source comments, assertion structure, and variant naming.
- [x] Compare ISR definitions:
  - same ISR functions;
  - same global writes;
  - same entry function;
  - same unwind/property settings;
  - no active C_ASYNC_PROVER labels in improved main.
- [x] For `Failed vs Successful`, verify whether improved missed a global-changing ISR or stock modeled an impossible interrupt.
- [x] For `Successful vs Failed`, verify whether improved injected a feasible ISR ordering or over-injected.
- [x] For `Failed vs Exit 6`, inspect improved logs and decide whether exit 6 is a pipeline/tool bug or unsupported model.
- [x] Write one verdict per case in `check-src/uncomparable-correctness.md`.

**Exit criteria:**

- Every IntAbs mismatch has a correctness verdict.
- Any source mismatch is converted into a concrete normalization fix.
- Any true tool/pipeline failure is tracked separately from valid benchmark outcomes.

## Phase 5: i-CBMC Logger2 Failed vs Exit 6 Audit

**Scope:** Audit de-duplicated Logger2 cases and avoid double-counting diagnostic suite repeats.

Logical cases:

| Source family | Cases |
| --- | --- |
| Logger2 | `logger2-conc`, `logger2-bug-conc`, `logger2-conc-cprover`, `logger2-bug-conc-cprover` |

- [x] Use Phase 0 logical IDs to pick one canonical evidence suite per case. Prefer `icbmc-timeout-30m-logger-stable` for stable five-run logs.
- [x] Rerun improved variants with trace/log evidence and preserve exit 6 logs.
- [x] Inspect whether exit 6 happens during CBMC verification, injected source compilation, or invalid generated GOTO/program state.
- [x] Inspect stock failure traces to see whether the property failure is real for the intended Logger2 model.
- [x] Compare Logger2 non-CPROVER and CPROVER variants:
  - if CPROVER variants are semantically closer to stock, use them as the preferred canonical cases;
  - if non-CPROVER variants retain pthread or async behavior, keep them out of headline comparison.
- [x] Decide for each logical case:
  - fix improved source/injection;
  - mark stock-only diagnostic;
  - keep excluded from automatic `run_all.sh` with precise reason.

**Exit criteria:**

- Logger2 is no longer reported as nine independent correctness failures.
- Each logical Logger2 case has one canonical verdict and one canonical suite location.

**Phase 3-5 audit result:** `check-src/uncomparable-correctness.md` records 11
`improved_correct` cases that must remain uncomparable because the stock model
does not match atomic improved-pipeline ISR semantics, plus 5 `both_need_fix`
cases that require nested-atomic or missing-body fixes before correctness can be
compared.

## Phase 6: Apply Source, Manifest, Or Report Fixes

**Scope:** Only after evidence exists.

- [x] For `stock_correct` where improved missed a real bug:
  - fix improved `isr_define` extraction;
  - ensure ISR is whole-function atomic;
  - ensure ISR writes appear in the interleaving manifest;
  - rerun the case.
  - Phase 6 result: no audited case was classified as `stock_correct`.
- [x] For `improved_correct` where stock is over-approximate:
  - keep the case in `uncomparable.md`;
  - document stock as over-approximate/incompatible;
  - do not report speed/RAM delta.
- [x] For `both_models_different`:
  - normalize stock and improved source roots until they model the same ISR behavior;
  - rerun both variants.
  - Phase 6 result: no audited case was classified as `both_models_different`.
- [x] For `both_need_fix` cases found during audit:
  - keep the case in `uncomparable.md`;
  - document the concrete blocker before any speed/RAM comparison;
  - do not report speed/RAM delta.
- [x] For `no_injection_false`:
  - identify whether ISR metadata, source layout, or candidate filtering is the blocker;
  - keep the case out of comparable benchmark results until improved injection emits safe candidates.
  - Phase 6 result: these cases are now explicitly classified as requiring
    ISR source-effect metadata or insertion-site manifest fixes before
    comparison. They were not promoted because the current manifest lacks safe
    insertion locations.
- [x] For `needs_manual_review` no-injection cases found during audit:
  - keep the case in `uncomparable.md`;
  - document unresolved external-call/pointer-write reachability;
  - do not report speed/RAM delta.
- [x] For `no_injection_true`:
  - reclassify from generic `No Injection Candidates` to a clearer final status.
  - Phase 6 result: no audited case was classified as `no_injection_true`.

**Exit criteria:**

- No case remains in a vague "we do not know why" state.
- Any newly comparable case moves to `check-src/benchmark.md` only after both variants produce the same verification outcome.

## Phase 7: Full Docker Verification And Benchmark Regeneration

**Scope:** Run only after all selected fixes are complete.

- [x] Run structural tests:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

- [x] Run targeted benchmark suites in Docker for every changed case:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/<suite>.json --case <case>"
```

- [x] Rerun full enabled benchmark suites after targeted cases pass:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "bash check-src/benchmarks/run_all.sh && python3 check-src/benchmarks/common/report_benchmark.py"
```

- [x] Regenerate correctness report:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/uncomparable_audit.py --write-report"
```

**Exit criteria:**

- `check-src/benchmark.md` contains only same-outcome comparable cases.
- `check-src/uncomparable.md` contains only explained, evidence-backed uncomparable cases.
- `check-src/uncomparable-correctness.md` contains the correctness verdict and action for every audited case.

## Phase 8: Final Acceptance Criteria

The work is complete only when all of these are true:

- Every `Failed vs Successful`, `Successful vs Failed`, and `Failed vs Exit 6` logical case has a verdict: `stock_correct`, `improved_correct`, `both_models_different`, or `both_need_fix`.
- Every `NO_INJECTION_CANDIDATES` case has `no_injection_true`, `no_injection_false`, or `needs_manual_review` with a concrete reason.
- No duplicate diagnostic row is counted as a separate logical correctness issue.
- Any case promoted to `benchmark.md` has matching verification outcomes across stock and improved variants.
- No speed/RAM percentage is reported for a case with mismatched or unresolved verification outcomes.
- All changed scripts pass `selftest.ps1`, `py_compile`, and Docker report generation.
