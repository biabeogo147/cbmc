#!/usr/bin/env bash
set -euo pipefail

cat <<'MSG'
Import the IntAbs interrupt-driven benchmarks manually from:
  https://github.com/ChunghaSung/intAbs

Place sources under:
  check-src/benchmark-sources/intabs/

Then update:
  check-src/benchmarks/suites/intabs-interrupts.json

Normalize __VERIFIER_* helpers in harness/support files, not by editing the
original imported sources in place.
MSG
