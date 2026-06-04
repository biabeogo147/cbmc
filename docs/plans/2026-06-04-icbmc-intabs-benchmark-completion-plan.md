# i-CBMC And IntAbs Benchmark Completion Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Complete the i-CBMC and IntAbs benchmark coverage by gradually normalizing upstream cases into runnable `check-src/benchmark-sources/*/cases`, validating each batch in Docker, and promoting only meaningful comparable cases into `check-src/benchmark.md`.

**Architecture:** Add cases in controlled phases. Each phase imports a fixed batch, creates stock C_ASYNC_PROVER and improved interleaving-pipeline variants, keeps improved ISR/task definitions under `isr_define/`, runs Docker smoke checks, classifies comparable versus uncomparable results, and regenerates CSV/Markdown reports.

**Tech Stack:** CBMC/goto-cc/aib, Python benchmark runner, suite JSON manifests, Docker Linux benchmark image, Markdown reports.

---

## Current State

Existing normalized case roots:

| Corpus | Current cases |
| --- | --- |
| i-CBMC | `blink`, `blink-bug`, `logger`, `logger-bug`, `rc-core`, `rc-core-bug` |
| IntAbs | `logger2`, `logger3`, `sc520wdt-1`, `sc520wdt-2`, `wdt-pci-2`, `wdt-pci-3`, `wdt-pci-src-3` |

Current report classification after the previous refactor:

- Comparable: IntAbs `sc520wdt-1`, `wdt-pci-3`, `wdt-pci-src-3`.
- Uncomparable: i-CBMC enabled cases currently compile, but improved pipeline has `NO_INJECTION_CANDIDATES`.
- Uncomparable: some IntAbs/local/OSEK cases have different stock versus improved verification outcomes.

Important source contract:

- Stock variant: explicit C_ASYNC_PROVER-compatible modeling.
- Improved variant: no active `__CPROVER_ASYNC_*`; ISR/task definitions under `isr_define/isr.c` or an explicitly documented deeper `isr_define/` path.
- Monolithic improved files may keep `main.c` as the only direct compile source and include `isr_define/isr.c` at the original definition point.
- Runner must compile injected improved trees from `interleaving_pipeline_injected.json` `project.translation_units`.

## Phase 0: Stabilize Intake Tooling And Baseline

**Scope:** 0 new cases. This phase prevents repeated manual mistakes before adding more source.

**Files:**
- Modify: `check-src/benchmarks/common/candidate_scan.py`
- Modify: `check-src/benchmarks/common/normalize_case.py`
- Modify: `check-src/benchmarks/tests/selftest.ps1`
- Create: `check-src/benchmark-sources/CASE_INTAKE.md`

- [ ] Confirm the working tree state before importing more cases. If upstream corpora have staged deletions or cleanup changes, record them in the phase notes and do not mix unrelated restoration with case normalization.
- [ ] Extend `candidate_scan.py` output with `already_staged`, `case_family`, and `recommended_phase` columns.
- [ ] Extend `normalize_case.py` so it can create this standard layout:

```text
check-src/benchmark-sources/<corpus>/cases/<case-name>/
  CASE.md
  stock-cprover-async/
  improved-pipeline/
    isr_define/
      isr.c
      isr.h
```

