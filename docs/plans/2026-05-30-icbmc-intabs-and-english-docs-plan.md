# i-CBMC, IntAbs, and English Documentation Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Put all benchmark source corpora in one managed location, add runnable i-CBMC and IntAbs interrupt suites with correct stock-vs-improved modeling, then convert all Markdown documentation under `check-src` to English.

**Architecture:** Use `check-src/benchmark-sources` as the single source-corpus root. Each logical benchmark case has two source/model variants: `stock-cprover-async` for stock CBMC using `__CPROVER_ASYNC_*`/C_ASYNC_PROVER-style modeling, and `improved-pipeline` for the improved CBMC interleaving pipeline using `goto-cc --interleaving-*` plus `aib`. Do not edit imported upstream files in place; keep provenance beside each corpus and add support harnesses or normalized copies under the relevant variant directory.

**Tech Stack:** Bash, Python 3, Docker Linux runner, CBMC/goto-cc, `aib`, JSON suite manifests, Markdown docs.

---

## Source References

- i-CBMC benchmark source page: `https://www.cprover.org/interrupts/`
- IntAbs project/source page: `https://github.com/ChunghaSung/intAbs`
- Existing local placeholders:
  - `check-src/external/icbmc/README.md` (legacy notes/staging only after this plan)
  - `check-src/external/intabs/README.md` (legacy notes/staging only after this plan)
  - `check-src/benchmarks/importers/import_icbmc_interrupts.sh`
  - `check-src/benchmarks/importers/import_intabs.sh`
  - `check-src/benchmarks/suites/icbmc-interrupts.json`
  - `check-src/benchmarks/suites/intabs-interrupts.json`

## File Structure Target

Create or modify these paths:

- Create: `check-src/benchmark-sources/`
  - Single managed location for Trampoline, i-CBMC, IntAbs, and future benchmark source corpora.
- Move and then delete old paths:
  - Move `check-src/simple-benchmarks/trampoline` to `check-src/benchmark-sources/trampoline/improved-pipeline`
  - Move `check-src/simple-benchmarks/trampoline_c_async` to `check-src/benchmark-sources/trampoline/stock-cprover-async`
  - Delete the old `check-src/simple-benchmarks/trampoline` and `check-src/simple-benchmarks/trampoline_c_async` directories after the move succeeds. Do not leave duplicate source trees.
- Create: `check-src/benchmark-sources/trampoline/PROVENANCE.md`
  - Record that both Trampoline variants came from the previous local `simple-benchmarks` source trees.
- Create: `check-src/benchmark-sources/icbmc/`
  - Put i-CBMC source variants here, not under `check-src/external`.
- Create: `check-src/benchmark-sources/intabs/`
  - Put IntAbs source variants here, not under `check-src/external`.
- Modify: `check-src/benchmarks/common/runner.py`
  - Support variant-specific source roots, stock CPROVER async modeling, improved pipeline modeling, `defines`, `timeout_sec`, and `memory_limit_mb`.
- Create: `check-src/benchmarks/common/normalize_verifier.py`
  - Generate support files for common `__VERIFIER_*`, `nondet_*`, and interrupt harness compatibility without changing imported source in place.
- Modify: `check-src/benchmarks/importers/import_icbmc_interrupts.sh`
  - Import or stage i-CBMC artifacts, record provenance, and print exact next steps when network/manual download is required.
- Modify: `check-src/benchmarks/importers/import_intabs.sh`
  - Import or stage IntAbs artifacts, record commit/archive metadata, and generate normalized harness support files.
- Modify: `check-src/benchmarks/suites/icbmc-interrupts.json`
  - Replace placeholder with enabled cases after at least one i-CBMC case compiles and verifies.
- Modify: `check-src/benchmarks/suites/intabs-interrupts.json`
  - Replace placeholder with enabled cases after at least one IntAbs case compiles and verifies.
