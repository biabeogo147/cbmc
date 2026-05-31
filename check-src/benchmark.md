# ISR Benchmark Results

Generated: 2026-05-30 19:05:09 UTC

This report is generated from `check-src/benchmarks/results/*.csv` by `check-src/benchmarks/common/report_benchmark.py`.
Warmup rows are ignored; measured rows are summarized with median time and median peak RSS per phase.

Comparison labels: Stock CPROVER async, Improved pipeline, Stock naive, Improved targeted, Comparable, Not comparable, Median, Peak RSS.

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
| `icbmc-interrupts` | false | 1 | 0 | 0 | no |
| `icbmc-large` | true | 6 | 4 | 23166 | yes |
| `intabs-interrupts` | false | 1 | 0 | 0 | no |
| `intabs-large` | true | 6 | 5 | 5882 | yes |
| `local-smoke` | true | 4 | 3 | 142 | no |
| `osek-local` | true | 6 | 2 | 199 | no |
| `trampoline-c-async` | true | 1 | 1 | 7605 | yes |
| `trampoline-current` | true | 1 | 1 | 7605 | yes |
| `trampoline-expanded` | true | 1 | 1 | 7605 | yes |

## icbmc-interrupts

Suite manifest is disabled; any listed cases are staged or smoke-only until validation gates pass.

### icbmc-logger

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 104 | 6.1 | `OK` |
| Stock CPROVER async | verify | 1 | 10 | 104 | 18.6 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 1 | 0 | 145 | 9.5 | `OK` |
| Improved pipeline | inject | 1 | 0 | 225 | 3.8 | `OK` |
| Improved pipeline | compile | 1 | 0 | 225 | 9.4 | `OK` |
| Improved pipeline | verify | 1 | 10 | 190 | 18.0 | `VERIFICATION FAILED` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 208 ms | 785 ms | Not reported because the suite is not headline-ready. |
| Peak RSS | 18.6 MB | 18.0 MB | Not reported because the suite is not headline-ready. |

## icbmc-large

### blink

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 105 | 14.8 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 84 | 14.5 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 265 | 16.1 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 226 | 16.2 | `OK` |
| Improved pipeline | verify | 5 | 6 | 186 | 19.5 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 189 ms | 677 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 14.8 MB | 19.5 MB | Not reported for not-comparable verification outcomes. |

### blink-bug

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 145 | 14.5 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 105 | 13.8 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 267 | 16.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 288 | 16.1 | `OK` |
| Improved pipeline | verify | 5 | 6 | 254 | 19.7 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 250 ms | 809 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 14.5 MB | 19.7 MB | Not reported for not-comparable verification outcomes. |

### logger

No measured CSV rows are available yet.

### logger-bug

No measured CSV rows are available yet.

### rc-core

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 306 | 33.8 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 249 | 30.4 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 642 | 35.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 650 | 35.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 873 | 32.0 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 555 ms | 2165 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 33.8 MB | 35.9 MB | Not reported for not-comparable verification outcomes. |

### rc-core-bug

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 267 | 33.8 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 246 | 30.7 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 651 | 36.1 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 651 | 35.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 794 | 32.2 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 513 ms | 2096 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 33.8 MB | 36.1 MB | Not reported for not-comparable verification outcomes. |

## intabs-interrupts

Suite manifest is disabled; any listed cases are staged or smoke-only until validation gates pass.

### intabs-logger2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 145 | 8.0 | `OK` |
| Stock CPROVER async | verify | 1 | 10 | 413 | 13.8 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 1 | 0 | 585 | 9.8 | `OK` |
| Improved pipeline | inject | 1 | 0 | 358 | 3.8 | `OK` |
| Improved pipeline | compile | 1 | 0 | 680 | 9.7 | `OK` |
| Improved pipeline | verify | 1 | 0 | 639 | 16.1 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 558 ms | 2262 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 13.8 MB | 16.1 MB | Not reported for not-comparable verification outcomes. |

## intabs-large

### logger3

No measured CSV rows are available yet.

### sc520wdt-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 128 | 10.6 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 105 | 14.5 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 266 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 85 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 267 | 12.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 125 | 15.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 233 ms | 743 ms | improved is 218.9% slower |
| Peak RSS | 14.5 MB | 15.6 MB | improved uses 7.6% more RAM |

### sc520wdt-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 206 | 13.2 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 328 | 35.3 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 327 | 14.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 105 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 287 | 14.6 | `OK` |
| Improved pipeline | verify | 5 | 10 | 145 | 16.6 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 534 ms | 864 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 35.3 MB | 16.6 MB | Not reported for not-comparable verification outcomes. |

### wdt-pci-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 166 | 10.8 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 64 | 10.0 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 275 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 105 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 246 | 12.3 | `OK` |
| Improved pipeline | verify | 5 | 6 | 124 | 15.5 | `EXIT_6` |

