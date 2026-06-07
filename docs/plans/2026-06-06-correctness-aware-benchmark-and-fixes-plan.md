# Correctness-Aware Benchmark And Fixes Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

**Goal:** Refactor the benchmark so it reports both performance and correctness, produce a detailed report for improved-pipeline injection failures, and fix the current `both_need_fix` cases before promoting any result.

**Architecture:** Keep Docker CSV measurements as the source of performance truth, and add a first-class correctness layer beside them. The benchmark report should have two independent axes: speed/RAM only for same-outcome comparable cases, and correctness verdicts for audited outcome-mismatch or no-injection cases. Fixes must be case-local or normalizer-backed, then rerun through the existing suite runner before any report promotion.

**Tech Stack:** Python benchmark scripts, JSON suite manifests, Docker runner, stock CBMC `C_ASYNC_PROVER`, improved CBMC interleaving pipeline, Markdown generated reports.

---

## Current Baseline

The current audit state is:

| Area | Current result | Meaning |
| --- | ---: | --- |
| Outcome mismatch audit | 16 logical cases | Cases where stock and improved verification outcomes differ. |
| `improved_correct` | 11 | Improved model is judged more faithful for ISR/task behavior, but speed/RAM must not be compared. |
| `both_need_fix` | 5 | Current model/result is not trustworthy enough on either side. |
| No-injection audit | 9 logical cases | Cases where improved injection reports `NO_INJECTION_CANDIDATES`. |
| `no_injection_false` | 6 | ISR affects globals reachable from `main`, but insertion/source-effect metadata is missing or filtered out. |
| `needs_manual_review` | 3 | Static scan cannot prove the no-injection rule because of unresolved external calls or pointer writes. |

The known `both_need_fix` cases are:

| Suite | Case | Main blocker |
| --- | --- | --- |
| `icbmc-timeout-30m-logger-stable` | `logger2-conc` | Stock missing `get_power_status` body; improved nested atomic. |
| `icbmc-timeout-30m-logger-stable` | `logger2-bug-conc` | Stock missing `get_power_status` body; improved nested atomic. |
| `icbmc-timeout-30m-logger-stable` | `logger2-conc-cprover` | Stock missing `get_power_status` body; improved nested atomic. |
| `icbmc-timeout-30m-logger-stable` | `logger2-bug-conc-cprover` | Stock missing `get_power_status` body; improved nested atomic. |
| `intabs-large` | `wdt-pci-2` | Improved nested atomic in `writer1`; stock has incomplete/incorrect callee evidence around `closesr3`. |

## Files To Modify

| File | Responsibility |
| --- | --- |
| `check-src/benchmarks/common/report_benchmark.py` | Generate performance and correctness-aware Markdown reports from CSV and audit CSVs. |
| `check-src/benchmarks/common/uncomparable_audit.py` | Keep producing deduplicated correctness inventory and `uncomparable-correctness.md`. May be split if it grows too much. |
| `check-src/benchmarks/common/outcome_mismatch_audit.py` | Convert from hard-coded verdict helper into a reusable correctness verdict table generator. |
| `check-src/benchmarks/common/global_effect_scan.py` | Provide detailed no-injection evidence: ISR functions, written globals, main-reachable globals, manifest counts, and blockers. |
| `check-src/benchmarks/common/run_evidence_case.py` | Rerun selected cases with trace/log/manifest artifacts in audit work directories. |
| `check-src/benchmarks/tests/selftest.ps1` | Add structural checks for correctness fields, no-injection report shape, and nested-atomic guards. |
| `check-src/benchmarks/README.md` | Document the new benchmark interpretation: performance axis vs correctness axis. |
| `check-src/benchmark.md` | Generated headline report with performance and correctness sections. |
| `check-src/uncomparable.md` | Generated detailed non-comparable report with correctness notes. |
| `check-src/uncomparable-correctness.md` | Generated audit verdict report. |
| `check-src/no-injection-failures.md` | New generated detailed report for improved cases that failed to inject correctly. |
| `check-src/benchmark-sources/icbmc/cases/logger2-*/stock-cprover-async/main.c` | Candidate case-local stock fixes for Logger2 missing model bodies. |
| `check-src/benchmark-sources/icbmc/cases/logger2-*/improved-pipeline/main.c` | Candidate case-local improved fixes for Logger2 nested atomic/model bodies. |
| `check-src/benchmark-sources/icbmc/cases/logger2-*/improved-pipeline/isr_define/isr.c` | Candidate case-local ISR extraction fixes for Logger2. |
| `check-src/benchmark-sources/intabs/cases/wdt-pci-2/stock-cprover-async/main.c` | Candidate stock model fix for `wdt-pci-2`. |
| `check-src/benchmark-sources/intabs/cases/wdt-pci-2/improved-pipeline/main.c` | Candidate improved model alignment for `wdt-pci-2`. |
| `check-src/benchmark-sources/intabs/cases/wdt-pci-2/improved-pipeline/isr_define/isr.c` | Candidate nested-atomic fix for `writer1`. |
| `check-src/benchmarks/suites/*.json` | Update case reasons/enablement only after Docker reruns prove the new status. |

