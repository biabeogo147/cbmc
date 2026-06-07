# ISR Benchmark Comparison Results

Generated: 2026-06-07 06:57:07 UTC

This report is generated from `check-src/benchmarks/results/*.csv` by `check-src/benchmarks/common/report_benchmark.py`.
Warmup rows are ignored; measured rows are summarized with median time and median peak RSS per phase.
This file compares stock CBMC and improved CBMC output, correctness judgment, time, and RAM for every measured case. Diagnostic and no-injection audit evidence is folded into this same report.

Comparison labels: Stock CPROVER async, Improved pipeline, Correct output, Median, Peak RSS.

## Benchmark Scope

### Source Inventory

This table describes the source corpus size used to judge benchmark scale.

Column guide:

| Column | Meaning |
| --- | --- |
| `Corpus` | Stable corpus label used by this report. |
| `Path` | Repository-relative source root. |
| `C/H/I files` | Number of C, header, and preprocessed C files. |
| `LOC` | Total line count across those files. |

| Corpus | Path | C/H/I files | LOC |
| --- | --- | ---: | ---: |
| `trampoline-stock-cprover-async` | `check-src/benchmark-sources/trampoline/stock-cprover-async` | 153 | 22262 |
| `trampoline-improved-pipeline` | `check-src/benchmark-sources/trampoline/improved-pipeline` | 153 | 22257 |
| `icbmc-upstream` | `check-src/benchmark-sources/icbmc/upstream` | 232 | 216799 |
| `icbmc-po-code` | `check-src/benchmark-sources/icbmc/upstream/extracted/po-code` | 32 | 31302 |
| `icbmc-seq-code` | `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code` | 72 | 79314 |
| `icbmc-conc-code` | `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code` | 128 | 106183 |
| `intabs-upstream` | `check-src/benchmark-sources/intabs/upstream/repository` | 120 | 87868 |
| `intabs-icbmc` | `check-src/benchmark-sources/intabs/upstream/repository/icbmc` | 64 | 50459 |
| `intabs-src-test` | `check-src/benchmark-sources/intabs/upstream/repository/src/test` | 47 | 36088 |

## Suite Coverage

### Suite Readiness

This table shows which suite manifests are active, staged, and large enough for headline reporting.

Column guide:

| Column | Meaning |
| --- | --- |
| `Suite` | Suite manifest name used to group cases and CSV rows. |
| `Manifest enabled` | Whether `run_all.sh` includes this suite automatically. |
| `Staged cases` | Cases listed in the suite manifest, including disabled cases. |
| `Enabled cases` | Cases enabled for execution in that suite. |
| `Enabled compile LOC` | Estimated maximum compile LOC across enabled case variants. |
| `Headline-ready` | Whether the enabled suite is large enough for headline comparison claims. |

| Suite | Manifest enabled | Staged cases | Enabled cases | Enabled compile LOC | Headline-ready |
| --- | --- | ---: | ---: | ---: | --- |
| `icbmc-large` | true | 24 | 12 | 36008 | yes |
| `icbmc-timeout-30m` | false | 6 | 6 | 13202 | no |
| `icbmc-timeout-30m-blink-highmem` | false | 2 | 2 | 8111 | no |
| `icbmc-timeout-30m-logger-stable` | false | 4 | 4 | 5091 | no |
| `intabs-large` | true | 23 | 21 | 29597 | yes |
| `local-smoke` | true | 4 | 1 | 54 | no |
| `osek-local` | true | 6 | 2 | 199 | no |
| `trampoline-current` | true | 1 | 1 | 7605 | yes |
| `trampoline-expanded` | true | 1 | 1 | 7605 | yes |

## Correctness Results

### Correctness Summary

This table counts correctness verdicts across measured cases.

Column guide:

| Column | Meaning |
| --- | --- |
| `Verdict` | Normalized correctness classification assigned by comparison and audit evidence. |
| `Cases` | Number of measured cases assigned to the verdict. |

| Verdict | Cases |
| --- | ---: |
| `same_outcome_comparable` | 17 |
| `improved_correct` | 11 |
| `stock_correct` | 0 |
| `both_correct_different_model` | 0 |
| `both_need_fix` | 0 |
| `no_injection_true` | 0 |
| `no_injection_false` | 6 |
| `needs_manual_review` | 7 |
| `not_audited` | 0 |
| `pending_manual_review` | 7 |

### Correctness Wins

This table lists cases where one variant is judged more faithful than the other.

Column guide:

| Column | Meaning |
| --- | --- |
| `Suite` | Suite containing the audited case. |
| `Case` | Case with an output disagreement or correctness audit result. |
| `Correct variant` | Variant judged correct by the audit evidence. |
| `Verdict` | Correctness verdict assigned to the case. |
| `Evidence summary` | Short explanation of why that output is considered correct. |
| `Action` | Follow-up action or reporting policy for the case. |

| Suite | Case | Correct variant | Verdict | Evidence summary | Action |
| --- | --- | --- | --- | --- | --- |
| icbmc-timeout-30m | logger2-bug-conc-cprover | improved_pipeline | `improved_correct` | Stock C_ASYNC_PROVER exposes an interleaving through task_measure that violates numberOfRecords==pos+1; improved checks the extracted ISR/task body as one atomic entry, matching the benchmark ISR-atomic contract. | keep_benchmark_diagnostic_stock_non_atomic_async_interleaving |
| icbmc-timeout-30m-logger-stable | logger2-bug-conc-cprover | improved_pipeline | `improved_correct` | Stock C_ASYNC_PROVER exposes an interleaving through task_measure that violates numberOfRecords==pos+1; improved checks the extracted ISR/task body as one atomic entry, matching the benchmark ISR-atomic contract. | keep_benchmark_diagnostic_stock_non_atomic_async_interleaving |
| intabs-large | i8xx-tco-1 | improved_pipeline | `improved_correct` | Improved keeps ISR/task entry atomic and has filtered interleavings 3/3; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-1__evidence/i8xx-tco-1/measure-1/stock_cprover_async/main.c function closer2 line 722 thread 3 assertion 0 0 != 0. | keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads |
| intabs-large | i8xx-tco-2 | improved_pipeline | `improved_correct` | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-2__evidence/i8xx-tco-2/measure-1/stock_cprover_async/main.c function closer2 line 739 thread 2 assertion 0 0 != 0. | keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads |
| intabs-large | i8xx-tco-3 | improved_pipeline | `improved_correct` | Improved keeps ISR/task entry atomic and has filtered interleavings 6/6; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-3__evidence/i8xx-tco-3/measure-1/stock_cprover_async/main.c function closer3 line 749 thread 3 assertion 0 0 != 0. | keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads |
| intabs-large | i8xx-tco-src-2 | improved_pipeline | `improved_correct` | Improved keeps ISR/task entry atomic and has filtered interleavings 21/21; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-src-2__evidence/i8xx-tco-src-2/measure-1/stock_cprover_async/main.c function closer2 line 732 thread 2 assertion 0 0 != 0. | keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads |
| intabs-large | i8xx-tco-src-3 | improved_pipeline | `improved_correct` | Improved keeps ISR/task entry atomic and has filtered interleavings 23/23; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-src-3__evidence/i8xx-tco-src-3/measure-1/stock_cprover_async/main.c function closer2 line 732 thread 2 assertion 0 0 != 0. | keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads |
| intabs-large | sc520wdt-2 | improved_pipeline | `improved_correct` | Improved injected closer/writer interleavings and reaches Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__sc520wdt-2__evidence/sc520wdt-2/measure-1/improved_pipeline/isr_define/isr.c function closer line 840 thread 0 assertion dev_open dev_open != FALSE; stock baseline proves without that injected ISR ordering. | keep_benchmark_diagnostic_stock_model_too_weak |
| intabs-large | wdt-pci-1 | improved_pipeline | `improved_correct` | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__wdt-pci-1__evidence/wdt-pci-1/measure-1/stock_cprover_async/main.c function closer1 line 973 thread 3 assertion 0 0 != 0. | keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads |
| intabs-large | wdt-pci-src-1 | improved_pipeline | `improved_correct` | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__wdt-pci-src-1__evidence/wdt-pci-src-1/measure-1/stock_cprover_async/main.c function closer2 line 1002 thread 4 assertion 0 0 != 0. | keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads |
| local-smoke | t-isr-multifile | improved_pipeline | `improved_correct` | Improved trace reaches injected ISR/task perturbation; simple benchmark docs expect the injected pipeline to fail. | keep_benchmark_diagnostic_stock_model_too_weak |

