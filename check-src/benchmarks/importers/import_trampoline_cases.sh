#!/usr/bin/env bash
set -euo pipefail

cat <<'MSG'
Import larger Trampoline ISR/OSEK cases from the local full Trampoline tree:
  D:\DS-AI\Research-thay-Hoa\CBMC Research\trampoline

Prioritize examples/tests with ISR1/ISR2, alarms, events, hooks, IOC, and COM.
Keep imported or selected sources unchanged and express compile details in:
  check-src/benchmarks/suites/trampoline-expanded.json
MSG
