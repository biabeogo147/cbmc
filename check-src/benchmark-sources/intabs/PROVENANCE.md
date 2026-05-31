# IntAbs Benchmark Source Provenance

Import date: 2026-05-30

Upstream repository: https://github.com/chunghasung/intabs

Imported revision:
- `b80d842993013ca40d4900498171192bd94b2602`

Collected upstream corpus:
- Exported repository snapshot: `upstream/repository`
- Total collected C/H/I size: 120 files, 87868 LOC
- `upstream/repository/icbmc`: 64 files, 50459 LOC
- `upstream/repository/src/test`: 47 files, 36088 LOC

Normalized runnable case:
- `logger2/stock-cprover-async`: IntAbs Logger2 task model rewritten to use CPROVER async labels for stock CBMC.
- `logger2/improved-pipeline`: split foreground/ISR model for the improved CBMC interleaving pipeline.

Notes:
- The upstream README describes IntAbs as a thread-modular abstract-interpretation framework for interrupt-driven programs using priority information.
- The normalized Logger2 case is smoke-only and must not be used as the headline IntAbs benchmark.
- Select and normalize larger cases from `upstream/repository` before enabling the suite for benchmark reporting.