## Diagnostic Results

### Diagnostic Summary

This table groups diagnostic cases by the reason they are not clean same-output comparisons.

Column guide:

| Column | Meaning |
| --- | --- |
| `Reason` | Diagnostic category derived from stock/improved verification outputs. |
| `Cases` | Number of cases assigned to that diagnostic category. |

| Reason | Cases |
| --- | ---: |
| Verification Failed vs Successful | 15 |
| Verification Successful vs Failed | 3 |
| Verification Failed vs Exit 6 | 0 |
| CBMC Unsupported Concurrency | 2 |
| Stock Timeout | 0 |
| Improved Timeout | 0 |
| Stock Memory Limit | 2 |
| Improved Memory Limit | 0 |
| No Injection Candidates | 7 |
| Missing Variant Results | 0 |
| Not Run / Disabled Cases | 23 |
| Other Verification Outcome Mismatches | 2 |

### Diagnostic Audit Summary

This table summarizes audit CSV coverage, not raw timing coverage.

Column guide:

| Column | Meaning |
| --- | --- |
| `Category` | Audit inventory category assigned before report rendering. |
| `Cases` | Number of cases present in the audit inventory for that category. |

| Category | Cases |
| --- | ---: |
| No Injection Candidates | 7 |
| Stock Memory Limit | 2 |
| Verification Failed vs Successful | 14 |
| Verification Successful vs Failed | 3 |

### No Injection Candidate Cases

This table audits no-injection results; such a result is valid only when no ISR-written global can affect a global reachable from `main`.

Column guide:

| Column | Meaning |
| --- | --- |
| `Suite` | Suite containing the no-injection case. |
| `Case` | Case whose improved pipeline reported no injection candidates. |
| `Verdict` | Audit judgment for the no-injection result. |
| `Original interleavings` | Interleaving sites before filtering. |
| `Filtered interleavings` | Interleaving sites after ISR/global filtering. |
| `Candidate globals` | Globals that may connect ISR writes to main-reachable state. |
| `Unknowns` | Unresolved source-analysis items requiring manual review. |

| Suite | Case | Verdict | Original interleavings | Filtered interleavings | Candidate globals | Unknowns |
| --- | --- | --- | ---: | ---: | --- | --- |
| icbmc-large | blink | no_injection_false | 2 | 0 | AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;...(+3 more) | external_call:memset;pointer_write |
| icbmc-large | blink-bug | no_injection_false | 2 | 0 | AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;...(+2 more) | external_call:memset;pointer_write |
| icbmc-large | blink-bug-conc | no_injection_false | 0 | 0 | AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;...(+11 more) | external_call:__VERIFIER_assume;external_call:__VERIFIER_atomic_begin;external_call:__VERIFIER_atomic_end;external_call:memset;...(+1 more) |
| icbmc-large | blink-conc | no_injection_false | 0 | 0 | AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;...(+11 more) | external_call:__VERIFIER_assume;external_call:__VERIFIER_atomic_begin;external_call:__VERIFIER_atomic_end;external_call:memset;...(+1 more) |
| icbmc-large | rc-core | needs_manual_review | 3 | 0 |  | external_call:__class_register;external_call:__list_add;external_call:_raw_spin_lock;external_call:_raw_spin_unlock;...(+3 more) |
| icbmc-large | rc-core-bug | needs_manual_review | 3 | 0 |  | external_call:__class_register;external_call:__list_add;external_call:_raw_spin_lock;external_call:_raw_spin_unlock;...(+3 more) |
| intabs-large | rcmain | needs_manual_review | 5 | 0 |  | external_call:__class_register;external_call:__list_add;external_call:_raw_spin_lock;external_call:_raw_spin_unlock;...(+3 more) |
| icbmc-timeout-30m-blink-highmem | blink-bug-seq | no_injection_false | 2 | 0 | AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;...(+10 more) | external_call:__VERIFIER_assume;external_call:__VERIFIER_nondet_bool;external_call:__VERIFIER_nondet_int;external_call:memset;...(+1 more) |
| icbmc-timeout-30m-blink-highmem | blink-seq | no_injection_false | 2 | 0 | AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;...(+10 more) | external_call:__VERIFIER_assume;external_call:__VERIFIER_nondet_bool;external_call:__VERIFIER_nondet_int;external_call:memset;...(+1 more) |

### Output Mismatch Audit Details

This table gives evidence for stock/improved output disagreements.

Column guide:

| Column | Meaning |
| --- | --- |
| `Category` | Diagnostic category describing the output mismatch. |
| `Suite` | Suite containing the audited case. |
| `Case` | Case whose stock and improved outputs differ. |
| `Stock output` | Verification summary produced by stock CBMC modeling. |
| `Improved output` | Verification summary produced by the improved pipeline. |
| `Verdict` | Audit verdict for the disagreement. |
| `Correct output` | Which output is judged correct after audit. |
| `Reason` | Compact evidence supporting the audit verdict. |

