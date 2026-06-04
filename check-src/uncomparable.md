# ISR Uncomparable Benchmark Results

Generated: 2026-06-04 12:51:43 UTC

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
| `icbmc-large` | true | 24 | 12 | 36008 | yes |
| `icbmc-timeout-30m` | false | 6 | 6 | 13150 | no |
| `icbmc-timeout-30m-blink-highmem` | false | 2 | 2 | 8111 | no |
| `icbmc-timeout-30m-logger-stable` | false | 4 | 4 | 5039 | no |
| `intabs-large` | true | 23 | 21 | 29593 | yes |
| `local-smoke` | true | 4 | 1 | 54 | no |
| `osek-local` | true | 6 | 2 | 199 | no |
| `trampoline-c-async` | true | 1 | 1 | 7605 | yes |
| `trampoline-current` | true | 1 | 1 | 7605 | yes |
| `trampoline-expanded` | true | 1 | 1 | 7605 | yes |

## Uncomparable Summary

| Reason | Cases |
| --- | ---: |
| Verification Failed vs Successful | 7 |
| Verification Successful vs Failed | 4 |
| Verification Failed vs Exit 6 | 9 |
| CBMC Unsupported Concurrency | 8 |
| Stock Timeout | 0 |
| Improved Timeout | 0 |
| Stock Memory Limit | 4 |
| Improved Memory Limit | 0 |
| No Injection Candidates | 7 |
| Missing Variant Results | 1 |
| Not Run / Disabled Cases | 21 |
| Other Verification Outcome Mismatches | 0 |

## Verification Failed vs Successful

### intabs-large

#### i8xx-tco-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 770 | 11.2 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 460 | 17.5 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1365 | 11.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 440 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1364 | 11.6 | `OK` |
| Improved pipeline | verify | 5 | 0 | 387 | 15.2 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1230 ms | 3556 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 17.5 MB | 15.2 MB | Not reported for not-comparable verification outcomes. |

#### i8xx-tco-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 798 | 12.3 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 539 | 19.2 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1519 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 435 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1410 | 13.3 | `OK` |
| Improved pipeline | verify | 5 | 0 | 467 | 18.9 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1337 ms | 3831 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 19.2 MB | 18.9 MB | Not reported for not-comparable verification outcomes. |

#### i8xx-tco-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 712 | 12.3 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 396 | 20.1 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 891 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 443 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 723 | 14.5 | `OK` |
| Improved pipeline | verify | 5 | 0 | 444 | 19.4 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1108 ms | 2501 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 20.1 MB | 19.4 MB | Not reported for not-comparable verification outcomes. |

#### i8xx-tco-src-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 835 | 12.3 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 509 | 19.4 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1358 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 955 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1538 | 16.4 | `OK` |
| Improved pipeline | verify | 5 | 0 | 497 | 19.5 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1344 ms | 4348 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 19.4 MB | 19.5 MB | Not reported for not-comparable verification outcomes. |

#### i8xx-tco-src-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 855 | 12.5 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 614 | 21.5 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1548 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 938 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1435 | 17.2 | `OK` |
| Improved pipeline | verify | 5 | 0 | 520 | 19.7 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1469 ms | 4441 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 21.5 MB | 19.7 MB | Not reported for not-comparable verification outcomes. |

#### wdt-pci-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 824 | 11.9 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 522 | 19.0 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1477 | 12.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 443 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1424 | 13.0 | `OK` |
| Improved pipeline | verify | 5 | 0 | 434 | 15.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1346 ms | 3778 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 19.0 MB | 15.8 MB | Not reported for not-comparable verification outcomes. |

#### wdt-pci-src-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 730 | 12.0 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 539 | 19.6 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1533 | 12.0 | `OK` |
| Improved pipeline | inject | 5 | 0 | 424 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1470 | 12.7 | `OK` |
| Improved pipeline | verify | 5 | 0 | 476 | 18.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: verification outcomes differ (failed vs success).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1269 ms | 3903 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 19.6 MB | 18.8 MB | Not reported for not-comparable verification outcomes. |

## Verification Successful vs Failed

### intabs-large

#### sc520wdt-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 932 | 14.6 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 2110 | 47.2 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1756 | 14.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 527 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1832 | 14.2 | `OK` |
| Improved pipeline | verify | 5 | 10 | 546 | 16.7 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 3042 ms | 4661 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 47.2 MB | 16.7 MB | Not reported for not-comparable verification outcomes. |

