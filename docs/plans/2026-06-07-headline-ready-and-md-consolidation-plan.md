# Benchmark Comparison And Markdown Consolidation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

**Goal:** Make `benchmark.md` the single comparison report for every measured case, including both output correctness and performance, and reduce duplicated Markdown under `check-src`.

**Architecture:** Treat every measured case as comparable on performance, even when stock CBMC and improved CBMC produce different verification outputs. `benchmark.md` must report stock output, improved output, which output is judged correct when they differ, why, and speed/RAM deltas in one place. `uncomparable.md` remains an appendix for cases with missing measurements, tool errors, disabled/not-run evidence, or detailed diagnostics; `no-injection-failures.md` remains a dedicated source-effect report.

**Tech Stack:** Python benchmark scripts, JSON suite manifests, Docker benchmark runner, PowerShell selftests, generated Markdown reports.

---

## Corrected Requirements

The benchmark policy is:

- `benchmark.md` is the main comparison report.
- Every measured case must compare:
  - stock CBMC output;
  - improved CBMC output;
  - stock time/RAM;
  - improved time/RAM;
  - speed/RAM delta.
- If outputs differ, `benchmark.md` must still show performance deltas and must add:
  - which side is judged correct;
  - why that side is correct;
  - whether the difference comes from ISR/task atomic modeling, `C_ASYNC_PROVER` over-approximation, missing injection, unsupported concurrency, timeout, memory limit, or a model/tool error.
- Do not split the main benchmark into "performance-comparable" versus "correctness-only" groups.
- Keep `check-src/no-injection-failures.md` as a standalone file.
- Merge `check-src/uncomparable-correctness.md` into `check-src/uncomparable.md`.
- Remove duplicated Markdown content and avoid overloading readers with the same information in several files.

## Final Markdown Contract

Keep these four root-level Markdown files under `check-src`:

| Retained file | Role |
| --- | --- |
| `check-src/README.md` | Human entry point: pipeline, suite JSON guide, source layout, provenance summary, quick commands. |
| `check-src/benchmark.md` | Main comparison report for all measured cases: output, correctness judgment, time/RAM, deltas. |
| `check-src/uncomparable.md` | Diagnostic appendix for missing results, disabled/not-run cases, tool/model blockers, timeout/memory details, and folded correctness audit tables. |
| `check-src/no-injection-failures.md` | Dedicated source-effect report for `NO_INJECTION_CANDIDATES` cases. |

All other Markdown files under `check-src` should be deleted after useful non-duplicated content is folded into one of the four files above. In particular, `check-src/benchmarks/README.md`, `PIPELINE.md`, `VERIFICATION_PROTOCOL.md`, per-case `CASE.md`, corpus `PROVENANCE.md`, `CANDIDATES.md`, `CASE_INTAKE.md`, and `INVENTORY.md` should not remain as separate Markdown files.

## Current Findings

- `benchmark.md` currently suppresses speed/RAM deltas with `Not reported because the suite is not headline-ready` for comparable Logger2 measurements in disabled diagnostic suites.
- That suppression is now the wrong behavior. The report must print performance deltas for any case with measured stock and improved rows, regardless of suite headline readiness.
- Existing correctness data already exists in:
  - `check-src/benchmarks/results/audit/outcome-mismatch-audit.csv`;
  - `check-src/benchmarks/results/audit/no-injection-audit.csv`;
  - generated `check-src/uncomparable-correctness.md`;
  - generated `check-src/no-injection-failures.md`.
- `no-injection-failures.md` should remain because it contains detailed source-effect evidence that would overload the main benchmark.
- `uncomparable-correctness.md` should be merged into `uncomparable.md` to remove duplicate correctness reporting.

## Files To Modify

