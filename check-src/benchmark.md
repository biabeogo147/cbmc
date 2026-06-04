# ISR Comparable Benchmark Results

Generated: 2026-06-04 12:51:40 UTC

This report is generated from `check-src/benchmarks/results/*.csv` by `check-src/benchmarks/common/report_benchmark.py`.
Warmup rows are ignored; measured rows are summarized with median time and median peak RSS per phase.
This file contains cases whose stock and improved verification outcomes are comparable.

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
| `intabs-large` | true | 23 | 21 | 29593 | yes |
| `local-smoke` | true | 4 | 1 | 54 | no |
| `osek-local` | true | 6 | 2 | 199 | no |
| `trampoline-c-async` | true | 1 | 1 | 7605 | yes |
| `trampoline-current` | true | 1 | 1 | 7605 | yes |
| `trampoline-expanded` | true | 1 | 1 | 7605 | yes |

## intabs-large

### sc1200wdt-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 870 | 11.7 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 432 | 17.3 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1458 | 11.9 | `OK` |
| Improved pipeline | inject | 5 | 0 | 948 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1423 | 12.0 | `OK` |
| Improved pipeline | verify | 5 | 0 | 439 | 15.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1302 ms | 4268 ms | improved is 227.8% slower |
| Peak RSS | 17.3 MB | 15.6 MB | improved uses 9.8% less RAM |

### sc1200wdt-2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 633 | 11.6 | `OK` |
| Stock CPROVER async | verify | 5 | 10 | 334 | 17.5 | `VERIFICATION FAILED` |
| Improved pipeline | manifest | 5 | 0 | 1193 | 11.9 | `OK` |
| Improved pipeline | inject | 5 | 0 | 415 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1313 | 12.0 | `OK` |
| Improved pipeline | verify | 5 | 10 | 402 | 15.6 | `VERIFICATION FAILED` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 967 ms | 3323 ms | improved is 243.6% slower |
| Peak RSS | 17.5 MB | 15.6 MB | improved uses 10.9% less RAM |

### sc520wdt-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 870 | 12.2 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 480 | 19.1 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1505 | 12.0 | `OK` |
| Improved pipeline | inject | 5 | 0 | 524 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1576 | 12.5 | `OK` |
| Improved pipeline | verify | 5 | 0 | 457 | 15.8 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1350 ms | 4062 ms | improved is 200.9% slower |
| Peak RSS | 19.1 MB | 15.8 MB | improved uses 17.3% less RAM |

### wdt-pci-1-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 618 | 12.5 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 425 | 18.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1286 | 12.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 851 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1019 | 12.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 339 | 18.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1043 ms | 3495 ms | improved is 235.1% slower |
| Peak RSS | 18.8 MB | 18.4 MB | improved uses 2.1% less RAM |

### wdt-pci-2-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 651 | 12.5 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 514 | 18.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1450 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1140 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1110 | 12.7 | `OK` |
| Improved pipeline | verify | 5 | 0 | 491 | 18.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1165 ms | 4191 ms | improved is 259.7% slower |
| Peak RSS | 18.8 MB | 18.4 MB | improved uses 2.1% less RAM |

### wdt-pci-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 736 | 12.8 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 420 | 18.8 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 1573 | 12.8 | `OK` |
| Improved pipeline | inject | 5 | 0 | 448 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1689 | 12.8 | `OK` |
| Improved pipeline | verify | 5 | 6 | 353 | 16.6 | `EXIT_6` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1156 ms | 4063 ms | improved is 251.5% slower |
| Peak RSS | 18.8 MB | 16.6 MB | improved uses 11.7% less RAM |

### wdt-pci-3-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 832 | 12.5 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 532 | 18.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1537 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1217 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1335 | 12.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 510 | 18.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1364 ms | 4599 ms | improved is 237.2% slower |
| Peak RSS | 18.8 MB | 18.4 MB | improved uses 2.1% less RAM |

### wdt-pci-src-1-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 706 | 12.7 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 541 | 18.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1600 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1013 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1506 | 12.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 410 | 18.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1247 ms | 4529 ms | improved is 263.2% slower |
| Peak RSS | 18.8 MB | 18.4 MB | improved uses 2.1% less RAM |

### wdt-pci-src-2-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 738 | 12.5 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 571 | 18.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1506 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1257 | 3.6 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1527 | 12.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 477 | 18.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1309 ms | 4767 ms | improved is 264.2% slower |
| Peak RSS | 18.8 MB | 18.4 MB | improved uses 2.1% less RAM |

### wdt-pci-src-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 810 | 12.2 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 474 | 18.6 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1722 | 12.5 | `OK` |
| Improved pipeline | inject | 5 | 0 | 595 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1491 | 12.3 | `OK` |
| Improved pipeline | verify | 5 | 0 | 489 | 16.6 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1284 ms | 4297 ms | improved is 234.7% slower |
| Peak RSS | 18.6 MB | 16.6 MB | improved uses 10.8% less RAM |

### wdt-pci-src-3-main2

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 831 | 12.7 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 504 | 18.8 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 1340 | 12.7 | `OK` |
| Improved pipeline | inject | 5 | 0 | 1219 | 3.8 | `OK` |
| Improved pipeline | compile | 5 | 0 | 1496 | 12.8 | `OK` |
| Improved pipeline | verify | 5 | 0 | 459 | 18.4 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 1335 ms | 4514 ms | improved is 238.1% slower |
| Peak RSS | 18.8 MB | 18.4 MB | improved uses 2.1% less RAM |