| Category | Suite | Case | Stock output | Improved output | Verdict | Correct output | Reason |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Verification Failed vs Successful | icbmc-large | brake2-1-bug-po | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | pending_manual_review | unknown | No verdict rule matched this case. |
| Verification Failed vs Successful | icbmc-large | brake2-1-po | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | pending_manual_review | unknown | No verdict rule matched this case. |
| Verification Failed vs Successful | icbmc-large | brake2-2-bug-po | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | pending_manual_review | unknown | No verdict rule matched this case. |
| Verification Failed vs Successful | icbmc-large | brake2-2-po | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | pending_manual_review | unknown | No verdict rule matched this case. |
| Verification Failed vs Successful | icbmc-large | brake2-3-bug-po | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | pending_manual_review | unknown | No verdict rule matched this case. |
| Verification Failed vs Successful | icbmc-large | brake2-3-po | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | pending_manual_review | unknown | No verdict rule matched this case. |
| Verification Failed vs Successful | icbmc-timeout-30m-logger-stable | logger2-bug-conc-cprover | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | improved_correct | improved | Stock C_ASYNC_PROVER exposes an interleaving through task_measure that violates numberOfRecords==pos+1; improved checks the extracted ISR/task body as one atomic entry, matching the benchmark ISR-atomic contract. |
| Verification Failed vs Successful | intabs-large | i8xx-tco-1 | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | improved_correct | improved | Improved keeps ISR/task entry atomic and has filtered interleavings 3/3; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-1__evidence/i8xx-tco-1/measure-1/stock_cprover_async/main.c function closer2 line 722 thread 3 assertion 0 0 != 0. |
| Verification Failed vs Successful | intabs-large | i8xx-tco-2 | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | improved_correct | improved | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-2__evidence/i8xx-tco-2/measure-1/stock_cprover_async/main.c function closer2 line 739 thread 2 assertion 0 0 != 0. |
| Verification Failed vs Successful | intabs-large | i8xx-tco-3 | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | improved_correct | improved | Improved keeps ISR/task entry atomic and has filtered interleavings 6/6; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-3__evidence/i8xx-tco-3/measure-1/stock_cprover_async/main.c function closer3 line 749 thread 3 assertion 0 0 != 0. |
| Verification Failed vs Successful | intabs-large | i8xx-tco-src-2 | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | improved_correct | improved | Improved keeps ISR/task entry atomic and has filtered interleavings 21/21; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-src-2__evidence/i8xx-tco-src-2/measure-1/stock_cprover_async/main.c function closer2 line 732 thread 2 assertion 0 0 != 0. |
| Verification Failed vs Successful | intabs-large | i8xx-tco-src-3 | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | improved_correct | improved | Improved keeps ISR/task entry atomic and has filtered interleavings 23/23; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-src-3__evidence/i8xx-tco-src-3/measure-1/stock_cprover_async/main.c function closer2 line 732 thread 2 assertion 0 0 != 0. |
| Verification Failed vs Successful | intabs-large | wdt-pci-1 | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | improved_correct | improved | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__wdt-pci-1__evidence/wdt-pci-1/measure-1/stock_cprover_async/main.c function closer1 line 973 thread 3 assertion 0 0 != 0. |
| Verification Failed vs Successful | intabs-large | wdt-pci-src-1 | VERIFICATION FAILED | VERIFICATION SUCCESSFUL | improved_correct | improved | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__wdt-pci-src-1__evidence/wdt-pci-src-1/measure-1/stock_cprover_async/main.c function closer2 line 1002 thread 4 assertion 0 0 != 0. |
| Verification Successful vs Failed | intabs-large | sc1200wdt-2 | VERIFICATION SUCCESSFUL | VERIFICATION FAILED | pending_manual_review | unknown | No verdict rule matched this case. |
| Verification Successful vs Failed | intabs-large | sc520wdt-2 | VERIFICATION SUCCESSFUL | VERIFICATION FAILED | improved_correct | improved | Improved injected closer/writer interleavings and reaches Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__sc520wdt-2__evidence/sc520wdt-2/measure-1/improved_pipeline/isr_define/isr.c function closer line 840 thread 0 assertion dev_open dev_open != FALSE; stock baseline proves without that injected ISR ordering. |
| Verification Successful vs Failed | local-smoke | t-isr-multifile | VERIFICATION SUCCESSFUL | VERIFICATION FAILED | improved_correct | improved | Improved trace reaches injected ISR/task perturbation; simple benchmark docs expect the injected pipeline to fail. |

### Diagnostic Details

This table lists each diagnostic case with the stock output, improved output, and comparison reason.

Column guide:

| Column | Meaning |
| --- | --- |
| `Suite` | Suite containing the diagnostic case. |
| `Case` | Case whose output is diagnostic rather than a clean same-output comparison. |
| `Stock output` | Normalized verification outcome for the stock variant. |
| `Improved output` | Normalized verification outcome for the improved variant. |
| `Reason` | Why the case is diagnostic or how to rerun disabled evidence. |

#### Verification Failed vs Successful

| Suite | Case | Stock output | Improved output | Reason |
| --- | --- | --- | --- | --- |
| icbmc-large | brake2-1-bug-po | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| icbmc-large | brake2-1-po | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| icbmc-large | brake2-2-bug-po | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| icbmc-large | brake2-2-po | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| icbmc-large | brake2-3-bug-po | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| icbmc-large | brake2-3-po | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| icbmc-timeout-30m | logger2-bug-conc-cprover | failed | success | Not comparable: verification outcomes differ (failed vs success). Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed. |
| icbmc-timeout-30m-logger-stable | logger2-bug-conc-cprover | failed | success | Not comparable: verification outcomes differ (failed vs success). Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed. |
| intabs-large | i8xx-tco-1 | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| intabs-large | i8xx-tco-2 | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| intabs-large | i8xx-tco-3 | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| intabs-large | i8xx-tco-src-2 | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| intabs-large | i8xx-tco-src-3 | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| intabs-large | wdt-pci-1 | failed | success | Not comparable: verification outcomes differ (failed vs success). |
| intabs-large | wdt-pci-src-1 | failed | success | Not comparable: verification outcomes differ (failed vs success). |

#### Verification Successful vs Failed

| Suite | Case | Stock output | Improved output | Reason |
| --- | --- | --- | --- | --- |
| intabs-large | sc1200wdt-2 | success | failed | Not comparable: verification outcomes differ (success vs failed). |
| intabs-large | sc520wdt-2 | success | failed | Not comparable: verification outcomes differ (success vs failed). |
| local-smoke | t-isr-multifile | success | failed | Not comparable: verification outcomes differ (success vs failed). |

#### CBMC Unsupported Concurrency

| Suite | Case | Stock output | Improved output | Reason |
| --- | --- | --- | --- | --- |
| trampoline-current | trampoline-alarms-s1-non | unsupported | failed | Not comparable: stock CBMC reports unsupported concurrency. |
| trampoline-expanded | trampoline-expanded-alarms-s1-non-full-source | unsupported | failed | Not comparable: stock CBMC reports unsupported concurrency. |

#### Stock Memory Limit

| Suite | Case | Stock output | Improved output | Reason |
| --- | --- | --- | --- | --- |
| icbmc-timeout-30m-blink-highmem | blink-bug-seq | memory_limit | exit_6 | Not comparable: stock verification hit the memory limit. Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed. |
| icbmc-timeout-30m-blink-highmem | blink-seq | memory_limit | exit_6 | Not comparable: stock verification hit the memory limit. Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed. |

#### No Injection Candidates

| Suite | Case | Stock output | Improved output | Reason |
| --- | --- | --- | --- | --- |
| icbmc-large | blink | exit_6 | exit_6 | Not comparable: improved variant had no injection candidates. |
| icbmc-large | blink-bug | exit_6 | exit_6 | Not comparable: improved variant had no injection candidates. |
| icbmc-large | blink-bug-conc | success | success | Not comparable: improved variant had no injection candidates. |
| icbmc-large | blink-conc | success | success | Not comparable: improved variant had no injection candidates. |
| icbmc-large | rc-core | exit_6 | exit_6 | Not comparable: improved variant had no injection candidates. |
| icbmc-large | rc-core-bug | exit_6 | exit_6 | Not comparable: improved variant had no injection candidates. |
| intabs-large | rcmain | unsupported | success | Not comparable: improved variant had no injection candidates. |

#### Not Run / Disabled Cases