## Correctness Vocabulary

Use these report-facing verdicts:

| Verdict | Meaning | Speed/RAM percentage allowed? |
| --- | --- | --- |
| `same_outcome_comparable` | Stock and improved reach the same verification outcome. | Yes, if suite is headline-ready. |
| `improved_correct` | Improved model is judged more faithful; stock outcome is over-approximate, under-approximate, or too weak. | No. |
| `stock_correct` | Stock model is judged more faithful; improved missed a real bug or introduced a wrong proof/fail. | No. |
| `both_correct_different_model` | Both answer different but intentional questions; keep diagnostic-only. | No. |
| `both_need_fix` | At least one side has an invalid/incomplete model or tool error before verdict. | No. |
| `no_injection_true` | ISR does not affect any global reachable from `main`; no injection is valid. | No, unless both variants still have same verification outcome for another reason. |
| `no_injection_false` | Improved failed to inject despite ISR-global-main overlap. | No. |
| `needs_manual_review` | Scanner cannot decide correctness safely. | No. |

## Phase 0: Freeze Baseline And Add Regression Fixtures

**Scope:** Capture the current benchmark/audit state before changing semantics.

- [x] Record current counts from:

```powershell
Import-Csv .\check-src\benchmarks\results\audit\outcome-mismatch-audit.csv | Group-Object verdict,correct_variant
Import-Csv .\check-src\benchmarks\results\audit\no-injection-audit.csv | Group-Object verdict
```

- [x] Add selftest fixtures that assert:
  - outcome audit contains no `pending_manual_review` for already-audited mismatch rows;
  - no-injection audit contains action-worthy verdicts;
  - generated `benchmark.md` does not print speed/RAM percentages for mismatched correctness verdicts.
- [x] Run:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

Expected: `selftest ok`.

**Exit criteria:** Existing generated reports can be regenerated without losing current correctness classifications.

## Phase 1: Make Correctness A First-Class Report Model

**Scope:** Refactor report data flow so performance comparability and correctness verdict are separate fields.

- [x] Add a Python data structure in `report_benchmark.py` for:

```python
{
    "performance_status": "comparable|not_comparable",
    "correctness_verdict": "same_outcome_comparable|improved_correct|stock_correct|both_need_fix|...",
    "correct_variant": "stock_cprover_async|improved_pipeline|both|none|unknown",
    "correctness_action": "...",
}
```

- [x] Load audit CSVs through one helper, keyed by `(suite, case)`.
- [x] For cases not present in audit CSVs:
  - same verify outcome -> `same_outcome_comparable`;
  - different verify outcome -> `needs_manual_review`;
  - timeout/memory/missing -> keep existing non-comparable reason.
- [x] Preserve the current rule that speed/RAM percentages are printed only when:
  - stock and improved verification classes match;
  - neither side timed out, hit memory limit, missed verify, or reported unsupported concurrency;
  - improved injection did not report `NO_INJECTION_CANDIDATES`;
  - suite is headline-ready.
- [x] Add selftest fixtures for each verdict class.

**Exit criteria:** Report generation can answer two questions independently: "which model is more correct?" and "which one is faster/uses less RAM on comparable cases?"

## Phase 2: Refactor `benchmark.md` Into Performance + Correctness Sections

**Scope:** Make `benchmark.md` useful even when many cases are not performance-comparable.

- [x] Keep the existing comparable case sections with time/RAM tables.
- [x] Add a top-level "Correctness Summary" section:
  - count `same_outcome_comparable`;
  - count `improved_correct`;
  - count `stock_correct`;
  - count `both_need_fix`;
  - count `no_injection_false`;
  - count `needs_manual_review`.