### local-smoke

#### t-isr-multifile

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 1226 | 9.7 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 388 | 15.0 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 1298 | 10.0 | `OK` |
| Improved pipeline | inject | 1 | 0 | 1147 | 3.6 | `OK` |
| Improved pipeline | compile | 1 | 0 | 1222 | 9.8 | `OK` |
| Improved pipeline | verify | 1 | 10 | 472 | 15.8 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1614 ms | 4139 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 15.0 MB | 15.8 MB | Not reported for not-comparable verification outcomes. |

### osek-local

#### osek-event-interleaving

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 2112 | 9.5 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 477 | 15.3 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 2331 | 9.4 | `OK` |
| Improved pipeline | inject | 1 | 0 | 712 | 3.6 | `OK` |
| Improved pipeline | compile | 1 | 0 | 1930 | 9.7 | `OK` |
| Improved pipeline | verify | 1 | 10 | 433 | 15.3 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 2589 ms | 5406 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 15.3 MB | 15.3 MB | Not reported for not-comparable verification outcomes. |

#### osek-priority-interleaving

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 1874 | 9.5 | `OK` |
| Stock CPROVER async | verify | 1 | 0 | 462 | 15.2 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 1 | 0 | 1978 | 9.4 | `OK` |
| Improved pipeline | inject | 1 | 0 | 881 | 3.6 | `OK` |
| Improved pipeline | compile | 1 | 0 | 1654 | 9.4 | `OK` |
| Improved pipeline | verify | 1 | 10 | 262 | 15.8 | `VERIFICATION FAILED` |

Not comparable: verification outcomes differ (success vs failed).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 2336 ms | 4775 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 15.2 MB | 15.8 MB | Not reported for not-comparable verification outcomes. |

## Verification Failed vs Exit 6

### icbmc-timeout-30m

Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed.

#### logger2-bug-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 205 | 14.6 | `OK` |
| Stock CPROVER async | verify | 1 | 10 | 36763 | 262.8 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 1 | 0 | 245 | 14.4 | `OK` |
| Improved pipeline | inject | 1 | 0 | 63 | 3.9 | `OK` |
| Improved pipeline | compile | 1 | 0 | 244 | 14.7 | `OK` |
| Improved pipeline | verify | 1 | 6 | 144 | 18.0 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 36968 ms | 696 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 262.8 MB | 18.0 MB | Not reported for not-comparable verification outcomes. |

#### logger2-bug-conc-cprover

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 226 | 13.9 | `OK` |
| Stock CPROVER async | verify | 1 | 10 | 52585 | 298.1 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 1 | 0 | 265 | 13.6 | `OK` |
| Improved pipeline | inject | 1 | 0 | 85 | 3.9 | `OK` |
| Improved pipeline | compile | 1 | 0 | 287 | 13.4 | `OK` |
| Improved pipeline | verify | 1 | 6 | 145 | 16.7 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 52811 ms | 782 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 298.1 MB | 16.7 MB | Not reported for not-comparable verification outcomes. |

#### logger2-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 226 | 14.4 | `OK` |
| Stock CPROVER async | verify | 1 | 10 | 37381 | 262.7 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 1 | 0 | 246 | 14.5 | `OK` |
| Improved pipeline | inject | 1 | 0 | 84 | 3.9 | `OK` |
| Improved pipeline | compile | 1 | 0 | 245 | 14.8 | `OK` |
| Improved pipeline | verify | 1 | 6 | 124 | 16.6 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 37607 ms | 699 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 262.7 MB | 16.6 MB | Not reported for not-comparable verification outcomes. |

#### logger2-conc-cprover

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 166 | 13.4 | `OK` |
| Stock CPROVER async | verify | 1 | 10 | 89452 | 381.9 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 1 | 0 | 165 | 13.1 | `OK` |
| Improved pipeline | inject | 1 | 0 | 84 | 3.9 | `OK` |
| Improved pipeline | compile | 1 | 0 | 166 | 13.1 | `OK` |
| Improved pipeline | verify | 1 | 6 | 144 | 17.8 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 89618 ms | 559 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 381.9 MB | 17.8 MB | Not reported for not-comparable verification outcomes. |

### icbmc-timeout-30m-logger-stable

Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed.