| Suite | Case | Stock output | Improved output | Reason |
| --- | --- | --- | --- | --- |
| icbmc-large | blink-bug-seq | missing | missing | Not run: Disabled after 30-minute review: stock verification reaches the available 14000 MB RSS cap before timeout and the improved pipeline has no injection candidates. |
| icbmc-large | blink-seq | missing | missing | Not run: Disabled after 30-minute review: stock verification reaches the available 14000 MB RSS cap before timeout and the improved pipeline has no injection candidates. |
| icbmc-large | logger | missing | missing | Not run: Normalized as a control case but below the large-case LOC gate; do not use as a headline i-CBMC result. |
| icbmc-large | logger-bug | missing | missing | Not run: Normalized as a control case but below the large-case LOC gate; do not use as a headline i-CBMC result. |
| icbmc-large | logger2-bug-conc | missing | missing | Not run: Disabled after 30-minute review: stock verification fails while improved verification exits with code 6; retained as staged Logger2 coverage. |
| icbmc-large | logger2-bug-conc-cprover | missing | missing | Not run: Disabled after 30-minute review: stock verification fails while improved verification exits with code 6; improved ISR entries were normalized to whole-function atomic regions. |
| icbmc-large | logger2-conc | missing | missing | Not run: Disabled after 30-minute review: stock verification fails while improved verification exits with code 6; retained as staged Logger2 coverage. |
| icbmc-large | logger2-conc-cprover | missing | missing | Not run: Disabled after 30-minute review: stock verification fails while improved verification exits with code 6; improved ISR entries were normalized to whole-function atomic regions. |
| icbmc-large | rc-core-bug-conc | missing | missing | Not run: Disabled during Phase 5 hardening: the improved source retains active pthread launches and reports no injection candidates. |
| icbmc-large | rc-core-bug-conc-cprover | missing | missing | Not run: Disabled during Phase 5 hardening: extracted ISR functions are not atomic from function entry and the improved pipeline reports no injection candidates. |
| icbmc-large | rc-core-conc | missing | missing | Not run: Disabled during Phase 5 hardening: the improved source retains active pthread launches and reports no injection candidates. |
| icbmc-large | rc-core-conc-cprover | missing | missing | Not run: Disabled during Phase 5 hardening: extracted ISR functions are not atomic from function entry and the improved pipeline reports no injection candidates. |
| icbmc-timeout-30m | blink-bug-seq | missing | missing | No measured CSV rows are available yet. Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed. |
| icbmc-timeout-30m | blink-seq | missing | missing | No measured CSV rows are available yet. Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed. |
| intabs-large | logger2 | missing | missing | Not run: Legacy normalized control case; disabled because the stock tree has no CPROVER async modeling and the original upstream source metadata was not recorded. |
| intabs-large | logger3 | missing | missing | Not run: Normalized as a control case but below the large-case LOC gate; do not use as a headline IntAbs result. |
| local-smoke | t-interleaving | missing | missing | Not run: Non-ISR smoke input kept documented; enable after defining ISR entry points. |
| local-smoke | t-isr-added-single-file | missing | missing | Not run: Legacy pre-injected single-file smoke input was removed; kept only as historical report context. |
| local-smoke | t-isr-single-file | missing | missing | Not run: Legacy single-file smoke input was removed; kept only as historical report context. |
| osek-local | osek-event-basic | missing | missing | Not run: Regression case has no dedicated ISR source yet; tracked for future harness normalization. |
| osek-local | osek-event-multi-bits | missing | missing | Not run: Regression case has no dedicated ISR source yet; tracked for future harness normalization. |
| osek-local | osek-event-wait-block | missing | missing | Not run: Regression case has no dedicated ISR source yet; tracked for future harness normalization. |
| osek-local | osek-event-wait-noblock | missing | missing | Not run: Regression case has no dedicated ISR source yet; tracked for future harness normalization. |

#### Other Verification Outcome Mismatches

| Suite | Case | Stock output | Improved output | Reason |
| --- | --- | --- | --- | --- |
| osek-local | osek-event-interleaving | exit_64 | failed | Not comparable: verification outcomes differ (exit_64 vs failed). |
| osek-local | osek-priority-interleaving | exit_64 | failed | Not comparable: verification outcomes differ (exit_64 vs failed). |

## Per-Suite Case Measurements

Each case subsection contains per-phase measurements, correctness fields, and performance deltas. Phase tables show runs, exits, median time, peak RSS, and summaries; correctness tables show stock/improved outputs and audit judgment; metric tables compare full measured time and peak RSS.

### icbmc-large

#### blink

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 306 | 14.8 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 172 | 14.8 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 349 | 16.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 568 | 15.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 471 | 20.0 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Field | Value |
| --- | --- |
| Stock output | `exit_6` |
| Improved output | `exit_6` |
| Correct output | `unknown` |
| Correctness verdict | `no_injection_false` |
| Reason | candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;...(+4 more) |