- [ ] Add a selftest fixture that checks every enabled i-CBMC/IntAbs improved case has `variant_isr_sources.improved_pipeline` pointing to an `isr_define/` path.
- [ ] Run:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/candidate_scan.py && python3 check-src/benchmarks/common/corpus_inventory.py"
```

**Exit criteria:**

- No new benchmark case yet.
- Candidate list explicitly marks existing versus missing cases.
- Intake doc explains how to classify stock, improved, comparable, and uncomparable outputs.

## Phase 1: Complete The IntAbs Watchdog Core Batch

**Scope:** 6 new IntAbs cases. These are close to the current working IntAbs cases and should have the highest chance of producing comparable numbers quickly.

**New cases:**

| New case | Upstream source | Reason |
| --- | --- | --- |
| `wdt-pci-1` | `intabs/upstream/repository/icbmc/wdt_pci_1/main.c` | Same family as existing `wdt-pci-2/3`, high score, C_ASYNC metadata present. |
| `wdt-pci-src-1` | `intabs/upstream/repository/src/test/wdt_pci_1/main.c` | Source-test counterpart for existing `wdt-pci-src-3`. |
| `sc1200wdt-1` | `intabs/upstream/repository/src/test/sc1200wdt_1/main.c` | Watchdog family with many pthread launches. |
| `sc1200wdt-2` | `intabs/upstream/repository/src/test/sc1200wdt_2/main.c` | Pair for `sc1200wdt-1`; likely useful for differential comparison. |
| `i8xx-tco-2` | `intabs/upstream/repository/icbmc/i8xx_tco_2/main.c` | New watchdog driver family, high score. |
| `i8xx-tco-3` | `intabs/upstream/repository/icbmc/i8xx_tco_3/main.c` | Pair for `i8xx-tco-2`, higher score. |

**Work per case:**

- [ ] Create `stock-cprover-async/main.c` from upstream, preserving or creating C_ASYNC_PROVER-compatible launch modeling.
- [ ] Create `improved-pipeline/main.c` plus `improved-pipeline/isr_define/isr.c`.
- [ ] Wrap configured ISR/task functions with `__CPROVER_atomic_begin/end`.
- [ ] Create `CASE.md` with origin, normalization notes, compile files, ISR functions, and expected first-run classification.
- [ ] Add each case to `check-src/benchmarks/suites/intabs-large.json` as `enabled: false`.
- [ ] Run Docker smoke with `--case <case>` and `--variant stock_cprover_async`, then `--variant improved_pipeline`.
- [ ] Enable only cases where both variants compile and verify reaches a classifiable outcome.

**Batch verification:**

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-large.json --case wdt-pci-1 --case wdt-pci-src-1 --case sc1200wdt-1 --case sc1200wdt-2 --case i8xx-tco-2 --case i8xx-tco-3"
```

**Exit criteria:**

- At least 4 of 6 cases enabled.
- At least 2 new comparable cases in `benchmark.md`, or explicit `uncomparable.md` reasons for every non-comparable case.

**Execution result, 2026-06-04:**

- Completed Phase 1 with all 6 cases normalized and enabled in `intabs-large.json`.
- Added comparable results for `sc1200wdt-1` and `sc1200wdt-2` to `check-src/benchmark.md`.
- Added explicit uncomparable results for `wdt-pci-1`, `wdt-pci-src-1`, `i8xx-tco-2`, and `i8xx-tco-3` to `check-src/uncomparable.md`; each compiles in both variants but stock/improved verification outcomes differ.
- Regenerated `check-src/benchmark-sources/CANDIDATES.md` so the Phase 1 upstream sources are marked as staged.
- Verified with Docker full `intabs-large.json`, `selftest.ps1`, and Python `py_compile` for benchmark common scripts.

## Phase 2: Add i-CBMC High-Score Conc/Seq Cases

**Scope:** 8 new i-CBMC cases. These are the highest-score missing i-CBMC variants and should be handled before smaller logger/brake cases.

**New cases:**

| New case | Upstream source |
| --- | --- |
| `rc-core-conc` | `icbmc/upstream/extracted/conc-code/rc-core/nobug/rc_core_conc.c` |
| `rc-core-conc-cprover` | `icbmc/upstream/extracted/conc-code/rc-core/nobug/rc_core_conc_cprover.c` |
| `rc-core-bug-conc` | `icbmc/upstream/extracted/conc-code/rc-core/bug/rc_core_bug_conc.c` |
| `rc-core-bug-conc-cprover` | `icbmc/upstream/extracted/conc-code/rc-core/bug/rc_core_bug_conc_cprover.c` |
| `blink-conc` | `icbmc/upstream/extracted/conc-code/blink/nobug/blink_conc.c` |
| `blink-bug-conc` | `icbmc/upstream/extracted/conc-code/blink/bug/blink_bug_conc.c` |
| `blink-seq` | `icbmc/upstream/extracted/seq-code/blink/nobug/blink_por_seq.c` |
| `blink-bug-seq` | `icbmc/upstream/extracted/seq-code/blink/bug/blink_bug_por_seq.c` |

**Special handling:**

- For monolithic C files with `static` helper state, use the include-based split:

```c
#include "isr_define/isr.c"
```