- [x] Add a "Correctness Wins" table:

```markdown
| Suite | Case | Correct variant | Verdict | Evidence summary | Action |
| --- | --- | --- | --- | --- | --- |
```

- [x] For `improved_correct`, explicitly state that this is a correctness result, not a speed/RAM result.
- [x] If future `stock_correct` cases appear, report them symmetrically.
- [x] Keep `uncomparable.md` as the detailed case-by-case appendix.
- [x] Update `check-src/benchmarks/README.md` to explain:
  - performance-comparable benchmark;
  - correctness-adjudicated benchmark;
  - unresolved diagnostic cases.

**Exit criteria:** A reader can open `benchmark.md` and see both performance numbers and correctness counts without confusing the two.

## Phase 3: Produce Detailed Improved Injection Failure Report

**Scope:** Create a dedicated report for cases where improved CBMC did not inject correctly.

- [x] Create `check-src/no-injection-failures.md` from `global_effect_scan.py` or a small companion writer.
- [x] For each `no_injection_false` case, include:
  - suite and case;
  - source root;
  - `isr_functions`;
  - original interleaving manifest count;
  - filtered candidate count;
  - missing fields, especially empty `line_added_block_with_file`;
  - ISR-written globals;
  - main-reachable globals;
  - overlap globals;
  - concrete action: source layout fix, manifest metadata fix, or scanner limitation.
- [x] For each `needs_manual_review` case, include:
  - unresolved external calls;
  - pointer-write blockers;
  - reason scanner cannot safely decide.
- [x] Add a compact link from `benchmark.md` and `uncomparable.md` to `no-injection-failures.md`.
- [x] Run Docker audit regeneration:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/uncomparable_audit.py --inventory-only && python3 check-src/benchmarks/common/global_effect_scan.py && python3 check-src/benchmarks/common/uncomparable_audit.py --write-report && python3 check-src/benchmarks/common/report_benchmark.py"
```

**Exit criteria:** Every improved no-injection failure has a source-level explanation and an actionable next step.

## Phase 4: Fix Logger2 `both_need_fix` Cases

**Scope:** Repair the four Logger2 cases enough that stock and improved both reach real verification outcomes.

- [x] Inspect these roots:
  - `check-src/benchmark-sources/icbmc/cases/logger2-conc/`
  - `check-src/benchmark-sources/icbmc/cases/logger2-bug-conc/`
  - `check-src/benchmark-sources/icbmc/cases/logger2-conc-cprover/`
  - `check-src/benchmark-sources/icbmc/cases/logger2-bug-conc-cprover/`
- [x] For stock variants, replace the incomplete `extern uint8_t get_power_status();` model with a real nondeterministic stub that matches the intended upstream environment:

```c
uint8_t __VERIFIER_nondet_uint8_t(void);

uint8_t get_power_status(void)
{
  return __VERIFIER_nondet_uint8_t();
}
```

- [x] Apply the same body consistently to improved variants when the function is referenced there.
- [x] Remove nested atomic patterns from improved Logger2 ISR/task extraction:
  - no function wrapped by `__CPROVER_atomic_begin/end` may call another wrapper that also starts an atomic section;
  - `isr_define/isr.c` should contain whole ISR/task entry functions with a single atomic boundary at the outermost entry only.
- [x] Prefer a normalizer-backed fix if the same nested-atomic pattern exists across all four Logger2 cases. If the pattern is case-specific, apply case-local edits and document them.
- [x] Add selftest checks:

```powershell
rg -n "__CPROVER_atomic_begin\\(\\).*__CPROVER_atomic_begin" check-src\benchmark-sources\icbmc\cases\logger2-* 
```

Expected: no nested atomic pattern in the improved Logger2 ISR extraction.

- [x] Rerun Logger2 diagnostic suite in Docker:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/icbmc-timeout-30m-logger-stable.json && python3 check-src/benchmarks/common/report_benchmark.py"
```

**Exit criteria:** Logger2 stock no longer fails only because of missing `get_power_status`, and improved no longer exits with nested atomic before verification.

## Phase 5: Fix IntAbs `wdt-pci-2` `both_need_fix`

**Scope:** Repair `wdt-pci-2` enough that both variants reach meaningful verification outcomes.