- Create: `check-src/benchmark-sources/icbmc/PROVENANCE.md`
  - Record URL, download date, license notes, archive/hash/commit, and imported directories.
- Create: `check-src/benchmark-sources/intabs/PROVENANCE.md`
  - Record URL, download date, license notes, commit/hash, and imported directories.
- Modify: `check-src/benchmarks/README.md`
  - Update suite descriptions and keep all text English-only.
- Modify: `check-src/benchmark.md`
  - Translate benchmark report to English and append i-CBMC/IntAbs results when available.
- Modify: every Markdown file under `check-src/**/*.md`
  - Convert Vietnamese text to English while preserving commands, tables, paths, and measured numeric results.

## Required Source Layout

All runnable benchmark source trees must live under `check-src/benchmark-sources`.
`check-src/external` may remain as a notes/staging area if needed, but benchmark
manifests must not point to it for normal runs.

```text
check-src/benchmark-sources/
  trampoline/
    PROVENANCE.md
    improved-pipeline/
    stock-cprover-async/
  icbmc/
    PROVENANCE.md
    logger/
      improved-pipeline/
      stock-cprover-async/
    blink/
      improved-pipeline/
      stock-cprover-async/
  intabs/
    PROVENANCE.md
    <case-name>/
      improved-pipeline/
      stock-cprover-async/
```

The two variant directories represent two modeling strategies for the same
logical benchmark, not two unrelated benchmarks:

| Variant source directory | Tool under test | Modeling rule |
| --- | --- | --- |
| `stock-cprover-async` | Stock CBMC | Encode interrupt interleavings directly in C with `__CPROVER_ASYNC_*: isr(...);` labels or equivalent C_ASYNC_PROVER-compatible modeling. Do not run `aib`. |
| `improved-pipeline` | Improved CBMC | Keep source suitable for the improved interleaving pipeline. Generate an interleaving manifest with improved `goto-cc`, run `aib`, compile the injected output, then verify. |

Manifest naming should also reflect these variants. Avoid `stock_naive` and
`improved_targeted` for headline comparisons once the async source variant
exists; use `stock_cprover_async` and `improved_pipeline`.

---

### Task 1: Inventory Current Markdown and Benchmark State

**Files:**
- Inspect: `check-src/**/*.md`
- Inspect: `check-src/benchmarks/suites/*.json`
- Inspect: `check-src/benchmarks/importers/*.sh`
- Inspect: `check-src/simple-benchmarks/trampoline`
- Inspect: `check-src/simple-benchmarks/trampoline_c_async`

- [ ] **Step 1: List Markdown files under `check-src`**

Run:

```powershell
rg --files .\check-src | rg '\.md$'
```

Expected: a complete list including `check-src/README.md`, `check-src/benchmark.md`, `check-src/benchmarks/README.md`, external READMEs, and simple benchmark docs.

- [ ] **Step 2: Find Vietnamese text in Markdown**

Run:

```powershell
rg -n "[^\x00-\x7F]|\b(Ngay|Ket|qua|duoc|Ghi chu|goc|cai tien|cham hon|it RAM|Thu muc|Y nghia|Tac dung|Cach)\b" .\check-src -g "*.md"
```

Expected: hits mainly in `check-src/benchmark.md` and `check-src/benchmarks/README.md`.

- [ ] **Step 3: Validate current benchmark manifests before changing them**

Run:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

Expected: `selftest ok`.

---

### Task 2: Move Benchmark Sources into One Corpus Root

**Files:**
- Create: `check-src/benchmark-sources/trampoline/`
- Move: `check-src/simple-benchmarks/trampoline` to `check-src/benchmark-sources/trampoline/improved-pipeline`
- Move: `check-src/simple-benchmarks/trampoline_c_async` to `check-src/benchmark-sources/trampoline/stock-cprover-async`
- Create: `check-src/benchmark-sources/trampoline/PROVENANCE.md`
- Modify: `check-src/README.md`
- Modify: `check-src/benchmarks/suites/trampoline-current.json`
- Modify: `check-src/benchmarks/suites/trampoline-c-async.json`
- Modify: `check-src/benchmarks/suites/trampoline-expanded.json`
- Modify: `check-src/benchmark.md`
- Modify: Markdown references under `check-src/**/*.md`