- If improved `goto-cc` reports ISR entries but empty `write_global_var` and empty `line_added_block_with_file`, keep the case enabled only if it adds useful stock/improved compile/verify evidence; otherwise stage it disabled with `NO_INJECTION_CANDIDATES` notes.
- Prefer cases where the raw manifest has non-empty `line_added_block_with_file`.

**Batch verification:**

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-large.json --case rc-core-conc --case rc-core-conc-cprover --case rc-core-bug-conc --case rc-core-bug-conc-cprover --case blink-conc --case blink-bug-conc --case blink-seq --case blink-bug-seq"
```

**Exit criteria:**

- At least 6 of 8 cases compile in both variants.
- At least 2 cases produce real improved injection candidates, or the phase report documents why i-CBMC cases are structurally unsuitable for AIB insertion.

**Execution result, 2026-06-04:**

- Completed Phase 2 with all 8 cases normalized and enabled in `icbmc-large.json`.
- The candidate inventory recognizes all 8 upstream Phase 2 sources as `staged`, including the `blink_*_por_seq.c` to `blink-*-seq` mapping.
- All 8 cases compile in both `stock_cprover_async` and `improved_pipeline` variants in Docker.
- All 8 cases are reported in `check-src/uncomparable.md`; no Phase 2 case appears in `check-src/benchmark.md` because the improved manifest has zero AIB insertion candidates.
- `rc-core-conc`, `rc-core-bug-conc`, and their CPROVER variants preserve stock/improved evidence, but stock CBMC reports unsupported concurrency and improved injection is `NO_INJECTION_CANDIDATES`.
- `blink-conc` and `blink-bug-conc` compile after normalized TinyOS syntax cleanup, but stock/improved verification outcomes differ and improved injection is `NO_INJECTION_CANDIDATES`.
- `blink-seq` and `blink-bug-seq` compile in both variants, but stock verification times out under the Phase 2 30-second cap and improved injection is `NO_INJECTION_CANDIDATES`.
- This documents the structural issue for this i-CBMC batch: the collected conc/seq artifacts already contain transformed/thread metadata and direct async/thread modeling, but the improved manifest does not expose non-empty `line_added_block_with_file`/write-candidate data for AIB insertion.
- Verified with Docker full `icbmc-large.json`, `selftest.ps1`, and Python `py_compile` for benchmark common scripts.

## Phase 3: Add Logger2 And Brake Coverage

**Scope:** 10 new i-CBMC cases. This phase improves breadth after the high-score families are triaged.

**New cases:**

| New case | Upstream source |
| --- | --- |
| `logger2-conc` | `icbmc/upstream/extracted/conc-code/logger2/nobug/logger2_conc.c` |
| `logger2-bug-conc` | `icbmc/upstream/extracted/conc-code/logger2/bug/logger2_bug_conc.c` |
| `logger2-conc-cprover` | `icbmc/upstream/extracted/conc-code/logger2/nobug/logger2_conc_cprover.c` |
| `logger2-bug-conc-cprover` | `icbmc/upstream/extracted/conc-code/logger2/bug/logger2_bug_conc_cprover.c` |
| `brake2-1-po` | `icbmc/upstream/extracted/po-code/brake/brake2_1_po.c` |
| `brake2-2-po` | `icbmc/upstream/extracted/po-code/brake/brake2_2_po.c` |
| `brake2-3-po` | `icbmc/upstream/extracted/po-code/brake/brake2_3_po.c` |
| `brake2-1-bug-po` | `icbmc/upstream/extracted/po-code/brake/brake2_1_bug_po.c` |
| `brake2-2-bug-po` | `icbmc/upstream/extracted/po-code/brake/brake2_2_bug_po.c` |
| `brake2-3-bug-po` | `icbmc/upstream/extracted/po-code/brake/brake2_3_bug_po.c` |

**Special handling:**

- Logger2 likely normalizes like existing logger cases, but should not be treated as headline if LOC remains too small.
- Brake cases have many async labels but lower LOC; keep them as breadth/control cases unless they add strong comparable evidence.

**Exit criteria:**

- Logger2 cases either enabled with real injection candidates or documented as smoke/control.
- Brake cases classified into comparable, uncomparable, or disabled-with-reason.

**Execution result, 2026-06-04:**

- Completed Phase 3 with all 10 cases normalized, enabled in `icbmc-large.json`, and recognized as `staged` by the candidate inventory.
- All 10 cases compile in both `stock_cprover_async` and `improved_pipeline` variants in Docker.
- All 10 improved variants produce real injection candidates and run AIB; none reports `NO_INJECTION_CANDIDATES`.
- Updated the normalization helper to include extracted ISR definitions at the last extracted task location. This preserves globals declared between upstream task definitions while keeping every extracted ISR atomic.
- The three Brake bug cases define `CBMC`, matching the upstream conditional used to include generated model definitions.
- All six Brake cases are classified in `check-src/uncomparable.md`: stock CBMC reports unsupported concurrency while improved verification succeeds.
- All four Logger2 cases are classified in `check-src/uncomparable.md`: stock verification reaches the Phase 3 30-second timeout while improved verification exits with code 6.
- No Phase 3 case appears in `check-src/benchmark.md`, because none has comparable stock/improved verification outcomes.
- Full Docker `icbmc-large.json` completed for 22 enabled cases in approximately 1,858 seconds. The regenerated reports load 1,284 official CSV rows after removing temporary smoke artifacts.

## Phase 4: Add Remaining IntAbs Driver Variants

**Scope:** 10 new IntAbs cases. This phase fills remaining high-score driver variants after the core watchdog batch is stable.

**New cases:**

| New case | Upstream source |
| --- | --- |
| `wdt-pci-1-main2` | `intabs/upstream/repository/icbmc/wdt_pci_1/main2.c` |
| `wdt-pci-2-main2` | `intabs/upstream/repository/icbmc/wdt_pci_2/main2.c` |
| `wdt-pci-3-main2` | `intabs/upstream/repository/icbmc/wdt_pci_3/main2.c` |
| `wdt-pci-src-1-main2` | `intabs/upstream/repository/src/test/wdt_pci_1/main2.c` |
| `wdt-pci-src-2-main2` | `intabs/upstream/repository/src/test/wdt_pci_2/main2.c` |
| `wdt-pci-src-3-main2` | `intabs/upstream/repository/src/test/wdt_pci_3/main2.c` |
| `i8xx-tco-1` | `intabs/upstream/repository/icbmc/i8xx_tco_1/main.c` |
| `i8xx-tco-src-2` | `intabs/upstream/repository/src/test/i8xx_tco_2/main.c` |
| `i8xx-tco-src-3` | `intabs/upstream/repository/src/test/i8xx_tco_3/main.c` |
| `rcmain` | `intabs/upstream/repository/src/test/rcmain/rc_core.c` |

**Exit criteria:**

- Total IntAbs enabled case count is at least 12.
- Comparable report has at least 6 IntAbs cases, or every failed candidate has a precise uncomparable reason.

**Execution result, 2026-06-04:**

- Completed Phase 4 with all 10 cases normalized, enabled in `intabs-large.json`, and recognized as `staged` by the candidate inventory.
- IntAbs now has 23 staged normalized cases and 21 enabled cases. All Phase 4 stock and improved variants compile in Docker.
- Nine Phase 4 improved variants produce real injection candidates and run AIB. `rcmain` is classified separately because its improved manifest has no injection candidates.
- All six WDT PCI `main2` cases have matching successful verification outcomes and are reported in `check-src/benchmark.md`.
- Across those six comparable cases, the full improved pipeline is 58.6% to 233.5% slower than stock CPROVER async, while using 1.1% to 2.6% less peak RSS.
- `i8xx-tco-1`, `i8xx-tco-src-2`, and `i8xx-tco-src-3` are reported in `check-src/uncomparable.md` because stock verification fails while improved verification succeeds.
- `rcmain` is reported in `check-src/uncomparable.md` because stock CBMC reports unsupported concurrency and the improved pipeline has no injection candidates.
- Updated normalization so stock pthread launches of zero-argument functions use `func()`, and nested pthread arguments are recognized. Every extracted improved ISR remains atomic.
- Full Docker `intabs-large.json` completed for 21 enabled cases in approximately 336 seconds. The regenerated reports load 1,644 official CSV rows.

## Phase 5: Full Benchmark Hardening And Reporting

**Scope:** No new cases unless a previous phase leaves fewer than 10 enabled useful cases.

**Work:**

- [x] Re-run all enabled suites in Docker:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "bash check-src/benchmarks/run_all.sh"
```

