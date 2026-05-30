#!/usr/bin/env bash
set -euo pipefail

results_dir=${1:-"$(dirname "${BASH_SOURCE[0]}")/../results"}
summary="$results_dir/summary.md"

PYTHON=${PYTHON:-python3}
"$PYTHON" - "$results_dir" "$summary" <<'PY'
import csv
import pathlib
import statistics
import sys

results = pathlib.Path(sys.argv[1])
summary = pathlib.Path(sys.argv[2])
rows = []
for path in results.glob("*.csv"):
    with path.open(newline="") as fh:
        reader = csv.DictReader(fh)
        rows.extend(reader)

groups = {}
for row in rows:
    if row.get("phase") != "verify" or row.get("run", "").startswith("warmup"):
        continue
    key = (row["benchmark"], row["case"])
    groups.setdefault(key, {}).setdefault(row["variant"], []).append(row)

lines = [
    "# check-src Benchmark Summary",
    "",
    "| Suite | Case | Stock ms | Improved ms | Faster % | Stock MB | Improved MB | RAM less % |",
    "| --- | --- | ---: | ---: | ---: | ---: | ---: | ---: |",
]
for (suite, case), variants in sorted(groups.items()):
    stock = variants.get("stock_naive", [])
    improved = variants.get("improved_targeted", [])
    if not stock or not improved:
        continue
    stock_ms = statistics.median(float(r["time_ms"]) for r in stock)
    improved_ms = statistics.median(float(r["time_ms"]) for r in improved)
    stock_mb = statistics.median(float(r["max_rss_mb"]) for r in stock)
    improved_mb = statistics.median(float(r["max_rss_mb"]) for r in improved)
    faster = ((stock_ms - improved_ms) * 100 / stock_ms) if stock_ms else 0
    ram_less = ((stock_mb - improved_mb) * 100 / stock_mb) if stock_mb else 0
    lines.append(f"| {suite} | {case} | {stock_ms:.0f} | {improved_ms:.0f} | {faster:.1f} | {stock_mb:.1f} | {improved_mb:.1f} | {ram_less:.1f} |")

summary.write_text("\n".join(lines) + "\n")
print(summary)
PY