- [ ] **Step 1: Verify source directories exist before moving**

Run:

```powershell
Test-Path .\check-src\simple-benchmarks\trampoline
Test-Path .\check-src\simple-benchmarks\trampoline_c_async
Test-Path .\check-src\benchmark-sources
```

Expected before the move:

```text
True
True
False
```

If `benchmark-sources` already exists, inspect it before moving and do not overwrite user files.

- [ ] **Step 2: Create the new corpus root**

Run:

```powershell
New-Item -ItemType Directory -Path .\check-src\benchmark-sources\trampoline -Force
```

Expected: `check-src/benchmark-sources/trampoline` exists.

- [ ] **Step 3: Move Trampoline improved-pipeline source**

Run:

```powershell
Move-Item -LiteralPath .\check-src\simple-benchmarks\trampoline -Destination .\check-src\benchmark-sources\trampoline\improved-pipeline
```

Expected:

```powershell
Test-Path .\check-src\benchmark-sources\trampoline\improved-pipeline
Test-Path .\check-src\simple-benchmarks\trampoline
```

returns:

```text
True
False
```

- [ ] **Step 4: Move Trampoline stock CPROVER async source**

Run:

```powershell
Move-Item -LiteralPath .\check-src\simple-benchmarks\trampoline_c_async -Destination .\check-src\benchmark-sources\trampoline\stock-cprover-async
```

Expected:

```powershell
Test-Path .\check-src\benchmark-sources\trampoline\stock-cprover-async
Test-Path .\check-src\simple-benchmarks\trampoline_c_async
```

returns:

```text
True
False
```

This is required: do not leave old duplicate source folders under
`check-src/simple-benchmarks`.

- [ ] **Step 5: Add Trampoline provenance**

Create `check-src/benchmark-sources/trampoline/PROVENANCE.md`:

```markdown
# Trampoline Benchmark Source Provenance

Import date: 2026-05-30
Previous local paths:
- `check-src/simple-benchmarks/trampoline`
- `check-src/simple-benchmarks/trampoline_c_async`

Current variants:
- `improved-pipeline`: source used by the improved CBMC interleaving pipeline.
- `stock-cprover-async`: source used by stock CBMC with CPROVER async labels.

Notes:
- These directories were moved from the existing local `check-src/simple-benchmarks` tree.
- Do not keep duplicate Trampoline source trees in `check-src/simple-benchmarks`.
```

- [ ] **Step 6: Update existing manifest roots**

Change:

```json
"root": "check-src/simple-benchmarks/trampoline"
```

to:

```json
"root": "check-src/benchmark-sources/trampoline/improved-pipeline"
```

in:

- `check-src/benchmarks/suites/trampoline-current.json`
- enabled or placeholder improved Trampoline cases in `check-src/benchmarks/suites/trampoline-expanded.json`

Change:

```json
"root": "check-src/simple-benchmarks/trampoline_c_async"
```

to:

```json
"root": "check-src/benchmark-sources/trampoline/stock-cprover-async"
```

in:

- `check-src/benchmarks/suites/trampoline-c-async.json`

- [ ] **Step 7: Update Markdown and shell references**

Replace Trampoline paths:

```text
check-src/simple-benchmarks/trampoline
check-src/simple-benchmarks/trampoline_c_async
```

with:

```text
check-src/benchmark-sources/trampoline/improved-pipeline
check-src/benchmark-sources/trampoline/stock-cprover-async
```

in all relevant `.md` and `.sh` files.

- [ ] **Step 8: Verify the old directories are gone**

Run:

```powershell
Test-Path .\check-src\simple-benchmarks\trampoline
Test-Path .\check-src\simple-benchmarks\trampoline_c_async
```