- [x] Regenerate inventory and reports:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/corpus_inventory.py && python3 check-src/benchmarks/common/report_benchmark.py"
```

- [x] Review `check-src/benchmark.md`:
  - no `Not comparable:` case reasons;
  - every comparable row has stock/improved full time and peak RSS deltas;
  - no headline case is based on disabled/control/smoke input.
- [x] Review `check-src/uncomparable.md`:
  - every disabled or non-comparable case has a concrete reason;
  - no case is missing measured rows unless intentionally staged.
- [x] Update `check-src/benchmark-sources/CANDIDATES.md` so already-imported cases are marked.
- [x] Update `check-src/benchmark-sources/README.md` with final case counts.

**Final acceptance criteria:**

- i-CBMC has at least 12 normalized cases staged, with at least 8 enabled after Docker validation.
- IntAbs has at least 16 normalized cases staged, with at least 12 enabled after Docker validation.
- `benchmark.md` contains only comparable results.
- `uncomparable.md` explains every unsupported/no-candidate/different-outcome case.
- Docker full benchmark and report generation complete without command-start, timeout, or memory-limit failures.

**Execution result, 2026-06-04:**

- Completed the final structurally valid full Docker run across all seven enabled suites in approximately 3,014 seconds.
- The final CSV set contains 1,494 raw rows across 39 enabled cases. No row reports a command-start, timeout, memory-limit, or RSS-limit failure.
- Kept all normalized sources staged, but disabled six historical i-CBMC timeout cases pending the 30-minute review documented below.
- Disabled four additional Phase 2 rc-core conc artifacts because their improved variants retain active pthread launches or do not keep ISR functions atomic from function entry. These cases also report no injection candidates. i-CBMC finishes with 24 staged and 12 enabled cases.
- Added the legacy IntAbs `logger2` normalized control case to `intabs-large.json` as disabled/staged with a concrete reason and `CASE.md`. IntAbs finishes with 23 staged and 21 enabled cases.
- Updated `report_benchmark.py` so disabled cases with no CSV rows retain their suite-manifest reason. Added a regression check to `selftest.ps1`.
- Added a structural regression gate to `selftest.ps1`: every enabled external improved case must have whole-function atomic ISR entries and no active CPROVER async or pthread launch in `main.c`.
- Regenerated `CANDIDATES.md`, `INVENTORY.md`, `benchmark.md`, and `uncomparable.md`. The reports load 1,284 measured rows after excluding warmups and preparation rows.
- `benchmark.md` contains 11 comparable cases, each with full measured time and peak RSS deltas, and no `Not comparable:` sections.
- `uncomparable.md` contains 49 classified cases. Every disabled case has a `Not run:` reason, and no case uses the generic missing-row message.
- Final acceptance criteria are satisfied: both external corpora exceed staged/enabled thresholds, every enabled case has CSV results, and the full Docker run and report generation complete without infrastructure or case timeout failures.

## 30-Minute Timeout Review

**Execution result, 2026-06-04:**

- Re-ran all six historical i-CBMC timeout cases with `timeout_sec: 1800` in the diagnostic `icbmc-timeout-30m` suite.
- `logger2-conc`, `logger2-bug-conc`, `logger2-conc-cprover`, and `logger2-bug-conc-cprover` complete before timeout. A follow-up suite records one warmup and five measured runs for each case.
- Across the stable Logger2 measurements, stock verification finishes in approximately 36 to 88 seconds and reports `VERIFICATION FAILED`; improved verification finishes in approximately 123 to 144 ms and exits with code 6. These outcomes remain not comparable.
- Normalized the two Logger2 CPROVER improved ISR bundles to whole-function atomic ISR entries before measurement.
- `blink-seq` and `blink-bug-seq` reach the initial 8192 MB RSS cap before timeout. A high-memory follow-up with a 14000 MB cap still reaches the cap after approximately 20.4 and 20.7 minutes respectively, before the 30-minute timeout.
- The blink improved variants finish quickly but have no injection candidates. The blink cases remain not comparable and are classified as memory-limited rather than timed out.
- Raw diagnostic evidence is stored in `icbmc-timeout-30m.csv`, `icbmc-timeout-30m-logger-stable.csv`, and `icbmc-timeout-30m-blink-highmem.csv`.
