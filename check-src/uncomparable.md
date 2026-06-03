# ISR Uncomparable Benchmark Results

Generated: 2026-06-03 13:36:08 UTC

This report is generated from `check-src/benchmarks/results/*.csv` by `check-src/benchmarks/common/report_benchmark.py`.
Warmup rows are ignored; measured rows are summarized with median time and median peak RSS per phase.
This file contains cases that cannot be compared directly.

Comparison labels: Stock CPROVER async, Improved pipeline, Comparable, Not comparable, Median, Peak RSS.

## Source Inventory

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

## Suite Readiness

| Suite | Manifest enabled | Staged cases | Enabled cases | Enabled compile LOC | Headline-ready |
| --- | --- | ---: | ---: | ---: | --- |
| `icbmc-large` | true | 6 | 4 | 23166 | yes |
| `intabs-large` | true | 6 | 5 | 5882 | yes |
| `local-smoke` | true | 4 | 1 | 54 | no |
| `osek-local` | true | 6 | 2 | 199 | no |
| `trampoline-c-async` | true | 1 | 1 | 7605 | yes |
| `trampoline-current` | true | 1 | 1 | 7605 | yes |
| `trampoline-expanded` | true | 1 | 1 | 7605 | yes |

## icbmc-large

### blink

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 204 | 16.1 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 224 | 19.5 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 203 | 16.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 183 | 15.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 184 | 20.0 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 428 ms | 570 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 19.5 MB | 20.0 MB | Not reported for not-comparable verification outcomes. |

### blink-bug

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 224 | 16.1 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 224 | 20.3 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 224 | 15.9 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 204 | 16.1 | `OK` |
| Improved pipeline | verify | 5 | 6 | 183 | 19.2 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 448 ms | 611 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 20.3 MB | 19.2 MB | Not reported for not-comparable verification outcomes. |

### logger

No measured CSV rows are available yet.

### logger-bug

No measured CSV rows are available yet.

### rc-core

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 611 | 35.9 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2188 | 43.2 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 609 | 36.1 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 609 | 35.7 | `OK` |
| Improved pipeline | verify | 5 | 6 | 751 | 32.1 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 2799 ms | 1969 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 43.2 MB | 36.1 MB | Not reported for not-comparable verification outcomes. |

### rc-core-bug

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 569 | 35.7 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2209 | 43.1 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 609 | 36.1 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 588 | 35.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 791 | 31.9 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 2778 ms | 1988 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 43.1 MB | 36.1 MB | Not reported for not-comparable verification outcomes. |

## intabs-large

### logger3

No measured CSV rows are available yet.

### sc520wdt-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 183 | 14.6 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 1541 | 46.5 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 183 | 14.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 42 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 184 | 14.4 | `OK` |
| Improved pipeline | verify | 5 | 10 | 103 | 16.1 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1724 ms | 512 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 46.5 MB | 16.1 MB | Not reported for not-comparable verification outcomes. |

### wdt-pci-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 122 | 12.7 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 82 | 15.3 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 123 | 12.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 62 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 143 | 12.0 | `OK` |
| Improved pipeline | verify | 5 | 6 | 82 | 15.3 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 204 ms | 410 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 15.3 MB | 15.3 MB | Not reported for not-comparable verification outcomes. |

## local-smoke

### t-interleaving

No measured CSV rows are available yet.

### t-isr-added-single-file

No measured CSV rows are available yet.

### t-isr-multifile

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 103 | 9.5 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 147 | 13.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 102 | 10.0 | `OK` |
| Improved pipeline | inject | 1 | 0 | 21 | 0.0 | `OK` |
| Improved pipeline | compile | 1 | 0 | 102 | 9.8 | `OK` |
| Improved pipeline | verify | 1 | 10 | 82 | 15.3 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 250 ms | 307 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 13.8 MB | 15.3 MB | Not reported for not-comparable verification outcomes. |

### t-isr-single-file

No measured CSV rows are available yet.

## osek-local

### osek-event-basic

No measured CSV rows are available yet.

### osek-event-interleaving

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 102 | 9.8 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 62 | 13.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 102 | 9.4 | `OK` |
| Improved pipeline | inject | 1 | 0 | 22 | 0.0 | `OK` |
| Improved pipeline | compile | 1 | 0 | 102 | 10.0 | `OK` |
| Improved pipeline | verify | 1 | 10 | 82 | 15.2 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 164 ms | 308 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 13.8 MB | 15.2 MB | Not reported for not-comparable verification outcomes. |

### osek-event-multi-bits

No measured CSV rows are available yet.

### osek-event-wait-block

No measured CSV rows are available yet.

### osek-event-wait-noblock

No measured CSV rows are available yet.

### osek-priority-interleaving

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 102 | 9.7 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 83 | 15.0 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 102 | 9.5 | `OK` |
| Improved pipeline | inject | 1 | 0 | 22 | 0.0 | `OK` |
| Improved pipeline | compile | 1 | 0 | 102 | 9.4 | `OK` |
| Improved pipeline | verify | 1 | 10 | 103 | 15.8 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 185 ms | 329 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 15.0 MB | 15.8 MB | Not reported for not-comparable verification outcomes. |

## trampoline-c-async

### trampoline-c-async-alarms-s1-non

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 2350 | 25.7 | `OK` |
| Stock CPROVER async | verify | 1 | 6 | 2700 | 36.1 | `CBMC_UNSUPPORTED_CONCURRENCY` |

Not comparable: one variant has no measured CSV rows.

## trampoline-current

### trampoline-alarms-s1-non

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 2273 | 25.7 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2756 | 35.5 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 2291 | 25.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 670 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 2312 | 25.8 | `OK` |
| Improved pipeline | verify | 5 | 10 | 1825 | 27.4 | `VERIFICATION FAILED` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 5029 ms | 7098 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 35.5 MB | 27.4 MB | Not reported for not-comparable verification outcomes. |

## trampoline-expanded

### trampoline-expanded-alarms-s1-non-full-source

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 2295 | 25.7 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2737 | 35.6 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 2376 | 25.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 670 | 4.1 | `OK` |
| Improved pipeline | compile | 5 | 0 | 2311 | 25.2 | `OK` |
| Improved pipeline | verify | 5 | 10 | 1784 | 27.3 | `VERIFICATION FAILED` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 5032 ms | 7141 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 35.6 MB | 27.3 MB | Not reported for not-comparable verification outcomes. |