Expected:

```text
False
False
```

---

### Task 3: Make Runner Support Variant-Specific Modeling

**Files:**
- Modify: `check-src/benchmarks/common/runner.py`
- Test: `check-src/benchmarks/tests/selftest.ps1`
- Test: Docker dry-run of `local-smoke` and `trampoline-current`

- [ ] **Step 1: Define variant semantics**

Update runner names and behavior so headline comparisons use:

```text
stock_cprover_async
improved_pipeline
```

Keep backward compatibility for old manifests that still list
`stock_naive`/`improved_targeted`, but new i-CBMC/IntAbs/Trampoline headline
manifests should use `stock_cprover_async` and `improved_pipeline`.

- [ ] **Step 2: Add variant-specific roots to manifest handling**

Support a case shape like:

```json
"variant_roots": {
  "stock_cprover_async": "check-src/benchmark-sources/trampoline/stock-cprover-async",
  "improved_pipeline": "check-src/benchmark-sources/trampoline/improved-pipeline"
}
```

Runner behavior:

- `stock_cprover_async` compiles and verifies the stock async source directly.
- `improved_pipeline` runs manifest generation, `aib`, compile, and verify.
- If `variant_roots` is absent, fall back to the existing `root` field for old suites.

- [ ] **Step 3: Add command support for `defines`**

Update `runner.py` so every compile command includes manifest `defines` as `-D<value>`.

Implementation shape:

```python
def define_args(case):
    return [f"-D{value}" for value in case.get("defines", [])]
```

Then include `*define_args(case)` in:

```python
stock_compile = [str(stock_gotocc), *define_args(case), *rel_args(...)]
improved_manifest_cmd = [str(improved_gotocc), *define_args(case), *rel_args(...)]
improved_compile = [str(improved_gotocc), *define_args(case), *rel_args(...)]
```

- [ ] **Step 4: Add timeout enforcement**

Modify `measure(...)` to accept `timeout_sec` and kill the process when elapsed wall time exceeds that value.

Expected CSV behavior:

```text
exit_code=124
summary=TIMEOUT after <timeout_sec>s
```

- [ ] **Step 5: Add memory-limit enforcement**

Modify `measure(...)` to accept `memory_limit_mb` and terminate the process when sampled RSS exceeds the limit.

Expected CSV behavior:

```text
exit_code=125
summary=MEMORY_LIMIT exceeded <memory_limit_mb> MB
```

- [ ] **Step 6: Pass limits from each case**

Update each `measure(...)` call in `run_case(...)` to pass:

```python
case["timeout_sec"], case["memory_limit_mb"]
```

- [ ] **Step 7: Verify runner syntax and existing suites**

Run in Docker:

```bash
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 -m py_compile check-src/benchmarks/common/runner.py check-src/benchmarks/common/inject_naive.py && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/local-smoke.json --dry-run && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/trampoline-current.json --dry-run"
```

Expected: py_compile succeeds and dry-run lists enabled cases.

---

### Task 4: Import and Normalize i-CBMC Benchmarks

**Files:**
- Modify: `check-src/benchmarks/importers/import_icbmc_interrupts.sh`
- Create: `check-src/benchmark-sources/icbmc/PROVENANCE.md`
- Create: `check-src/benchmark-sources/icbmc/<case>/improved-pipeline/`
- Create: `check-src/benchmark-sources/icbmc/<case>/stock-cprover-async/`
- Create: `check-src/benchmark-sources/icbmc/support/`
- Modify: `check-src/benchmarks/suites/icbmc-interrupts.json`

- [ ] **Step 1: Record provenance before adding source**

Create `check-src/benchmark-sources/icbmc/PROVENANCE.md`:

