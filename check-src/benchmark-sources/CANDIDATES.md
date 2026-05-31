# Benchmark Candidate Scan

## i-CBMC

| Path | LOC | async labels | pthread_create | thread metadata | assert | score |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/rc-core/nobug/rc_core_conc.c` | 9535 | 5 | 6 | 2 | 4 | 16235 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/rc-core/nobug/rc_core_conc_cprover.c` | 9519 | 5 | 6 | 2 | 4 | 16219 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/rc-core/rc_core.c` | 8135 | 7 | 6 | 2 | 2 | 15735 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/rc-core/rc_core_bug.c` | 8135 | 7 | 6 | 2 | 2 | 15735 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/rc-core/bug/rc_core_bug_conc.c` | 8835 | 5 | 6 | 2 | 4 | 15535 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/rc-core/bug/rc_core_bug_conc_cprover.c` | 8820 | 5 | 6 | 2 | 4 | 15520 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/rc-core/bug/rc_core_bug_por_seq.c` | 8568 | 5 | 6 | 2 | 2 | 15168 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/rc-core/nobug/rc_core_por_seq.c` | 8563 | 5 | 6 | 2 | 2 | 15163 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/blink/nobug/blink_conc.c` | 4642 | 2 | 2 | 2 | 15 | 8392 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/blink/bug/blink_bug_conc.c` | 4597 | 2 | 2 | 2 | 15 | 8347 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/blink/bug/blink_bug_conc_cprover.c` | 4703 | 2 | 0 | 2 | 16 | 7503 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/blink/nobug/blink_conc_cprover.c` | 4616 | 2 | 0 | 2 | 15 | 7366 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/brake/brake2_1_bug_po.c` | 601 | 12 | 0 | 1 | 2 | 7201 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/brake/brake2_2_bug_po.c` | 601 | 12 | 0 | 1 | 2 | 7201 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/brake/brake2_3_bug_po.c` | 601 | 12 | 0 | 1 | 2 | 7201 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/blink/bug/blink_bug_por_seq.c` | 4059 | 2 | 0 | 2 | 7 | 6409 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/blink/nobug/blink_por_seq.c` | 4052 | 2 | 0 | 2 | 7 | 6402 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/blink/blink.c` | 3438 | 3 | 0 | 2 | 7 | 6288 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/blink/blink_bug.c` | 3438 | 3 | 0 | 2 | 7 | 6288 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/logger2/bug/logger2_bug_conc.c` | 1365 | 4 | 4 | 1 | 2 | 5965 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/logger2/nobug/logger2_conc.c` | 1365 | 4 | 4 | 1 | 2 | 5965 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/logger2/bug/logger2_bug_conc_cprover.c` | 1180 | 4 | 4 | 1 | 2 | 5780 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/logger2/nobug/logger2_conc_cprover.c` | 1113 | 4 | 4 | 1 | 2 | 5713 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/brake/brake2_2_po.c` | 595 | 9 | 0 | 1 | 2 | 5695 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/brake/brake2_3_po.c` | 594 | 9 | 0 | 1 | 2 | 5694 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/brake/brake2_1_po.c` | 593 | 9 | 0 | 1 | 2 | 5693 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/brake/nobug/brake2_3_por_seq.i` | 4184 | 0 | 0 | 1 | 0 | 4684 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/brake/bug/brake2_3_bug_por_seq.i` | 4179 | 0 | 0 | 1 | 0 | 4679 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/brake/nobug/brake2_2_por_seq.i` | 4160 | 0 | 0 | 1 | 0 | 4660 |
| `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/brake/bug/brake2_2_bug_por_seq.i` | 4157 | 0 | 0 | 1 | 0 | 4657 |

## IntAbs

| Path | LOC | async labels | pthread_create | thread metadata | assert | score |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_3/main.c` | 1359 | 5 | 37 | 0 | 5 | 22609 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc520wdt_2/main.c` | 884 | 0 | 40 | 0 | 5 | 21134 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc520wdt_2/main2.c` | 882 | 0 | 40 | 0 | 5 | 21132 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_2/main.c` | 1302 | 3 | 35 | 0 | 4 | 20502 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/wdt_pci_3/main.c` | 1339 | 0 | 37 | 0 | 5 | 20089 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_1/main.c` | 1256 | 4 | 33 | 0 | 3 | 19906 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/wdt_pci_2/main.c` | 1290 | 0 | 35 | 0 | 4 | 18990 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/wdt_pci_1/main.c` | 1239 | 0 | 33 | 0 | 3 | 17889 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_1/main2.c` | 1133 | 0 | 30 | 0 | 1 | 16183 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_2/main2.c` | 1133 | 0 | 30 | 0 | 1 | 16183 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_3/main2.c` | 1133 | 0 | 30 | 0 | 1 | 16183 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/wdt_pci_1/main2.c` | 1133 | 0 | 30 | 0 | 1 | 16183 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/wdt_pci_2/main2.c` | 1133 | 0 | 30 | 0 | 1 | 16183 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/wdt_pci_3/main2.c` | 1133 | 0 | 30 | 0 | 1 | 16183 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc1200wdt_2/main2.c` | 770 | 0 | 30 | 0 | 4 | 15970 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc520wdt_1/main2.c` | 806 | 0 | 30 | 0 | 1 | 15856 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc520wdt_1/main.c` | 805 | 0 | 30 | 0 | 1 | 15855 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/po-code/rc-core/rc_core.c` | 8135 | 7 | 6 | 2 | 2 | 15735 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/po-code/rc-core/rc_core_bug.c` | 8135 | 7 | 6 | 2 | 2 | 15735 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/rcmain/rc_core.c` | 8135 | 7 | 6 | 2 | 2 | 15735 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/i8xx_tco_3/main.c` | 963 | 6 | 23 | 0 | 1 | 15513 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/i8xx_tco_2/main.c` | 943 | 4 | 21 | 0 | 1 | 13493 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/i8xx_tco_3/main.c` | 944 | 0 | 23 | 0 | 1 | 12494 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc1200wdt_1/main.c` | 715 | 0 | 23 | 0 | 1 | 12265 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc1200wdt_1/main2.c` | 715 | 0 | 23 | 0 | 1 | 12265 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/i8xx_tco_2/main2.c` | 901 | 0 | 22 | 0 | 1 | 11951 |
| `check-src/benchmark-sources/intabs/upstream/repository/icbmc/i8xx_tco_3/main2.c` | 901 | 0 | 22 | 0 | 1 | 11951 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/i8xx_tco_2/main2.c` | 901 | 0 | 22 | 0 | 1 | 11951 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/i8xx_tco_3/main2.c` | 901 | 0 | 22 | 0 | 1 | 11951 |
| `check-src/benchmark-sources/intabs/upstream/repository/src/test/i8xx_tco_2/main.c` | 949 | 0 | 21 | 0 | 1 | 11499 |