- [x] Inspect:
  - `check-src/benchmark-sources/intabs/cases/wdt-pci-2/stock-cprover-async/main.c`
  - `check-src/benchmark-sources/intabs/cases/wdt-pci-2/improved-pipeline/main.c`
  - `check-src/benchmark-sources/intabs/cases/wdt-pci-2/improved-pipeline/isr_define/isr.c`
- [x] Confirm whether stock's `closesr3` evidence is:
  - a typo for `closer3`;
  - a missing upstream helper;
  - a normalization artifact.
- [x] Fix stock only when the intended callee is clear from neighboring source or upstream origin.
- [x] Fix improved `writer1` nested atomic:
  - keep ISR whole-function atomic;
  - remove nested atomic calls inside the ISR body;
  - ensure `writer1` appears in the interleaving manifest with non-empty insertion metadata.
- [x] Rerun the single case in Docker:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/intabs-large.json --case wdt-pci-2 && python3 check-src/benchmarks/common/report_benchmark.py"
```

**Exit criteria:** `wdt-pci-2` is no longer `both_need_fix`; it is either comparable, `improved_correct`, `stock_correct`, or explicitly `both_correct_different_model`.

## Phase 6: Re-Audit Correctness After Fixes

**Scope:** Recompute verdicts from fresh Docker evidence.

- [x] Rerun evidence for all previously `both_need_fix` cases using `run_evidence_case.py`.
- [x] Update `outcome_mismatch_audit.py` verdict rules only when backed by the new logs/traces.
- [x] Regenerate:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/uncomparable_audit.py --inventory-only && python3 check-src/benchmarks/common/global_effect_scan.py && python3 check-src/benchmarks/common/outcome_mismatch_audit.py && python3 check-src/benchmarks/common/uncomparable_audit.py --write-report && python3 check-src/benchmarks/common/report_benchmark.py"
```

- [x] Promote a case to `benchmark.md` performance comparison only if both variants now have matching verification outcomes.

**Exit criteria:** `both_need_fix` count decreases, and every moved case has fresh Docker evidence.

## Phase 7: Full Benchmark Rerun And Final Reports

**Scope:** Produce final benchmark artifacts after report refactor and source fixes.

- [x] Run full enabled benchmark suites:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "bash check-src/benchmarks/run_all.sh && python3 check-src/benchmarks/common/report_benchmark.py && python3 check-src/benchmarks/common/uncomparable_audit.py --inventory-only && python3 check-src/benchmarks/common/global_effect_scan.py && python3 check-src/benchmarks/common/outcome_mismatch_audit.py && python3 check-src/benchmarks/common/uncomparable_audit.py --write-report && python3 check-src/benchmarks/common/report_benchmark.py"
```

- [x] Verify:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
git diff --check
```

- [x] Docker compile check:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 -m py_compile check-src/benchmarks/common/report_benchmark.py check-src/benchmarks/common/uncomparable_audit.py check-src/benchmarks/common/run_evidence_case.py check-src/benchmarks/common/global_effect_scan.py check-src/benchmarks/common/outcome_mismatch_audit.py"
```

**Exit criteria:** The final reports are generated from fresh Docker data and no script fails structural checks.

## Final Acceptance Criteria

- [x] `benchmark.md` reports both performance and correctness summaries.
- [x] Speed/RAM percentages appear only for same-outcome comparable cases.
- [x] Correctness verdicts identify whether stock CBMC or improved CBMC is more faithful when outcomes differ.
- [x] `no-injection-failures.md` explains every improved no-injection problem in source-level detail.
- [x] The four Logger2 cases no longer fail due to missing `get_power_status` body or improved nested atomic.
- [x] `wdt-pci-2` no longer fails due to stock incomplete callee evidence or improved nested atomic.
- [x] Any fixed case is rerun in Docker before being promoted or reclassified.
- [x] `selftest.ps1`, Docker `py_compile`, Docker report generation, and `git diff --check` pass.

## Implementation Notes

- Final enabled-suite benchmark was regenerated with Docker `run_all.sh`.
- Logger2 diagnostic CSVs were regenerated with clean mounted `WORK` directories so stale `/tmp` work products cannot leak into the report.
- `logger2-bug-conc-cprover` has fresh audit evidence and is classified as `improved_correct`, because stock C_ASYNC_PROVER reports the non-atomic `task_measure` interleaving while the improved pipeline preserves the ISR/task atomic-entry contract.
- `wdt-pci-2` is now same-outcome comparable: both variants verify successfully in the refreshed `intabs-large` CSV.