Correctness audit: `no_injection_false`; action: `fix ISR source-effect metadata or insertion-site manifest before comparing`. candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;TransformAlarmC_0_m_dt;...(+2 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 478 ms | 1388 ms | improved is 190.4% slower |
| Peak RSS | 14.8 MB | 20.0 MB | improved uses 35.1% more RAM |

#### blink-bug

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 334 | 14.5 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 578 | 14.7 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 547 | 16.1 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 966 | 16.1 | `OK` |
| Improved pipeline | verify | 5 | 6 | 698 | 19.7 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Field | Value |
| --- | --- |
| Stock output | `exit_6` |
| Improved output | `exit_6` |
| Correct output | `unknown` |
| Correctness verdict | `no_injection_false` |
| Reason | candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;...(+4 more) |

Correctness audit: `no_injection_false`; action: `fix ISR source-effect metadata or insertion-site manifest before comparing`. candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;TransformAlarmC_0_m_dt;...(+1 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 912 ms | 2211 ms | improved is 142.4% slower |
| Peak RSS | 14.7 MB | 19.7 MB | improved uses 34.0% more RAM |

#### blink-bug-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 493 | 16.6 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 1993 | 53.4 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 917 | 18.0 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 1133 | 17.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 529 | 18.4 | `VERIFICATION SUCCESSFUL` |

Not comparable: improved variant had no injection candidates.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `no_injection_false` |
| Reason | candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;...(+4 more) |

Correctness audit: `no_injection_false`; action: `fix ISR source-effect metadata or insertion-site manifest before comparing`. candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;TransformAlarmC_0_m_dt;...(+10 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 2486 ms | 2579 ms | improved is 3.7% slower |
| Peak RSS | 53.4 MB | 18.4 MB | improved uses 65.5% less RAM |

#### blink-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 587 | 17.2 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 1875 | 56.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1225 | 18.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 1043 | 18.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 430 | 18.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: improved variant had no injection candidates.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `no_injection_false` |
| Reason | candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;...(+4 more) |

Correctness audit: `no_injection_false`; action: `fix ISR source-effect metadata or insertion-site manifest before comparing`. candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;TransformAlarmC_0_m_dt;...(+10 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 2462 ms | 2698 ms | improved is 9.6% slower |
| Peak RSS | 56.8 MB | 18.8 MB | improved uses 66.9% less RAM |

#### brake2-1-bug-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 1000 | 15.0 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 2299 | 152.9 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 915 | 16.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 517 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 987 | 16.4 | `OK` |
| Improved pipeline | verify | 5 | 0 | 554 | 18.0 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `pending_manual_review` |
| Reason | No verdict rule matched this case. |

Correctness audit: `pending_manual_review`; correct variant: `unknown`; action: `inspect_trace`. No verdict rule matched this case.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 3299 ms | 2973 ms | improved is 9.9% faster |
| Peak RSS | 152.9 MB | 18.0 MB | improved uses 88.2% less RAM |

#### brake2-1-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 403 | 13.6 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 2277 | 148.2 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1254 | 15.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 568 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1002 | 15.4 | `OK` |
| Improved pipeline | verify | 5 | 0 | 377 | 17.7 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `pending_manual_review` |
| Reason | No verdict rule matched this case. |

Correctness audit: `pending_manual_review`; correct variant: `unknown`; action: `inspect_trace`. No verdict rule matched this case.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 2680 ms | 3201 ms | improved is 19.4% slower |
| Peak RSS | 148.2 MB | 17.7 MB | improved uses 88.1% less RAM |

#### brake2-2-bug-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 444 | 14.8 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 4068 | 233.6 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1603 | 16.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 549 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 717 | 16.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 596 | 18.0 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `pending_manual_review` |
| Reason | No verdict rule matched this case. |

Correctness audit: `pending_manual_review`; correct variant: `unknown`; action: `inspect_trace`. No verdict rule matched this case.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 4512 ms | 3465 ms | improved is 23.2% faster |
| Peak RSS | 233.6 MB | 18.0 MB | improved uses 92.3% less RAM |

#### brake2-2-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 511 | 13.4 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 10319 | 220.8 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1199 | 15.6 | `OK` |
| Improved pipeline | inject | 5 | 0 | 669 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1192 | 15.4 | `OK` |
| Improved pipeline | verify | 5 | 0 | 373 | 17.7 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `pending_manual_review` |
| Reason | No verdict rule matched this case. |

Correctness audit: `pending_manual_review`; correct variant: `unknown`; action: `inspect_trace`. No verdict rule matched this case.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 10830 ms | 3433 ms | improved is 68.3% faster |
| Peak RSS | 220.8 MB | 17.7 MB | improved uses 92.0% less RAM |

#### brake2-3-bug-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 475 | 14.9 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 4746 | 291.7 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 781 | 16.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 707 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1039 | 16.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 437 | 18.1 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `pending_manual_review` |
| Reason | No verdict rule matched this case. |

Correctness audit: `pending_manual_review`; correct variant: `unknown`; action: `inspect_trace`. No verdict rule matched this case.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 5221 ms | 2964 ms | improved is 43.2% faster |
| Peak RSS | 291.7 MB | 18.1 MB | improved uses 93.8% less RAM |

#### brake2-3-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 525 | 13.4 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 4658 | 265.3 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1249 | 15.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 744 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1026 | 15.3 | `OK` |
| Improved pipeline | verify | 5 | 0 | 475 | 17.7 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `pending_manual_review` |
| Reason | No verdict rule matched this case. |

Correctness audit: `pending_manual_review`; correct variant: `unknown`; action: `inspect_trace`. No verdict rule matched this case.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 5183 ms | 3494 ms | improved is 32.6% faster |
| Peak RSS | 265.3 MB | 17.7 MB | improved uses 93.3% less RAM |

#### rc-core

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 466 | 34.6 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 527 | 30.6 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 919 | 35.9 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 1125 | 35.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 1224 | 32.2 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Field | Value |
| --- | --- |
| Stock output | `exit_6` |
| Improved output | `exit_6` |
| Correct output | `unknown` |
| Correctness verdict | `needs_manual_review` |
| Reason | unknowns: external_call:__class_register;external_call:__list_add;...(+4 more) |

Correctness audit: `needs_manual_review`; action: `inspect unresolved ISR/global reachability before comparing`. unknowns: external_call:__class_register;external_call:__list_add;external_call:_raw_spin_lock;external_call:_raw_spin_unlock;external_call:class_unregister;...(+2 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 993 ms | 3268 ms | improved is 229.1% slower |
| Peak RSS | 34.6 MB | 35.9 MB | improved uses 3.8% more RAM |

#### rc-core-bug

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 639 | 34.4 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 478 | 30.7 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 880 | 36.1 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 883 | 35.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 1285 | 32.2 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Field | Value |
| --- | --- |
| Stock output | `exit_6` |
| Improved output | `exit_6` |
| Correct output | `unknown` |
| Correctness verdict | `needs_manual_review` |
| Reason | unknowns: external_call:__class_register;external_call:__list_add;...(+4 more) |

Correctness audit: `needs_manual_review`; action: `inspect unresolved ISR/global reachability before comparing`. unknowns: external_call:__class_register;external_call:__list_add;external_call:_raw_spin_lock;external_call:_raw_spin_unlock;external_call:class_unregister;...(+2 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1117 ms | 3048 ms | improved is 172.9% slower |
| Peak RSS | 34.4 MB | 36.1 MB | improved uses 4.9% more RAM |

### icbmc-timeout-30m

#### logger2-bug-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 310 | 14.3 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 35971 | 262.3 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 338 | 13.9 | `OK` |
| Improved pipeline | inject | 1 | 0 | 336 | 3.8 | `OK` |
| Improved pipeline | compile | 1 | 0 | 926 | 13.7 | `OK` |
| Improved pipeline | verify | 1 | 0 | 126 | 16.1 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 36281 ms | 1726 ms | improved is 95.2% faster |
| Peak RSS | 262.3 MB | 16.1 MB | improved uses 93.9% less RAM |

#### logger2-bug-conc-cprover

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 360 | 14.4 | `OK` |
| Stock CPROVER async | verify | 1 | 10 | 55873 | 298.2 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 1 | 0 | 1072 | 13.9 | `OK` |
| Improved pipeline | inject | 1 | 0 | 470 | 3.6 | `OK` |
| Improved pipeline | compile | 1 | 0 | 329 | 14.0 | `OK` |
| Improved pipeline | verify | 1 | 0 | 146 | 16.6 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Stock C_ASYNC_PROVER exposes an interleaving through task_measure that violates numberOfRecords==pos+1; improved checks the extracted ISR/task body as one atomic entry, matching the benchmark ISR-atomic contract. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 56233 ms | 2017 ms | improved is 96.4% faster |
| Peak RSS | 298.2 MB | 16.6 MB | improved uses 94.4% less RAM |

#### logger2-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 330 | 14.8 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 36038 | 262.2 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 454 | 13.0 | `OK` |
| Improved pipeline | inject | 1 | 0 | 578 | 3.8 | `OK` |
| Improved pipeline | compile | 1 | 0 | 408 | 14.1 | `OK` |
| Improved pipeline | verify | 1 | 0 | 132 | 16.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 36368 ms | 1572 ms | improved is 95.7% faster |
| Peak RSS | 262.2 MB | 16.6 MB | improved uses 93.7% less RAM |

#### logger2-conc-cprover

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 248 | 13.9 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 89165 | 381.2 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 718 | 13.1 | `OK` |
| Improved pipeline | inject | 1 | 0 | 491 | 3.8 | `OK` |
| Improved pipeline | compile | 1 | 0 | 501 | 13.8 | `OK` |
| Improved pipeline | verify | 1 | 0 | 169 | 16.2 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 89413 ms | 1879 ms | improved is 97.9% faster |
| Peak RSS | 381.2 MB | 16.2 MB | improved uses 95.8% less RAM |

### icbmc-timeout-30m-blink-highmem

#### blink-bug-seq

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 246 | 15.6 | `OK` |
| Stock CPROVER async | verify | 1 | -9 | 1243245 | 14000.0 | `MEMORY_LIMIT_EXCEEDED_14000MB` |
| Improved pipeline | manifest | 1 | 0 | 246 | 16.4 | `OK` |
| Improved pipeline | inject | 1 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 1 | 0 | 228 | 16.4 | `OK` |
| Improved pipeline | verify | 1 | 6 | 134 | 17.3 | `EXIT_6` |

Not comparable: stock verification hit the memory limit.

| Field | Value |
| --- | --- |
| Stock output | `memory_limit` |
| Improved output | `exit_6` |
| Correct output | `unknown` |
| Correctness verdict | `no_injection_false` |
| Reason | candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;...(+4 more) |

Correctness audit: `no_injection_false`; action: `fix ISR source-effect metadata or insertion-site manifest before comparing`. candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;TransformAlarmC_0_m_dt;...(+9 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1243491 ms | 608 ms | improved is 100.0% faster |
| Peak RSS | 14000.0 MB | 17.3 MB | improved uses 99.9% less RAM |

#### blink-seq

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 307 | 16.6 | `OK` |
| Stock CPROVER async | verify | 1 | -9 | 1221497 | 14000.2 | `MEMORY_LIMIT_EXCEEDED_14000MB` |
| Improved pipeline | manifest | 1 | 0 | 246 | 16.1 | `OK` |
| Improved pipeline | inject | 1 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 1 | 0 | 226 | 16.4 | `OK` |
| Improved pipeline | verify | 1 | 6 | 123 | 17.3 | `EXIT_6` |

Not comparable: stock verification hit the memory limit.

| Field | Value |
| --- | --- |
| Stock output | `memory_limit` |
| Improved output | `exit_6` |
| Correct output | `unknown` |
| Correctness verdict | `no_injection_false` |
| Reason | candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;...(+4 more) |

Correctness audit: `no_injection_false`; action: `fix ISR source-effect metadata or insertion-site manifest before comparing`. candidate globals: AlarmToTimerC_0_m_dt;AlarmToTimerC_0_m_oneshot;SchedulerBasicP_m_head;SchedulerBasicP_m_tail;TransformAlarmC_0_m_dt;...(+9 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1221804 ms | 595 ms | improved is 100.0% faster |
| Peak RSS | 14000.2 MB | 17.3 MB | improved uses 99.9% less RAM |

### icbmc-timeout-30m-logger-stable

#### logger2-bug-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 539 | 14.5 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 36345 | 262.1 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 922 | 13.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 402 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 640 | 14.1 | `OK` |
| Improved pipeline | verify | 5 | 0 | 551 | 16.2 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 36884 ms | 2515 ms | improved is 93.2% faster |
| Peak RSS | 262.1 MB | 16.2 MB | improved uses 93.8% less RAM |

#### logger2-bug-conc-cprover

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 318 | 14.3 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 54666 | 297.4 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 696 | 13.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 470 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 499 | 14.1 | `OK` |
| Improved pipeline | verify | 5 | 0 | 360 | 16.1 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Stock C_ASYNC_PROVER exposes an interleaving through task_measure that violates numberOfRecords==pos+1; improved checks the extracted ISR/task body as one atomic entry, matching the benchmark ISR-atomic contract. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_non_atomic_async_interleaving`. Stock C_ASYNC_PROVER exposes an interleaving through task_measure that violates numberOfRecords==pos+1; improved checks the extracted ISR/task body as one atomic entry, matching the benchmark ISR-atomic contract.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 54984 ms | 2025 ms | improved is 96.3% faster |
| Peak RSS | 297.4 MB | 16.1 MB | improved uses 94.6% less RAM |

#### logger2-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 309 | 14.3 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 35914 | 262.4 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1287 | 13.8 | `OK` |
| Improved pipeline | inject | 5 | 0 | 188 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 693 | 14.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 318 | 16.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 36223 ms | 2486 ms | improved is 93.1% faster |
| Peak RSS | 262.4 MB | 16.4 MB | improved uses 93.8% less RAM |

#### logger2-conc-cprover

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 315 | 13.9 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 89930 | 381.4 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 580 | 13.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 188 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 724 | 13.6 | `OK` |
| Improved pipeline | verify | 5 | 0 | 369 | 16.2 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 90245 ms | 1861 ms | improved is 97.9% faster |
| Peak RSS | 381.4 MB | 16.2 MB | improved uses 95.8% less RAM |

### intabs-large

#### i8xx-tco-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 847 | 9.5 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 355 | 13.1 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1206 | 11.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 410 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1344 | 11.6 | `OK` |
| Improved pipeline | verify | 5 | 0 | 435 | 15.3 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved keeps ISR/task entry atomic and has filtered interleavings 3/3; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-1__evidence/i8xx-tco-1/measure-1/stock_cprover_async/main.c function closer2 line 722 thread 3 assertion 0 0 != 0. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads`. Improved keeps ISR/task entry atomic and has filtered interleavings 3/3; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-1__evidence/i8xx-tco-1/measure-1/stock_cprover_async/main.c function closer2 line 722 thread 3 assertion 0 0 != 0.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1202 ms | 3395 ms | improved is 182.4% slower |
| Peak RSS | 13.1 MB | 15.3 MB | improved uses 16.8% more RAM |

#### i8xx-tco-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 622 | 10.5 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 365 | 15.3 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1146 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 408 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1493 | 13.6 | `OK` |
| Improved pipeline | verify | 5 | 0 | 807 | 19.1 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-2__evidence/i8xx-tco-2/measure-1/stock_cprover_async/main.c function closer2 line 739 thread 2 assertion 0 0 != 0. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads`. Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-2__evidence/i8xx-tco-2/measure-1/stock_cprover_async/main.c function closer2 line 739 thread 2 assertion 0 0 != 0.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 987 ms | 3854 ms | improved is 290.5% slower |
| Peak RSS | 15.3 MB | 19.1 MB | improved uses 24.8% more RAM |

#### i8xx-tco-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 616 | 10.8 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 393 | 15.9 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1280 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 519 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1687 | 14.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 618 | 19.2 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved keeps ISR/task entry atomic and has filtered interleavings 6/6; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-3__evidence/i8xx-tco-3/measure-1/stock_cprover_async/main.c function closer3 line 749 thread 3 assertion 0 0 != 0. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads`. Improved keeps ISR/task entry atomic and has filtered interleavings 6/6; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-3__evidence/i8xx-tco-3/measure-1/stock_cprover_async/main.c function closer3 line 749 thread 3 assertion 0 0 != 0.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1009 ms | 4104 ms | improved is 306.7% slower |
| Peak RSS | 15.9 MB | 19.2 MB | improved uses 20.8% more RAM |

#### i8xx-tco-src-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 459 | 10.8 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 360 | 15.5 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1535 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 778 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1253 | 16.5 | `OK` |
| Improved pipeline | verify | 5 | 0 | 416 | 19.5 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved keeps ISR/task entry atomic and has filtered interleavings 21/21; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-src-2__evidence/i8xx-tco-src-2/measure-1/stock_cprover_async/main.c function closer2 line 732 thread 2 assertion 0 0 != 0. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads`. Improved keeps ISR/task entry atomic and has filtered interleavings 21/21; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-src-2__evidence/i8xx-tco-src-2/measure-1/stock_cprover_async/main.c function closer2 line 732 thread 2 assertion 0 0 != 0.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 819 ms | 3982 ms | improved is 386.2% slower |
| Peak RSS | 15.5 MB | 19.5 MB | improved uses 25.8% more RAM |

#### i8xx-tco-src-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 681 | 10.9 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 322 | 17.7 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1422 | 12.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 949 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1026 | 17.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 694 | 19.7 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved keeps ISR/task entry atomic and has filtered interleavings 23/23; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-src-3__evidence/i8xx-tco-src-3/measure-1/stock_cprover_async/main.c function closer2 line 732 thread 2 assertion 0 0 != 0. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads`. Improved keeps ISR/task entry atomic and has filtered interleavings 23/23; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__i8xx-tco-src-3__evidence/i8xx-tco-src-3/measure-1/stock_cprover_async/main.c function closer2 line 732 thread 2 assertion 0 0 != 0.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1003 ms | 4091 ms | improved is 307.9% slower |
| Peak RSS | 17.7 MB | 19.7 MB | improved uses 11.3% more RAM |

#### rcmain

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 586 | 33.7 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 682 | 30.7 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 1220 | 36.1 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 878 | 35.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 1250 | 31.5 | `VERIFICATION SUCCESSFUL` |

Not comparable: improved variant had no injection candidates.

| Field | Value |
| --- | --- |
| Stock output | `unsupported` |
| Improved output | `success` |
| Correct output | `unknown` |
| Correctness verdict | `needs_manual_review` |
| Reason | unknowns: external_call:__class_register;external_call:__list_add;...(+4 more) |

Correctness audit: `needs_manual_review`; action: `inspect unresolved ISR/global reachability before comparing`. unknowns: external_call:__class_register;external_call:__list_add;external_call:_raw_spin_lock;external_call:_raw_spin_unlock;external_call:class_unregister;...(+2 more)

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1268 ms | 3348 ms | improved is 164.0% slower |
| Peak RSS | 33.7 MB | 36.1 MB | improved uses 7.1% more RAM |

#### sc1200wdt-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 521 | 9.7 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 392 | 12.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 559 | 12.0 | `OK` |
| Improved pipeline | inject | 5 | 0 | 999 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1397 | 12.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 338 | 15.8 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 913 ms | 3293 ms | improved is 260.7% slower |
| Peak RSS | 12.8 MB | 15.8 MB | improved uses 23.4% more RAM |

#### sc1200wdt-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 899 | 9.7 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 335 | 13.0 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1646 | 11.9 | `OK` |
| Improved pipeline | inject | 5 | 0 | 282 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1230 | 12.0 | `OK` |
| Improved pipeline | verify | 5 | 10 | 474 | 15.9 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `failed` |
| Correct output | `unknown` |
| Correctness verdict | `pending_manual_review` |
| Reason | No verdict rule matched this case. |

Correctness audit: `pending_manual_review`; correct variant: `unknown`; action: `inspect_trace`. No verdict rule matched this case.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1234 ms | 3632 ms | improved is 194.3% slower |
| Peak RSS | 13.0 MB | 15.9 MB | improved uses 22.3% more RAM |

#### sc520wdt-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 707 | 10.8 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 361 | 14.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1616 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 520 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1734 | 12.3 | `OK` |
| Improved pipeline | verify | 5 | 0 | 416 | 15.5 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1068 ms | 4286 ms | improved is 301.3% slower |
| Peak RSS | 14.8 MB | 15.5 MB | improved uses 4.7% more RAM |

#### sc520wdt-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 210 | 12.9 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 962 | 41.0 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1370 | 14.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 512 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1154 | 14.3 | `OK` |
| Improved pipeline | verify | 5 | 10 | 523 | 16.7 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `failed` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved injected closer/writer interleavings and reaches Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__sc520wdt-2__evidence/sc520wdt-2/measure-1/improved_pipeline/isr_define/isr.c function closer line 840 thread 0 assertion dev_open dev_open != FALSE; stock baseline proves without that injected ISR ordering. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_model_too_weak`. Improved injected closer/writer interleavings and reaches Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__sc520wdt-2__evidence/sc520wdt-2/measure-1/improved_pipeline/isr_define/isr.c function closer line 840 thread 0 assertion dev_open dev_open != FALSE; stock baseline proves without that injected ISR ordering.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1172 ms | 3559 ms | improved is 203.7% slower |
| Peak RSS | 41.0 MB | 16.7 MB | improved uses 59.3% less RAM |

#### wdt-pci-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 597 | 9.8 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 246 | 14.5 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1473 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 573 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1603 | 13.0 | `OK` |
| Improved pipeline | verify | 5 | 0 | 515 | 15.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__wdt-pci-1__evidence/wdt-pci-1/measure-1/stock_cprover_async/main.c function closer1 line 973 thread 3 assertion 0 0 != 0. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads`. Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__wdt-pci-1__evidence/wdt-pci-1/measure-1/stock_cprover_async/main.c function closer1 line 973 thread 3 assertion 0 0 != 0.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 843 ms | 4164 ms | improved is 394.0% slower |
| Peak RSS | 14.5 MB | 15.8 MB | improved uses 9.0% more RAM |

#### wdt-pci-1-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 738 | 10.5 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 282 | 15.3 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1444 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1304 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1264 | 13.0 | `OK` |
| Improved pipeline | verify | 5 | 0 | 422 | 18.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1020 ms | 4434 ms | improved is 334.7% slower |
| Peak RSS | 15.3 MB | 18.6 MB | improved uses 21.6% more RAM |

#### wdt-pci-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 876 | 10.6 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 324 | 10.9 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1832 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 557 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1534 | 12.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 542 | 15.9 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1200 ms | 4465 ms | improved is 272.1% slower |
| Peak RSS | 10.9 MB | 15.9 MB | improved uses 45.9% more RAM |

#### wdt-pci-2-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 187 | 10.6 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 126 | 14.7 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 572 | 12.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 289 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 350 | 13.0 | `OK` |
| Improved pipeline | verify | 5 | 0 | 209 | 18.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 313 ms | 1420 ms | improved is 353.7% slower |
| Peak RSS | 14.7 MB | 18.6 MB | improved uses 26.5% more RAM |

#### wdt-pci-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 738 | 11.2 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 391 | 14.5 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 793 | 13.0 | `OK` |
| Improved pipeline | inject | 5 | 0 | 559 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1917 | 12.7 | `OK` |
| Improved pipeline | verify | 5 | 6 | 616 | 16.6 | `EXIT_6` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `exit_6` |
| Improved output | `exit_6` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1129 ms | 3885 ms | improved is 244.1% slower |
| Peak RSS | 14.5 MB | 16.6 MB | improved uses 14.5% more RAM |

#### wdt-pci-3-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 249 | 10.0 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 168 | 14.7 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 713 | 12.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1329 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1587 | 13.0 | `OK` |
| Improved pipeline | verify | 5 | 0 | 478 | 18.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 417 ms | 4107 ms | improved is 884.9% slower |
| Peak RSS | 14.7 MB | 18.6 MB | improved uses 26.5% more RAM |

#### wdt-pci-src-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 804 | 10.3 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 622 | 16.1 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1829 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 476 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1739 | 12.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 455 | 18.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Field | Value |
| --- | --- |
| Stock output | `failed` |
| Improved output | `success` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__wdt-pci-src-1__evidence/wdt-pci-src-1/measure-1/stock_cprover_async/main.c function closer2 line 1002 thread 4 assertion 0 0 != 0. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_overapproximates_non_atomic_async_threads`. Improved keeps ISR/task entry atomic and has filtered interleavings 4/4; stock failure is an async-thread interleaving into Violated property: file /repo/check-src/benchmarks/work/audit/intabs-large__wdt-pci-src-1__evidence/wdt-pci-src-1/measure-1/stock_cprover_async/main.c function closer2 line 1002 thread 4 assertion 0 0 != 0.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1426 ms | 4499 ms | improved is 215.5% slower |
| Peak RSS | 16.1 MB | 18.8 MB | improved uses 16.8% more RAM |

#### wdt-pci-src-1-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 408 | 10.6 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 353 | 15.2 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 815 | 12.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1005 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 846 | 13.1 | `OK` |
| Improved pipeline | verify | 5 | 0 | 802 | 18.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 761 ms | 3468 ms | improved is 355.7% slower |
| Peak RSS | 15.2 MB | 18.6 MB | improved uses 22.4% more RAM |

#### wdt-pci-src-2-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 797 | 10.5 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 313 | 14.7 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1284 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1077 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1024 | 13.0 | `OK` |
| Improved pipeline | verify | 5 | 0 | 577 | 18.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1110 ms | 3962 ms | improved is 256.9% slower |
| Peak RSS | 14.7 MB | 18.6 MB | improved uses 26.5% more RAM |

#### wdt-pci-src-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 436 | 10.3 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 209 | 14.2 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1341 | 12.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 382 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1775 | 12.3 | `OK` |
| Improved pipeline | verify | 5 | 0 | 354 | 16.2 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 645 ms | 3852 ms | improved is 497.2% slower |
| Peak RSS | 14.2 MB | 16.2 MB | improved uses 14.1% more RAM |

#### wdt-pci-src-3-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 795 | 10.8 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 444 | 15.0 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1574 | 12.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1251 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 701 | 12.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 496 | 18.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `success` |
| Correct output | `both` |
| Correctness verdict | `same_outcome_comparable` |
| Reason | Comparable: both variants reached the same verification outcome. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1239 ms | 4022 ms | improved is 224.6% slower |
| Peak RSS | 15.0 MB | 18.4 MB | improved uses 22.7% more RAM |

### local-smoke

#### t-isr-multifile

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 288 | 7.3 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 67 | 8.0 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 227 | 9.8 | `OK` |
| Improved pipeline | inject | 1 | 0 | 435 | 3.8 | `OK` |
| Improved pipeline | compile | 1 | 0 | 595 | 10.0 | `OK` |
| Improved pipeline | verify | 1 | 10 | 227 | 15.8 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Field | Value |
| --- | --- |
| Stock output | `success` |
| Improved output | `failed` |
| Correct output | `improved` |
| Correctness verdict | `improved_correct` |
| Reason | Improved trace reaches injected ISR/task perturbation; simple benchmark docs expect the injected pipeline to fail. |

Correctness audit: `improved_correct`; correct variant: `improved_pipeline`; action: `keep_benchmark_diagnostic_stock_model_too_weak`. Improved trace reaches injected ISR/task perturbation; simple benchmark docs expect the injected pipeline to fail.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 355 ms | 1484 ms | improved is 318.0% slower |
| Peak RSS | 8.0 MB | 15.8 MB | improved uses 97.5% more RAM |

### osek-local

#### osek-event-interleaving

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 1180 | 5.5 | `OK` |
| Stock CPROVER async | verify | 1 | 64 | 146 | 6.1 | `EXIT_64` |
| Improved pipeline | manifest | 1 | 0 | 703 | 9.5 | `OK` |
| Improved pipeline | inject | 1 | 0 | 211 | 3.8 | `OK` |
| Improved pipeline | compile | 1 | 0 | 2928 | 10.0 | `OK` |
| Improved pipeline | verify | 1 | 10 | 600 | 15.5 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (exit_64 vs failed).

| Field | Value |
| --- | --- |
| Stock output | `exit_64` |
| Improved output | `failed` |
| Correct output | `unknown` |
| Correctness verdict | `needs_manual_review` |
| Reason | Not comparable: verification outcomes differ (exit_64 vs failed). |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1326 ms | 4442 ms | improved is 235.0% slower |
| Peak RSS | 6.1 MB | 15.5 MB | improved uses 154.1% more RAM |

#### osek-priority-interleaving

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 1479 | 6.7 | `OK` |
| Stock CPROVER async | verify | 1 | 64 | 229 | 5.8 | `EXIT_64` |
| Improved pipeline | manifest | 1 | 0 | 1144 | 9.5 | `OK` |
| Improved pipeline | inject | 1 | 0 | 890 | 3.8 | `OK` |
| Improved pipeline | compile | 1 | 0 | 2024 | 9.5 | `OK` |
| Improved pipeline | verify | 1 | 10 | 434 | 15.8 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (exit_64 vs failed).

| Field | Value |
| --- | --- |
| Stock output | `exit_64` |
| Improved output | `failed` |
| Correct output | `unknown` |
| Correctness verdict | `needs_manual_review` |
| Reason | Not comparable: verification outcomes differ (exit_64 vs failed). |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1708 ms | 4492 ms | improved is 163.0% slower |
| Peak RSS | 6.7 MB | 15.8 MB | improved uses 135.8% more RAM |

### trampoline-current

#### trampoline-alarms-s1-non

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 161080 | 23.5 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 828 | 20.7 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 166247 | 25.6 | `OK` |
| Improved pipeline | inject | 5 | 0 | 12139 | 4.1 | `OK` |
| Improved pipeline | compile | 5 | 0 | 142782 | 25.8 | `OK` |
| Improved pipeline | verify | 5 | 10 | 2127 | 29.4 | `VERIFICATION FAILED` |

Not comparable: stock CBMC reports unsupported concurrency.

| Field | Value |
| --- | --- |
| Stock output | `unsupported` |
| Improved output | `failed` |
| Correct output | `unknown` |
| Correctness verdict | `needs_manual_review` |
| Reason | Not comparable: stock CBMC reports unsupported concurrency. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 161908 ms | 323295 ms | improved is 99.7% slower |
| Peak RSS | 23.5 MB | 29.4 MB | improved uses 25.1% more RAM |

### trampoline-expanded

#### trampoline-expanded-alarms-s1-non-full-source

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 4 | 0 | 106885 | 24.1 | `OK` |
| Stock CPROVER async | verify | 4 | 6 | 727 | 19.9 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 4 | 0 | 112168 | 25.6 | `OK` |
| Improved pipeline | inject | 4 | 0 | 10548 | 3.9 | `OK` |
| Improved pipeline | compile | 4 | 0 | 113963 | 25.6 | `OK` |
| Improved pipeline | verify | 4 | 10 | 2151 | 29.5 | `VERIFICATION FAILED` |

Not comparable: stock CBMC reports unsupported concurrency.

| Field | Value |
| --- | --- |
| Stock output | `unsupported` |
| Improved output | `failed` |
| Correct output | `unknown` |
| Correctness verdict | `needs_manual_review` |
| Reason | Not comparable: stock CBMC reports unsupported concurrency. |

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 107612 ms | 238830 ms | improved is 121.9% slower |
| Peak RSS | 24.1 MB | 29.5 MB | improved uses 22.4% more RAM |