| File | Responsibility |
| --- | --- |
| `check-src/benchmarks/common/report_benchmark.py` | Generate `benchmark.md` as an all-case comparison report; always compute performance deltas when both variants have measured time/RAM; include correctness judgment inline. |
| `check-src/benchmarks/common/uncomparable_audit.py` | Fold `uncomparable-correctness.md` content into `uncomparable.md`; stop writing the standalone correctness Markdown. |
| `check-src/benchmarks/common/global_effect_scan.py` | Keep writing `check-src/no-injection-failures.md`; remove duplicate no-injection detail from other docs except compact references. |
| `check-src/benchmarks/common/outcome_mismatch_audit.py` | Keep correctness verdict rules used by `benchmark.md` and `uncomparable.md`. |
| `check-src/benchmarks/tests/selftest.ps1` | Assert all measured cases can show performance deltas, no headline-ready suppression text remains, and only the four root Markdown files remain. |
| `check-src/README.md` | Fold pipeline, suite JSON guide, source provenance, and benchmark operation docs here. |
| `check-src/benchmark.md` | Generated main comparison report. |
| `check-src/uncomparable.md` | Generated diagnostic appendix plus folded correctness audit. |
| `check-src/no-injection-failures.md` | Generated no-injection source-effect report; keep standalone. |
| `check-src/**/*.md` except the four retained files | Delete after deduplicating useful content. |

## Report Model

Each case row or section in `benchmark.md` must have this logical schema:

| Field | Meaning |
| --- | --- |
| Suite | Suite that produced the measurement. |
| Case | Case name. |
| Stock output | Normalized stock verify result: success, failed, timeout, memory, unsupported, exit code, missing. |
| Improved output | Normalized improved verify result. |
| Output relation | same output, stock-only fail, improved-only fail, timeout/memory/tool mismatch, missing result. |
| Correct output | `stock`, `improved`, `both`, `unknown`, or `not_applicable`. |
| Correctness reason | Short explanation from audit records or generated fallback. |
| Stock total time | Median measured total time in ms. |
| Improved total time | Median measured total time in ms. |
| Speed delta | Faster/slower percentage whenever both totals exist. |
| Stock peak RAM | Median/peak RSS in MB using current report convention. |
| Improved peak RAM | Median/peak RSS in MB using current report convention. |
| RAM delta | Less/more RAM percentage whenever both peaks exist. |

Important rule: output mismatch must not suppress speed/RAM deltas. Missing measurements may still show `N/A` for the missing side.

## Phase 0: Freeze Current State

**Goal:** Capture existing suppression points and Markdown inventory before changing report semantics.

- [x] Record current non-headline-ready suppression lines:

```powershell
Select-String -Path .\check-src\benchmark.md -Pattern 'Not reported because the suite is not headline-ready' -Context 8,2
```

Expected: Logger2 sections from `icbmc-timeout-30m` and `icbmc-timeout-30m-logger-stable`.

- [x] Record current Markdown inventory:

```powershell
Get-ChildItem -Path .\check-src -Recurse -Filter *.md |
  ForEach-Object { $_.FullName.Replace((Resolve-Path .).Path + '\', '') } |
  Sort-Object
```

Expected: many Markdown files, including generated reports and per-case/provenance docs.

- [x] Record current audit counts:

```powershell
Import-Csv .\check-src\benchmarks\results\audit\outcome-mismatch-audit.csv |
  Group-Object verdict,correct_variant |
  Select-Object Count,Name

Import-Csv .\check-src\benchmarks\results\audit\no-injection-audit.csv |
  Group-Object verdict |
  Select-Object Count,Name
```

Expected baseline from latest run: mismatch verdicts include `improved_correct`; no known `both_need_fix` should remain unless fresh evidence says otherwise.

**Exit criteria:** The old report suppression behavior and Markdown duplication are documented before refactor.

## Phase 1: Make `benchmark.md` Compare Every Measured Case

**Goal:** Replace the old "only comparable cases get performance deltas" behavior with all-case output/performance comparison.

- [x] In `report_benchmark.py`, introduce a case comparison record:

```python
def build_case_comparison(suite, case, grouped_rows, audit_records):
    stock_total = total_time_ms(grouped_rows, "stock_cprover_async")
    improved_total = total_time_ms(grouped_rows, "improved_pipeline")
    stock_peak = peak_rss_mb(grouped_rows, "stock_cprover_async")
    improved_peak = peak_rss_mb(grouped_rows, "improved_pipeline")
    stock_output = verify_summary(grouped_rows, "stock_cprover_async")
    improved_output = verify_summary(grouped_rows, "improved_pipeline")
    correctness = correctness_record_for_case(suite, case, stock_output, improved_output, audit_records)
    return {
        "suite": suite,
        "case": case,
        "stock_output": stock_output,
        "improved_output": improved_output,
        "correct_output": correctness["correct_variant"],
        "correctness_verdict": correctness["correctness_verdict"],
        "correctness_reason": correctness["evidence"],
        "stock_total_ms": stock_total,
        "improved_total_ms": improved_total,
        "speed_delta": percent_delta(stock_total, improved_total),
        "stock_peak_mb": stock_peak,
        "improved_peak_mb": improved_peak,
        "ram_delta": percent_delta(stock_peak, improved_peak),
    }
```

