# IntAbs Normalized Benchmark Cases

Each case directory must contain:

- `stock-cprover-async/`
- `improved-pipeline/`
- `CASE.md`

Do not enable a case in `intabs-large.json` until both variants compile in Docker.
The corpus-level suite must have at least 5 enabled cases or at least 5000
compile LOC before `benchmark.md` can report it as a headline benchmark.