```markdown
# i-CBMC Interrupt Benchmarks Provenance

Source page: https://www.cprover.org/interrupts/
Import date: 2026-05-30
Imported cases: Logger, Blink, Brake, RcCore
License: To be recorded exactly from the downloaded artifact before committing source files.
Archive or commit: To be recorded as URL plus hash after import.

Policy:
- Keep runnable source variants under each case directory.
- Do not edit upstream files in place; create normalized copies for each modeling variant.
- Put shared CBMC compatibility code under `support/`.
```

Before committing imported source, replace the two `To be recorded...` lines with exact license/archive/hash from the artifact.

- [ ] **Step 2: Update importer script behavior**

Modify `check-src/benchmarks/importers/import_icbmc_interrupts.sh` so it:

```bash
#!/usr/bin/env bash
set -euo pipefail

dest=${1:-check-src/benchmark-sources/icbmc}
mkdir -p "$dest/support"

cat <<'MSG'
i-CBMC import target prepared.

Source page:
  https://www.cprover.org/interrupts/

Manual action:
  Download the i-CBMC benchmark source archive from the source page.
  Extract Logger, Blink, Brake, and RcCore under:
    check-src/benchmark-sources/icbmc/<case>/upstream-original/

  Create the two runnable variants:
    check-src/benchmark-sources/icbmc/<case>/stock-cprover-async/
    check-src/benchmark-sources/icbmc/<case>/improved-pipeline/

Required after extraction:
  1. Update check-src/benchmark-sources/icbmc/PROVENANCE.md with exact URL, license, and hash.
  2. Add or update check-src/benchmark-sources/icbmc/support/*.h for CBMC compatibility.
  3. Enable validated cases in check-src/benchmarks/suites/icbmc-interrupts.json.
MSG
```

- [ ] **Step 3: Add i-CBMC support header**

Create `check-src/benchmark-sources/icbmc/support/cbmc_compat.h`:

```c
#ifndef CHECK_SRC_ICBMC_CBMC_COMPAT_H
#define CHECK_SRC_ICBMC_CBMC_COMPAT_H

extern _Bool nondet_bool(void);
extern int nondet_int(void);
extern unsigned int nondet_uint(void);

#endif
```

Only add more declarations after seeing the imported source compile errors.

- [ ] **Step 4: Replace placeholder manifest with first validated case**

Start with one small i-CBMC case, preferably `Logger` if present in the artifact.

Expected manifest shape:

```json
{
  "suite_name": "icbmc-interrupts",
  "description": "i-CBMC interrupt benchmarks imported from CPROVER interrupt artifacts.",
  "enabled": true,
  "runs": 5,
  "warmups": 1,
  "variants": ["stock_cprover_async", "improved_pipeline"],
  "cases": [
    {
      "name": "icbmc-logger",
      "enabled": true,
      "variant_roots": {
        "stock_cprover_async": "check-src/benchmark-sources/icbmc/logger/stock-cprover-async",
        "improved_pipeline": "check-src/benchmark-sources/icbmc/logger/improved-pipeline"
      },
      "sources": ["main.c"],
      "include_dirs": [".", "../../support"],
      "isr_sources": ["main.c"],
      "isr_functions": ["isr"],
      "entry_function": "main",
      "properties": [],
      "unwind": 3,
      "defines": ["CBMC"],
      "expected_result": "same-result",
      "timeout_sec": 900,
      "memory_limit_mb": 16384
    }
  ]
}
```

Adjust `sources`, `isr_sources`, and `isr_functions` after inspecting the actual artifact. Do not enable a case until both stock and improved compile phases run.

- [ ] **Step 5: Run Docker validation for i-CBMC**

Run:

```bash
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo -e STOCK_CBMC=/repo/check-src/benchmarks/work/stock-toolchain/bin/cbmc -e STOCK_GOTOCC=/repo/check-src/benchmarks/work/stock-toolchain/bin/goto-cc -e IMPROVED_CBMC=/repo/cmake-build-debug-cbmc/bin/cbmc -e IMPROVED_GOTOCC=/repo/cmake-build-debug-cbmc/bin/goto-cc -e AIB=/repo/cmake-build-debug-cbmc/bin/aib bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-interrupts.json"
```