#### logger2-bug-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 184 | 14.4 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 35934 | 262.6 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 245 | 14.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 72 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 245 | 15.0 | `OK` |
| Improved pipeline | verify | 5 | 6 | 124 | 16.4 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 36118 ms | 686 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 262.6 MB | 16.4 MB | Not reported for not-comparable verification outcomes. |

#### logger2-bug-conc-cprover

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 184 | 14.1 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 53242 | 298.8 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 245 | 13.6 | `OK` |
| Improved pipeline | inject | 5 | 0 | 64 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 244 | 13.8 | `OK` |
| Improved pipeline | verify | 5 | 6 | 123 | 16.6 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 53426 ms | 676 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 298.8 MB | 16.6 MB | Not reported for not-comparable verification outcomes. |

#### logger2-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 184 | 14.7 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 37550 | 262.9 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 265 | 14.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 83 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 265 | 14.8 | `OK` |
| Improved pipeline | verify | 5 | 6 | 144 | 17.3 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 37734 ms | 757 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 262.9 MB | 17.3 MB | Not reported for not-comparable verification outcomes. |

#### logger2-conc-cprover

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 144 | 13.6 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 88375 | 381.7 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 164 | 13.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 63 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 164 | 13.0 | `OK` |
| Improved pipeline | verify | 5 | 6 | 124 | 16.7 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 88519 ms | 515 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 381.7 MB | 16.7 MB | Not reported for not-comparable verification outcomes. |

### intabs-large

#### wdt-pci-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 801 | 12.8 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 482 | 16.6 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1694 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 531 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1646 | 12.3 | `OK` |
| Improved pipeline | verify | 5 | 6 | 367 | 15.9 | `EXIT_6` |

Not comparable: verification outcomes differ (failed vs exit_6).

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1283 ms | 4238 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 16.6 MB | 15.9 MB | Not reported for not-comparable verification outcomes. |

## CBMC Unsupported Concurrency

### icbmc-large

#### brake2-1-bug-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 1005 | 16.1 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 551 | 19.7 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 1669 | 16.6 | `OK` |
| Improved pipeline | inject | 5 | 0 | 765 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1750 | 16.4 | `OK` |
| Improved pipeline | verify | 5 | 0 | 458 | 18.0 | `VERIFICATION SUCCESSFUL` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1556 ms | 4642 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 19.7 MB | 18.0 MB | Not reported for not-comparable verification outcomes. |

#### brake2-1-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 1154 | 15.0 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 554 | 20.3 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 1096 | 15.6 | `OK` |
| Improved pipeline | inject | 5 | 0 | 553 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1727 | 15.6 | `OK` |
| Improved pipeline | verify | 5 | 0 | 514 | 17.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1708 ms | 3890 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 20.3 MB | 17.8 MB | Not reported for not-comparable verification outcomes. |

#### brake2-2-bug-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 1161 | 16.1 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 640 | 19.7 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 1602 | 16.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 778 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1804 | 16.0 | `OK` |
| Improved pipeline | verify | 5 | 0 | 513 | 17.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1801 ms | 4697 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 19.7 MB | 17.8 MB | Not reported for not-comparable verification outcomes. |

#### brake2-2-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 1009 | 14.9 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 610 | 20.5 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 1347 | 15.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 753 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1502 | 15.4 | `OK` |
| Improved pipeline | verify | 5 | 0 | 431 | 17.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1619 ms | 4033 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 20.5 MB | 17.8 MB | Not reported for not-comparable verification outcomes. |

#### brake2-3-bug-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 951 | 16.0 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 526 | 20.0 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 1883 | 16.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 863 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 2034 | 16.4 | `OK` |
| Improved pipeline | verify | 5 | 0 | 616 | 18.0 | `VERIFICATION SUCCESSFUL` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1477 ms | 5396 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 20.0 MB | 18.0 MB | Not reported for not-comparable verification outcomes. |

#### brake2-3-po

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 1059 | 15.2 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 705 | 20.3 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 1664 | 15.6 | `OK` |
| Improved pipeline | inject | 5 | 0 | 860 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1807 | 15.6 | `OK` |
| Improved pipeline | verify | 5 | 0 | 517 | 17.7 | `VERIFICATION SUCCESSFUL` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1764 ms | 4848 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 20.3 MB | 17.7 MB | Not reported for not-comparable verification outcomes. |

### trampoline-current

