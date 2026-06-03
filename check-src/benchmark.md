# ISR Comparable Benchmark Results

Generated: 2026-06-03 13:36:06 UTC

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
| `icbmc-large` | true | 6 | 4 | 23166 | yes |
| `intabs-large` | true | 6 | 5 | 5882 | yes |
| `local-smoke` | true | 4 | 1 | 54 | no |
| `osek-local` | true | 6 | 2 | 199 | no |
| `trampoline-c-async` | true | 1 | 1 | 7605 | yes |
| `trampoline-current` | true | 1 | 1 | 7605 | yes |
| `trampoline-expanded` | true | 1 | 1 | 7605 | yes |

## intabs-large

### sc520wdt-1

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 142 | 12.3 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 188 | 18.9 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 143 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 22 | 0.0 | `OK` |
| Improved pipeline | compile | 5 | 0 | 143 | 12.3 | `OK` |
| Improved pipeline | verify | 5 | 0 | 83 | 15.5 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 330 ms | 391 ms | improved is 18.5% slower |
| Peak RSS | 18.9 MB | 15.5 MB | improved uses 18.0% less RAM |

### wdt-pci-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 122 | 12.7 | `OK` |
| Stock CPROVER async | verify | 5 | 6 | 143 | 18.4 | `EXIT_6` |
| Improved pipeline | manifest | 5 | 0 | 143 | 12.8 | `OK` |
| Improved pipeline | inject | 5 | 0 | 62 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 144 | 12.7 | `OK` |
| Improved pipeline | verify | 5 | 6 | 103 | 15.2 | `EXIT_6` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 265 ms | 452 ms | improved is 70.6% slower |
| Peak RSS | 18.4 MB | 15.2 MB | improved uses 17.4% less RAM |

### wdt-pci-src-3

| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |
| --- | --- | ---: | ---: | ---: | ---: | --- |
| Stock CPROVER async | compile | 5 | 0 | 142 | 12.2 | `OK` |
| Stock CPROVER async | verify | 5 | 0 | 184 | 18.6 | `VERIFICATION SUCCESSFUL` |
| Improved pipeline | manifest | 5 | 0 | 143 | 12.3 | `OK` |
| Improved pipeline | inject | 5 | 0 | 42 | 3.9 | `OK` |
| Improved pipeline | compile | 5 | 0 | 143 | 12.3 | `OK` |
| Improved pipeline | verify | 5 | 0 | 123 | 16.1 | `VERIFICATION SUCCESSFUL` |

Comparable: both variants reached the same verification outcome.

| Metric | Stock | Improved | Difference |
| --- | ---: | ---: | --- |
| Full measured time | 326 ms | 451 ms | improved is 38.3% slower |
| Peak RSS | 18.6 MB | 16.1 MB | improved uses 13.4% less RAM |