Expected: CSV is written to `check-src/benchmarks/results/icbmc-interrupts.csv`. If a case fails compile, keep it disabled and record the exact blocker in the case `reason`.

---

### Task 5: Import and Normalize IntAbs Benchmarks

**Files:**
- Modify: `check-src/benchmarks/importers/import_intabs.sh`
- Create: `check-src/benchmark-sources/intabs/PROVENANCE.md`
- Create: `check-src/benchmark-sources/intabs/<case>/improved-pipeline/`
- Create: `check-src/benchmark-sources/intabs/<case>/stock-cprover-async/`
- Create: `check-src/benchmark-sources/intabs/support/`
- Create: `check-src/benchmarks/common/normalize_verifier.py`
- Modify: `check-src/benchmarks/suites/intabs-interrupts.json`

- [ ] **Step 1: Record provenance before adding source**

Create `check-src/benchmark-sources/intabs/PROVENANCE.md`:

```markdown
# IntAbs Interrupt-Driven Benchmarks Provenance

Source repository: https://github.com/ChunghaSung/intAbs
Import date: 2026-05-30
Imported benchmark count: record exact count after cloning or extracting.
License: To be recorded exactly from the repository before committing source files.
Commit: To be recorded after import.

Policy:
- Keep runnable source variants under each case directory.
- Do not edit upstream files in place; create normalized copies for each modeling variant.
- Put shared CBMC compatibility code under `support/`.
```

- [ ] **Step 2: Update importer script behavior**

Modify `check-src/benchmarks/importers/import_intabs.sh` so it prepares directories and records exact manual steps:

```bash
#!/usr/bin/env bash
set -euo pipefail

dest=${1:-check-src/benchmark-sources/intabs}
mkdir -p "$dest/support"

cat <<'MSG'
IntAbs import target prepared.

Source repository:
  https://github.com/ChunghaSung/intAbs

Manual action:
  Clone or download the repository, then copy benchmark C programs under:
    check-src/benchmark-sources/intabs/<case>/upstream-original/

  Create the two runnable variants:
    check-src/benchmark-sources/intabs/<case>/stock-cprover-async/
    check-src/benchmark-sources/intabs/<case>/improved-pipeline/

Required after extraction:
  1. Update check-src/benchmark-sources/intabs/PROVENANCE.md with exact commit and license.
  2. Add support declarations under check-src/benchmark-sources/intabs/support/.
  3. Enable validated cases in check-src/benchmarks/suites/intabs-interrupts.json.
MSG
```

- [ ] **Step 3: Add verifier compatibility support**

Create `check-src/benchmark-sources/intabs/support/verifier_compat.h`:

```c
#ifndef CHECK_SRC_INTABS_VERIFIER_COMPAT_H
#define CHECK_SRC_INTABS_VERIFIER_COMPAT_H

extern _Bool __VERIFIER_nondet_bool(void);
extern char __VERIFIER_nondet_char(void);
extern int __VERIFIER_nondet_int(void);
extern unsigned int __VERIFIER_nondet_uint(void);
extern long __VERIFIER_nondet_long(void);
extern unsigned long __VERIFIER_nondet_ulong(void);

void __VERIFIER_assume(int condition);
void __VERIFIER_error(void);

#endif
```

- [ ] **Step 4: Add generated compatibility implementation**

Create `check-src/benchmark-sources/intabs/support/verifier_compat.c`:

```c
#include "verifier_compat.h"

void __VERIFIER_assume(int condition)
{
  __CPROVER_assume(condition);
}

void __VERIFIER_error(void)
{
  __CPROVER_assert(0, "__VERIFIER_error");
}
```

- [ ] **Step 5: Add first IntAbs manifest case**

Pick the smallest imported interrupt-driven C benchmark that has clear ISR functions.

Expected manifest shape:

```json
{
  "suite_name": "intabs-interrupts",
  "description": "IntAbs interrupt-driven benchmarks imported from ChunghaSung/intAbs.",
  "enabled": true,
  "runs": 5,
  "warmups": 1,
  "variants": ["stock_cprover_async", "improved_pipeline"],
  "cases": [
    {
      "name": "intabs-small-001",
      "enabled": true,
      "variant_roots": {
        "stock_cprover_async": "check-src/benchmark-sources/intabs/<case-name>/stock-cprover-async",
        "improved_pipeline": "check-src/benchmark-sources/intabs/<case-name>/improved-pipeline"
      },
      "sources": ["main.c", "../../support/verifier_compat.c"],
      "include_dirs": [".", "../../support"],
      "isr_sources": ["main.c"],
      "isr_functions": ["isr"],
      "entry_function": "main",
      "properties": [],
      "unwind": 3,
      "defines": ["CBMC"],
      "expected_result": "same-result",
      "timeout_sec": 900,
      "memory_limit_mb": 16384
    }
  ]
}
```

Adjust names and source paths after inspecting the real repository layout.

- [ ] **Step 6: Run Docker validation for IntAbs**

Run:

```bash
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo -e STOCK_CBMC=/repo/check-src/benchmarks/work/stock-toolchain/bin/cbmc -e STOCK_GOTOCC=/repo/check-src/benchmarks/work/stock-toolchain/bin/goto-cc -e IMPROVED_CBMC=/repo/cmake-build-debug-cbmc/bin/cbmc -e IMPROVED_GOTOCC=/repo/cmake-build-debug-cbmc/bin/goto-cc -e AIB=/repo/cmake-build-debug-cbmc/bin/aib bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-interrupts.json"
```

Expected: CSV is written to `check-src/benchmarks/results/intabs-interrupts.csv`. If a case fails compile, keep it disabled and record the exact blocker in the case `reason`.

---

### Task 6: Update Benchmark Reporting for New Suites

**Files:**
- Modify: `check-src/benchmark.md`
- Modify: `check-src/benchmarks/README.md`
- Optional modify: `check-src/benchmarks/common/report.sh`

- [ ] **Step 1: Generate summary for all CSV files**

Run:

```bash
bash check-src/benchmarks/common/report.sh check-src/benchmarks/results
```

Expected: `check-src/benchmarks/results/summary.md` is generated locally.

- [ ] **Step 2: Update `check-src/benchmark.md` in English**

Replace Vietnamese headings and prose with English. Keep existing Trampoline numbers, then append sections:

```markdown
## i-CBMC Results

Raw CSV: `check-src/benchmarks/results/icbmc-interrupts.csv`

...

## IntAbs Results

Raw CSV: `check-src/benchmarks/results/intabs-interrupts.csv`

...
```

Only add numerical tables for suites that produced CSV in Docker. For suites that are imported but not fully runnable, write a short English status section with the exact compile or normalization blocker.

- [ ] **Step 3: Update suite descriptions in `check-src/benchmarks/README.md`**

Translate all Vietnamese text to English and update the suite table so:

```markdown
| `icbmc-interrupts.json` | Yes/No based on runnable cases | i-CBMC interrupt cases imported from CPROVER artifacts. |
| `intabs-interrupts.json` | Yes/No based on runnable cases | IntAbs interrupt-driven C benchmarks imported from ChunghaSung/intAbs. |
```

---

### Task 7: Convert All `check-src` Markdown to English

**Files:**
- Modify: every file returned by `rg --files .\check-src | rg '\.md$'`

- [ ] **Step 1: Translate `check-src/benchmark.md`**

Replace these Vietnamese terms consistently:

```text
Ngay chay -> Run date
Moi truong -> Environment
Quy mo source -> Source size
CBMC goc -> Stock CBMC
CBMC cai tien -> Improved CBMC
Ket qua do duoc -> Measured results
So sanh truc tiep -> Direct comparison
Ghi chu -> Note
Ket qua verification -> Verification results
Ket luan -> Conclusion
it RAM hon -> less RAM
cham hon -> slower
nhanh hon -> faster
```