#### trampoline-alarms-s1-non

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 26878 | 25.5 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2485 | 35.8 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 26715 | 25.1 | `OK` |
| Improved pipeline | inject | 5 | 0 | 2020 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 26756 | 24.9 | `OK` |
| Improved pipeline | verify | 5 | 10 | 1619 | 27.3 | `VERIFICATION FAILED` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 29363 ms | 57110 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 35.8 MB | 27.3 MB | Not reported for not-comparable verification outcomes. |

### trampoline-expanded

#### trampoline-expanded-alarms-s1-non-full-source

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 31122 | 25.3 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2657 | 35.7 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 31158 | 25.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 2061 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 28764 | 24.9 | `OK` |
| Improved pipeline | verify | 5 | 10 | 1638 | 27.3 | `VERIFICATION FAILED` |

Not comparable: stock CBMC reports unsupported concurrency.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 33779 ms | 63621 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 35.7 MB | 27.3 MB | Not reported for not-comparable verification outcomes. |

## Stock Memory Limit

### icbmc-timeout-30m

Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed.

#### blink-bug-seq

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 225 | 15.8 | `OK` |
| Stock CPROVER async | verify | 1 | -9 | 712900 | 8192.1 | `MEMORY_LIMIT_EXCEEDED_8192MB` |
| Improved pipeline | manifest | 1 | 0 | 245 | 16.4 | `OK` |
| Improved pipeline | inject | 1 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 1 | 0 | 225 | 16.6 | `OK` |
| Improved pipeline | verify | 1 | 6 | 124 | 17.3 | `EXIT_6` |

Not comparable: stock verification hit the memory limit.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 713125 ms | 594 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 8192.1 MB | 17.3 MB | Not reported for not-comparable verification outcomes. |

#### blink-seq

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 295 | 16.4 | `OK` |
| Stock CPROVER async | verify | 1 | -9 | 721702 | 8192.2 | `MEMORY_LIMIT_EXCEEDED_8192MB` |
| Improved pipeline | manifest | 1 | 0 | 225 | 16.1 | `OK` |
| Improved pipeline | inject | 1 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 1 | 0 | 225 | 16.2 | `OK` |
| Improved pipeline | verify | 1 | 6 | 125 | 17.3 | `EXIT_6` |

Not comparable: stock verification hit the memory limit.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 721997 ms | 575 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 8192.2 MB | 17.3 MB | Not reported for not-comparable verification outcomes. |

### icbmc-timeout-30m-blink-highmem

Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed.

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

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1243491 ms | 608 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 14000.0 MB | 17.3 MB | Not reported for not-comparable verification outcomes. |

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

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1221804 ms | 595 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 14000.2 MB | 17.3 MB | Not reported for not-comparable verification outcomes. |

## No Injection Candidates

### icbmc-large

#### blink

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 225 | 16.1 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 247 | 19.7 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 245 | 16.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 253 | 16.1 | `OK` |
| Improved pipeline | verify | 5 | 6 | 188 | 19.1 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 472 ms | 686 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 19.7 MB | 19.1 MB | Not reported for not-comparable verification outcomes. |

#### blink-bug

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 430 | 16.1 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 571 | 20.3 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 464 | 16.2 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 453 | 15.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 433 | 19.7 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1001 ms | 1350 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 20.3 MB | 19.7 MB | Not reported for not-comparable verification outcomes. |

#### blink-bug-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 285 | 18.2 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 25961 | 153.0 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 305 | 18.0 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 305 | 17.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 171 | 18.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 26246 ms | 781 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 153.0 MB | 18.8 MB | Not reported for not-comparable verification outcomes. |

#### blink-conc

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 285 | 18.3 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 22900 | 179.6 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 305 | 18.4 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 305 | 18.1 | `OK` |
| Improved pipeline | verify | 5 | 0 | 164 | 18.8 | `VERIFICATION SUCCESSFUL` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 23185 ms | 774 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 179.6 MB | 18.8 MB | Not reported for not-comparable verification outcomes. |

#### rc-core

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 864 | 35.9 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2575 | 43.1 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 1013 | 35.9 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 976 | 35.8 | `OK` |
| Improved pipeline | verify | 5 | 6 | 1111 | 32.2 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 3439 ms | 3100 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 43.1 MB | 35.9 MB | Not reported for not-comparable verification outcomes. |

