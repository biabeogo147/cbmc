# Benchmark Source Corpora

This directory is the single managed location for benchmark source corpora.

## Layout

| Path | Meaning |
| --- | --- |
| `trampoline/stock-cprover-async/` | Trampoline source modeled with CPROVER async labels for stock CBMC. |
| `trampoline/improved-pipeline/` | Trampoline source modeled for the improved CBMC interleaving pipeline. |
| `icbmc/upstream/` | Full collected i-CBMC benchmark artifacts from the CPROVER interrupt benchmark page. |
| `icbmc/cases/` | Staged normalized i-CBMC cases. Each case has `stock-cprover-async`, `improved-pipeline`, and `CASE.md`. |
| `intabs/upstream/` | Full collected IntAbs repository snapshot from GitHub. |
| `intabs/cases/` | Staged normalized IntAbs cases. Each case has `stock-cprover-async`, `improved-pipeline`, and `CASE.md`. |
| `CASE_INTAKE.md` | Intake workflow for moving upstream sources into comparable benchmark cases. |

## Collected Corpus Size

| Corpus | Location | C/H/I files | LOC |
| --- | --- | ---: | ---: |
| i-CBMC all artifacts | `icbmc/upstream` | 232 | 216799 |
| i-CBMC `po-code` | `icbmc/upstream/extracted/po-code` | 32 | 31302 |
| i-CBMC `seq-code` | `icbmc/upstream/extracted/seq-code` | 72 | 79314 |
| i-CBMC `conc-code` | `icbmc/upstream/extracted/conc-code` | 128 | 106183 |
| IntAbs repository | `intabs/upstream/repository` | 120 | 87868 |
| IntAbs `icbmc` cases | `intabs/upstream/repository/icbmc` | 64 | 50459 |
| IntAbs `src/test` cases | `intabs/upstream/repository/src/test` | 47 | 36088 |

## Policy

Do not report i-CBMC or IntAbs headline benchmark numbers from the tiny normalized
Logger smoke cases. First select larger upstream cases, create both benchmark
variants, validate that stock and improved variants compile, and only then enable
the corresponding suite manifest.

For improved-pipeline headline cases, ISR/task entry definitions must live under
`isr_define/isr.c` or an explicitly documented deeper `isr_define/` path. For
monolithic upstream files with heavy `static` state, keep `main.c` as the direct
compile unit and include `isr_define/isr.c` at the last extracted definition
location. This keeps globals declared between upstream task definitions visible
to every extracted ISR. The suite should then compile `main.c` but pass
`isr_define/isr.c` through `variant_isr_sources.improved_pipeline`.

## Staged Normalized Cases

Normalized source directories remain staged even when their suite entries are
disabled. Enable them only after both variants compile and verification outcomes
are classified in Docker.

| Corpus | Staged cases | Enabled cases | Suite |
| --- | ---: | ---: | --- |
| i-CBMC | 24 | 12 | `check-src/benchmarks/suites/icbmc-large.json` |
| IntAbs | 23 | 21 | `check-src/benchmarks/suites/intabs-large.json` |

## Headline Benchmark Gate

External i-CBMC and IntAbs benchmark suites are headline-ready only when:

- the suite has at least 5 enabled normalized cases, or at least 5000 compile LOC;
- every enabled case has `stock-cprover-async` and `improved-pipeline` variants;
- both variants compile in Docker;
- verification outcomes are classified as comparable or explicitly not comparable.