- [ ] **Step 2: Translate `check-src/benchmarks/README.md`**

Rewrite all prose and table headers in English. Preserve:

- file paths
- command examples
- JSON field names
- measured numbers
- suite names
- variant names

- [ ] **Step 3: Scan remaining Markdown**

Run:

```powershell
rg -n "[^\x00-\x7F]|\b(Ngay|Ket|qua|duoc|Ghi chu|goc|cai tien|cham hon|it RAM|Thu muc|Y nghia|Tac dung|Cach|duong dan|nguon)\b" .\check-src -g "*.md"
```

Expected: no matches, except false positives inside code, path names, or external quoted content. If there are false positives, inspect and document why they are acceptable.

- [ ] **Step 4: Keep Markdown ASCII unless existing content requires Unicode**

After edits, verify the files are not accidentally written as UTF-16:

```powershell
$bad = Get-ChildItem -Path .\check-src -Recurse -File -Include *.md | Where-Object {
  $b=[System.IO.File]::ReadAllBytes($_.FullName)
  $b.Length -ge 2 -and $b[0] -eq 0xff -and $b[1] -eq 0xfe
}
$bad
```

Expected: no output.

---

### Task 8: Final Verification

**Files:**
- Verify: `check-src/benchmarks/tests/selftest.ps1`
- Verify: `check-src/benchmarks/suites/*.json`
- Verify: `check-src/benchmark.md`
- Verify: `check-src/benchmarks/README.md`

- [ ] **Step 1: Run structural selftest**

Run:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

Expected: `selftest ok`.

- [ ] **Step 2: Run Docker dry-run for all enabled suites**

Run:

```bash
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 -m py_compile check-src/benchmarks/common/runner.py check-src/benchmarks/common/inject_naive.py && bash check-src/benchmarks/run_all.sh --dry-run"
```

Expected: enabled cases are listed without missing path errors.

- [ ] **Step 3: Run Docker benchmark for imported suites**

Run the i-CBMC and IntAbs suites individually:

```bash
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo -e STOCK_CBMC=/repo/check-src/benchmarks/work/stock-toolchain/bin/cbmc -e STOCK_GOTOCC=/repo/check-src/benchmarks/work/stock-toolchain/bin/goto-cc -e IMPROVED_CBMC=/repo/cmake-build-debug-cbmc/bin/cbmc -e IMPROVED_GOTOCC=/repo/cmake-build-debug-cbmc/bin/goto-cc -e AIB=/repo/cmake-build-debug-cbmc/bin/aib bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-interrupts.json && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-interrupts.json"
```

Expected: CSV files exist for every enabled imported suite. Disabled cases must have clear English `reason` fields.

- [ ] **Step 4: Run English-only Markdown scan**

Run:

```powershell
rg -n "[^\x00-\x7F]|\b(Ngay|Ket|qua|duoc|Ghi chu|goc|cai tien|cham hon|it RAM|Thu muc|Y nghia|Tac dung|Cach)\b" .\check-src -g "*.md"
```

Expected: no untranslated Vietnamese docs remain.

- [ ] **Step 5: Report final status**

Final response must include:

- imported i-CBMC cases enabled/disabled
- imported IntAbs cases enabled/disabled
- generated CSV paths
- whether Docker benchmark completed
- list of Markdown files translated
- any remaining blockers with exact file/case names

---

## Self-Review

- Spec coverage: The plan covers both requested tasks: adding i-CBMC/IntAbs benchmarks and translating `check-src` Markdown to English.
- Placeholder scan: The plan uses explicit files, commands, expected outputs, and status rules. Artifact-specific license/hash values must be filled only after the actual download because inventing them would be unsafe.
- Type consistency: Manifest fields match `manifest.schema.json`; commands match the current Docker benchmark workflow.