- [x] Remove the condition that only prints deltas for matching verification outcomes.

Old behavior to remove:

```python
if not comparable:
    lines.append("Not reported for not-comparable verification outcomes.")
```

New behavior:

```python
if stock_total is not None and improved_total is not None:
    lines.append(format_speed_delta(stock_total, improved_total))
else:
    lines.append("N/A: missing measured time for one side.")
```

- [x] Remove the condition that suppresses deltas for non-headline-ready suites.

Old behavior to remove:

```python
"Not reported because the suite is not headline-ready."
```

New behavior:

```python
"improved is X% faster"
```

or:

```python
"improved is X% slower"
```

- [x] Keep suite readiness in the report only as metadata:

```markdown
## Suite Status

| Suite | Manifest enabled | Diagnostic suite | Notes |
```

Do not let suite readiness suppress performance comparison.

**Exit criteria:** `benchmark.md` can display output and performance for same-output and different-output cases.

## Phase 2: Put Correctness Judgment Inline With Each Case

**Goal:** If stock and improved outputs differ, explain which output is correct and why directly in `benchmark.md`.

- [x] Load `outcome-mismatch-audit.csv` and `no-injection-audit.csv` in `report_benchmark.py`.

- [x] For outcome mismatches with audit verdicts, render:

```markdown
Correct output: `improved_pipeline`

Reason: Stock C_ASYNC_PROVER exposes a non-atomic async interleaving; improved keeps ISR/task entry atomic, matching the benchmark model.
```

- [x] For same outputs, render:

```markdown
Correct output: `both`

Reason: Both variants reached the same verification output; no correctness mismatch was audited for this case.
```

- [x] For no-injection failures, render a compact reason and link to `no-injection-failures.md`:

```markdown
Correct output: `unknown`

Reason: Improved reported `NO_INJECTION_CANDIDATES`, but source-effect scan found ISR-written globals reachable from `main`. See `no-injection-failures.md`.
```

- [x] For missing/timeout/memory/tool-error cases, render:

```markdown
Correct output: `unknown`

Reason: At least one side did not produce a complete verification result. See `uncomparable.md`.
```

**Exit criteria:** A reader does not need to leave `benchmark.md` to understand why an output mismatch is judged in favor of stock or improved.

## Phase 3: Promote Or Normalize Logger2 Without Hiding Mismatch Performance

**Goal:** Remove the visible `headline-ready` suppression and ensure Logger2 cases have performance deltas.

- [x] Rerun Logger2 diagnostic suites in Docker if current CSVs are stale:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/icbmc-timeout-30m-logger-stable.json && python3 check-src/benchmarks/common/report_benchmark.py"
```

- [x] Do not exclude `logger2-bug-conc-cprover` from performance comparison just because stock fails and improved succeeds.

Expected final case behavior:

```text
stock output: VERIFICATION FAILED
improved output: VERIFICATION SUCCESSFUL
correct output: improved_pipeline
performance: stock time/RAM vs improved time/RAM with percent delta
```

- [x] Optionally promote stable same-output Logger2 cases into `icbmc-large` for suite organization, but this is not required for performance deltas after Phase 1.

- [x] Confirm no suppression text remains:

```powershell
Select-String -Path .\check-src\benchmark.md -Pattern 'Not reported because the suite is not headline-ready'
```

Expected: no output.

**Exit criteria:** Every Logger2 section with stock and improved measurements has speed/RAM deltas, including output mismatch cases.

## Phase 4: Merge Only `uncomparable-correctness.md`

**Goal:** Remove one duplicate correctness report while keeping no-injection detail standalone.

- [x] Move the correctness audit summary from `check-src/uncomparable-correctness.md` into `check-src/uncomparable.md` under:

```markdown
## Correctness Audit Summary
```

- [x] Move the outcome mismatch audit table into `check-src/uncomparable.md` under:

```markdown
## Output Mismatch Audit Details
```

- [x] Keep `check-src/no-injection-failures.md` as a separate generated file.

- [x] In `uncomparable.md`, avoid duplicating the full no-injection details. Use only:

```markdown
## No Injection Candidate Cases