#### rc-core-bug

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 851 | 35.9 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2421 | 43.2 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 991 | 35.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 959 | 35.9 | `OK` |
| Improved pipeline | verify | 5 | 6 | 1115 | 32.0 | `EXIT_6` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 3272 ms | 3065 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 43.2 MB | 35.9 MB | Not reported for not-comparable verification outcomes. |

### intabs-large

#### rcmain

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 865 | 35.7 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 2504 | 43.3 | `CBMC_UNSUPPORTED_CONCURRENCY` |
| Improved pipeline | manifest | 5 | 0 | 1018 | 35.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 0 | 0.0 | `NO_INJECTION_CANDIDATES` |
| Improved pipeline | compile | 5 | 0 | 953 | 35.6 | `OK` |
| Improved pipeline | verify | 5 | 0 | 1142 | 31.5 | `VERIFICATION SUCCESSFUL` |

Not comparable: improved variant had no injection candidates.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 3369 ms | 3113 ms | Not reported for not-comparable verification outcomes. |
| Peak RSS | 43.3 MB | 35.7 MB | Not reported for not-comparable verification outcomes. |

## Missing Variant Results

### trampoline-c-async

#### trampoline-c-async-alarms-s1-non

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 1 | 0 | 37591 | 25.3 | `OK` |
| Stock CPROVER async | verify | 1 | 6 | 2465 | 35.5 | `CBMC_UNSUPPORTED_CONCURRENCY` |

Not comparable: one variant has no measured CSV rows.

## Not Run / Disabled Cases

### icbmc-large

#### blink-bug-seq

Not run: Disabled after 30-minute review: stock verification reaches the available 14000 MB RSS cap before timeout and the improved pipeline has no injection candidates.

#### blink-seq

Not run: Disabled after 30-minute review: stock verification reaches the available 14000 MB RSS cap before timeout and the improved pipeline has no injection candidates.

#### logger

Not run: Normalized as a control case but below the large-case LOC gate; do not use as a headline i-CBMC result.

#### logger-bug

Not run: Normalized as a control case but below the large-case LOC gate; do not use as a headline i-CBMC result.

#### logger2-bug-conc

Not run: Disabled after 30-minute review: stock verification fails while improved verification exits with code 6; retained as staged Logger2 coverage.

#### logger2-bug-conc-cprover

Not run: Disabled after 30-minute review: stock verification fails while improved verification exits with code 6; improved ISR entries were normalized to whole-function atomic regions.

#### logger2-conc

Not run: Disabled after 30-minute review: stock verification fails while improved verification exits with code 6; retained as staged Logger2 coverage.

#### logger2-conc-cprover

Not run: Disabled after 30-minute review: stock verification fails while improved verification exits with code 6; improved ISR entries were normalized to whole-function atomic regions.

#### rc-core-bug-conc

Not run: Disabled during Phase 5 hardening: the improved source retains active pthread launches and reports no injection candidates.

#### rc-core-bug-conc-cprover

Not run: Disabled during Phase 5 hardening: extracted ISR functions are not atomic from function entry and the improved pipeline reports no injection candidates.

#### rc-core-conc

Not run: Disabled during Phase 5 hardening: the improved source retains active pthread launches and reports no injection candidates.

#### rc-core-conc-cprover

Not run: Disabled during Phase 5 hardening: extracted ISR functions are not atomic from function entry and the improved pipeline reports no injection candidates.

### intabs-large

#### logger2

Not run: Legacy normalized control case; disabled because the stock tree has no CPROVER async modeling and the original upstream source metadata was not recorded.

#### logger3

Not run: Normalized as a control case but below the large-case LOC gate; do not use as a headline IntAbs result.

### local-smoke

#### t-interleaving

Not run: Non-ISR smoke input kept documented; enable after defining ISR entry points.

#### t-isr-added-single-file

Not run: Legacy pre-injected single-file smoke input was removed; kept only as historical report context.

#### t-isr-single-file

Not run: Legacy single-file smoke input was removed; kept only as historical report context.

### osek-local

#### osek-event-basic

Not run: Regression case has no dedicated ISR source yet; tracked for future harness normalization.

#### osek-event-multi-bits

Not run: Regression case has no dedicated ISR source yet; tracked for future harness normalization.

#### osek-event-wait-block

Not run: Regression case has no dedicated ISR source yet; tracked for future harness normalization.

#### osek-event-wait-noblock

Not run: Regression case has no dedicated ISR source yet; tracked for future harness normalization.

