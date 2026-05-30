#!/usr/bin/env bash
set -euo pipefail

cat <<'MSG'
Import the i-CBMC interrupt benchmarks manually from:
  https://www.cprover.org/interrupts/

Place sources under:
  check-src/external/icbmc/

Then update:
  check-src/benchmarks/suites/icbmc-interrupts.json

This placeholder intentionally does not download code automatically because the
artifact source and license metadata must be recorded with the imported files.
MSG