Detailed ISR/global reachability evidence is kept in `check-src/no-injection-failures.md`.
```

- [x] Update generators:

```text
uncomparable_audit.py: stop writing check-src/uncomparable-correctness.md
global_effect_scan.py: continue writing check-src/no-injection-failures.md
report_benchmark.py: link to benchmark.md, uncomparable.md, and no-injection-failures.md
```

- [x] Delete only:

```powershell
Remove-Item .\check-src\uncomparable-correctness.md -Force
```

Do not delete:

```text
check-src/no-injection-failures.md
```

**Exit criteria:** Correctness audit content is available in `uncomparable.md`; detailed no-injection evidence remains in `no-injection-failures.md`.

## Phase 5: Remove Duplicate Reader-Facing Markdown

**Goal:** Reduce Markdown overload while preserving unique content.

- [x] Fold `check-src/benchmarks/README.md`, `PIPELINE.md`, and `VERIFICATION_PROTOCOL.md` into `check-src/README.md`.

Use this structure:

```markdown
## Benchmark Pipeline

### Source Inputs
### Suite JSON
### Stock C_ASYNC_PROVER Variant
### Improved Interleaving Pipeline Variant
### Measurement Semantics
### CSV Outputs
### Report Generation

## Suite JSON Configuration

## Verification And Correctness Policy
```

- [x] Fold source-level docs into `check-src/README.md` only when they contain unique reader-facing information:

```text
check-src/benchmark-sources/README.md
check-src/benchmark-sources/CANDIDATES.md
check-src/benchmark-sources/CASE_INTAKE.md
check-src/benchmark-sources/INVENTORY.md
check-src/benchmark-sources/*/PROVENANCE.md
```

- [x] Do not copy repeated per-case boilerplate from every `CASE.md`. Instead, generate or write one compact catalog table in `README.md`:

```markdown
## Case Catalog

| Corpus | Case | Suite | Enabled | Stock root | Improved root | ISR functions | Origin |
| --- | --- | --- | --- | --- | --- | --- | --- |
```

- [x] Delete non-retained Markdown after content is folded:

```powershell
$allowed = @(
  (Resolve-Path .\check-src\README.md).Path,
  (Resolve-Path .\check-src\benchmark.md).Path,
  (Resolve-Path .\check-src\uncomparable.md).Path,
  (Resolve-Path .\check-src\no-injection-failures.md).Path
)
Get-ChildItem .\check-src -Recurse -Filter *.md |
  Where-Object { $allowed -notcontains $_.FullName } |
  Remove-Item -Force
```

**Exit criteria:** The only Markdown files under `check-src` are `README.md`, `benchmark.md`, `uncomparable.md`, and `no-injection-failures.md`.

## Phase 6: Update Selftests For New Semantics

**Goal:** Prevent old suppression and duplicate Markdown from returning.

- [x] Add a selftest that fails if `benchmark.md` suppresses performance:

```powershell
$benchmark = Get-Content "$RepoRoot\check-src\benchmark.md" -Raw
if ($benchmark -match 'Not reported because the suite is not headline-ready') {
  throw 'benchmark.md must always compare performance when both sides have measurements'
}
if ($benchmark -match 'Not reported for not-comparable verification outcomes') {
  throw 'benchmark.md must report performance even when verification outputs differ'
}
```

- [x] Add a selftest that checks output/correctness/performance columns exist:

```powershell
foreach ($required in @('Stock output', 'Improved output', 'Correct output', 'Stock total time', 'Improved total time', 'Speed delta', 'RAM delta')) {
  if ($benchmark -notmatch [regex]::Escape($required)) {
    throw "benchmark.md missing comparison field: $required"
  }
}
```

- [x] Add a Markdown allowlist selftest:

```powershell
$allowedMarkdown = @(
  'check-src/README.md',
  'check-src/benchmark.md',
  'check-src/uncomparable.md',
  'check-src/no-injection-failures.md'
)
$actualMarkdown = Get-ChildItem "$RepoRoot\check-src" -Recurse -Filter *.md |
  ForEach-Object { $_.FullName.Replace($RepoRoot + '\', '').Replace('\', '/') } |
  Sort-Object
$extraMarkdown = $actualMarkdown | Where-Object { $allowedMarkdown -notcontains $_ }
if ($extraMarkdown) {
  throw "unexpected Markdown files under check-src: $($extraMarkdown -join ', ')"
}
```

- [x] Add a selftest that confirms `no-injection-failures.md` still exists:

```powershell
if (-not (Test-Path "$RepoRoot\check-src\no-injection-failures.md")) {
  throw 'no-injection-failures.md must remain as a standalone source-effect report'
}
```

**Exit criteria:** Tests encode the corrected report semantics.

## Phase 7: Docker Benchmark And Report Regeneration

**Goal:** Produce final reports from Docker data after the report and docs refactor.

- [x] Run full enabled benchmark and regenerate reports:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "bash check-src/benchmarks/run_all.sh && python3 check-src/benchmarks/common/uncomparable_audit.py --inventory-only && python3 check-src/benchmarks/common/global_effect_scan.py && python3 check-src/benchmarks/common/outcome_mismatch_audit.py && python3 check-src/benchmarks/common/report_benchmark.py"
```

- [x] Rerun diagnostic Logger2 evidence if needed for fresh correctness judgment:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/run_evidence_case.py --suite check-src/benchmarks/suites/icbmc-timeout-30m-logger-stable.json --case logger2-bug-conc-cprover && python3 check-src/benchmarks/common/outcome_mismatch_audit.py && python3 check-src/benchmarks/common/report_benchmark.py"
```

- [x] Verify old suppression text is gone:

```powershell
Select-String -Path .\check-src\benchmark.md -Pattern 'Not reported because the suite is not headline-ready|Not reported for not-comparable verification outcomes'
```

Expected: no output.

- [x] Verify final Markdown list:

```powershell
Get-ChildItem .\check-src -Recurse -Filter *.md |
  ForEach-Object { $_.FullName.Replace((Resolve-Path .).Path + '\', '') } |
  Sort-Object
```

Expected exactly:

```text
check-src\README.md
check-src\benchmark.md
check-src\no-injection-failures.md
check-src\uncomparable.md
```

- [x] Run final checks:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
git diff --check
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 -m py_compile check-src/benchmarks/common/report_benchmark.py check-src/benchmarks/common/uncomparable_audit.py check-src/benchmarks/common/run_evidence_case.py check-src/benchmarks/common/global_effect_scan.py check-src/benchmarks/common/outcome_mismatch_audit.py check-src/benchmarks/common/runner.py"
```

Expected:

```text
selftest ok
```

`git diff --check` exits 0, and Docker `py_compile` exits 0.

**Exit criteria:** Final reports are generated from Docker data, benchmark compares output and performance for every measured case, and Markdown duplication is removed.

## Final Acceptance Criteria

- [x] `benchmark.md` reports every measured case with stock output, improved output, correctness judgment, reason, time/RAM, and speed/RAM delta.
- [x] Output mismatch no longer suppresses performance comparison.
- [x] Disabled/non-headline suite status no longer suppresses performance comparison.
- [x] Cases with missing measurements show `N/A` only for the missing metric, not for unrelated output/correctness fields.
- [x] If stock and improved outputs differ, `benchmark.md` states which side is correct and why.
- [x] `logger2-bug-conc-cprover` remains performance-compared and explains why improved output is correct.
- [x] `check-src/no-injection-failures.md` remains standalone.
- [x] `check-src/uncomparable-correctness.md` is removed after its content is folded into `check-src/uncomparable.md`.
- [x] Duplicate operational/source Markdown is folded into `check-src/README.md`, then removed.
- [x] Only these Markdown files remain under `check-src`: `README.md`, `benchmark.md`, `uncomparable.md`, `no-injection-failures.md`.
- [x] `selftest.ps1`, Docker full benchmark/report generation, Docker `py_compile`, and `git diff --check` pass.

## Implementation Notes

- `benchmark.md` now compares every measured stock/improved case on output, correctness judgment, time, RAM, and deltas.
- Output mismatches no longer suppress performance deltas.
- `logger2-bug-conc-cprover` appears with `Correct output: improved` and keeps speed/RAM deltas in both diagnostic suites where measured.
- `uncomparable-correctness.md` was removed; its audit summary and output mismatch details are folded into `uncomparable.md`.
- `no-injection-failures.md` remains as the standalone detailed source-effect report.
- `check-src` now contains exactly four Markdown files: `README.md`, `benchmark.md`, `uncomparable.md`, and `no-injection-failures.md`.
