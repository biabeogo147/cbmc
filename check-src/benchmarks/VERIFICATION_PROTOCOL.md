# Verification Protocol

Use this protocol for headline stock CBMC vs improved CBMC numbers.

1. Record machine information, OS/runtime, CPU, RAM, CBMC paths, CBMC versions,
   branch names, and build type.
2. Run one warmup and five measured runs by default.
3. Use identical `--function`, `--unwind`, `--property`, timeout, and memory
   limit for stock and improved variants.
4. Report median `time_ms` and `max_rss_mb`.
5. Refuse headline speed/RAM deltas when stock and improved verification
   summaries differ.
6. Store raw logs under `$WORK` and CSV/Markdown summaries under
   `check-src/benchmarks/results`.
7. On Windows without WSL, structural self-tests may run, but benchmark RAM
   numbers require Linux/WSL because the sampler reads `/proc/<pid>/status`.