Not comparable: verification outcomes differ (success vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 230 ms | 750 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 10.8 MB | 15.5 MB | Not reported for not-comparable verification outcomes. |

### wdt-pci-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 166 | 10.6 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 90 | 12.7 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 266 | 12.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 106 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 266 | 13.0 | `OK` |
| Improved pipeline | verify | 5 | 6 | 105 | 15.8 | `EXIT_6` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 256 ms | 743 ms | improved is 190.2% slower |
| Peak RSS | 12.7 MB | 15.8 MB | improved uses 24.4% more RAM |

### wdt-pci-src-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 145 | 10.0 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 105 | 14.2 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 246 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 124 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 267 | 12.5 | `OK` |
| Improved pipeline | verify | 5 | 0 | 146 | 16.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 250 ms | 783 ms | improved is 213.2% slower |
| Peak RSS | 14.2 MB | 16.4 MB | improved uses 15.5% more RAM |

## local-smoke

### t-interleaving

No measured CSV rows are available yet.

### t-isr-added-single-file

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock naive | compile | 1 | 0 | 401 | 8.8 | `OK` |
| Stock naive | verify | 1 | 10 | 204 | 10.2 | `VERIFICATION FAILED` |
| Improved targeted | manifest | 1 | 0 | 467 | 10.6 | `OK` |
| Improved targeted | inject | 1 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved targeted | compile | 1 | 0 | 352 | 10.5 | `OK` |
| Improved targeted | verify | 1 | 10 | 625 | 16.1 | `VERIFICATION FAILED` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 605 ms | 1444 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 10.2 MB | 16.1 MB | Not reported for not-comparable verification outcomes. |

### t-isr-multifile

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock naive | compile | 1 | 0 | 555 | 8.0 | `OK` |
| Stock naive | verify | 1 | 10 | 126 | 10.5 | `VERIFICATION FAILED` |
| Improved targeted | manifest | 1 | 0 | 1121 | 10.0 | `OK` |
| Improved targeted | inject | 1 | 0 | 444 | 3.8 | `OK` |
| Improved targeted | compile | 1 | 0 | 874 | 10.0 | `OK` |
| Improved targeted | verify | 1 | 10 | 149 | 15.6 | `VERIFICATION FAILED` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 681 ms | 2588 ms | Not reported because the suite is not headline-ready. |
| Peak RSS | 10.5 MB | 15.6 MB | Not reported because the suite is not headline-ready. |

### t-isr-single-file

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock naive | compile | 1 | 0 | 86 | 7.8 | `OK` |
| Stock naive | verify | 1 | 0 | 111 | 7.8 | `VERIFICATION SUCCESSFUL` |
| Improved targeted | manifest | 1 | 0 | 105 | 10.0 | `OK` |
| Improved targeted | inject | 1 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved targeted | compile | 1 | 0 | 206 | 10.2 | `OK` |
| Improved targeted | verify | 1 | 0 | 263 | 15.0 | `VERIFICATION SUCCESSFUL` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 197 ms | 574 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 7.8 MB | 15.0 MB | Not reported for not-comparable verification outcomes. |

## osek-local

### osek-event-basic

No measured CSV rows are available yet.

### osek-event-interleaving

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock naive | compile | 1 | 0 | 1017 | 8.0 | `OK` |
| Stock naive | verify | 1 | 10 | 564 | 11.7 | `VERIFICATION FAILED` |
| Improved targeted | manifest | 1 | 0 | 1085 | 9.7 | `OK` |
| Improved targeted | inject | 1 | 0 | 614 | 3.6 | `OK` |
| Improved targeted | compile | 1 | 0 | 658 | 9.5 | `OK` |
| Improved targeted | verify | 1 | 10 | 338 | 15.0 | `VERIFICATION FAILED` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1581 ms | 2695 ms | Not reported because the suite is not headline-ready. |
| Peak RSS | 11.7 MB | 15.0 MB | Not reported because the suite is not headline-ready. |

### osek-event-multi-bits

No measured CSV rows are available yet.

### osek-event-wait-block

No measured CSV rows are available yet.

### osek-event-wait-noblock

No measured CSV rows are available yet.

### osek-priority-interleaving

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock naive | compile | 1 | 0 | 959 | 7.7 | `OK` |
| Stock naive | verify | 1 | 10 | 165 | 8.6 | `VERIFICATION FAILED` |
| Improved targeted | manifest | 1 | 0 | 1531 | 9.7 | `OK` |
| Improved targeted | inject | 1 | 0 | 508 | 3.8 | `OK` |
| Improved targeted | compile | 1 | 0 | 966 | 9.7 | `OK` |
| Improved targeted | verify | 1 | 10 | 256 | 14.7 | `VERIFICATION FAILED` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1124 ms | 3261 ms | Not reported because the suite is not headline-ready. |
| Peak RSS | 8.6 MB | 14.7 MB | Not reported because the suite is not headline-ready. |

## trampoline-c-async

### trampoline-c-async-alarms-s1-non

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 32508 | 23.0 | `OK` |
| Stock CPROVER async | verify | 1 | 6 | 409 | 19.3 | `CBMC_UNSUPPORTED_CONCURRENCY` |

## trampoline-current

### trampoline-alarms-s1-non

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 57756 | 23.6 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 807 | 20.7 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 56952 | 25.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 4508 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 66419 | 25.9 | `OK` |
| Improved pipeline | verify | 5 | 10 | 2914 | 29.2 | `VERIFICATION FAILED` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 58563 ms | 130793 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 23.6 MB | 29.2 MB | Not reported for not-comparable verification outcomes. |

## trampoline-expanded

### trampoline-expanded-alarms-s1-non-full-source

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 55157 | 23.7 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 809 | 20.8 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 59194 | 25.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 4328 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 56496 | 25.5 | `OK` |
| Improved pipeline | verify | 5 | 10 | 2850 | 29.0 | `VERIFICATION FAILED` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 55966 ms | 122868 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 23.7 MB | 29.0 MB | Not reported for not-comparable verification outcomes. |

