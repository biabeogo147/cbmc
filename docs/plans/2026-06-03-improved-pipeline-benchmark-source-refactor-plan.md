# Improved Pipeline Benchmark Source Refactor Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Refactor `check-src/benchmark-sources` so every improved benchmark case follows the real interleaving pipeline demonstrated by `check-src/simple-benchmarks/*`, while every stock benchmark case remains a stock CBMC/C_ASYNC_PROVER model.

**Architecture:** Treat each benchmark case as one logical program with two modeling variants. The stock variant keeps explicit C_ASYNC_PROVER-style interrupt modeling; the improved variant keeps ISR definitions under `isr_define/`, generates an interleaving manifest with improved `goto-cc`, injects with `aib`, rebuilds the injected tree from the injected manifest's `project.translation_units`, then verifies with improved `cbmc`.

**Tech Stack:** Python benchmark runner, suite JSON manifests, CBMC/goto-cc/aib, Docker Linux benchmark container, Markdown reports.

---

## Findings From The Simple Benchmarks

The simple benchmarks define the intended improved-pipeline contract:

- `check-src/simple-benchmarks/t_isr_multifile/isr_define/isr.c`
- `check-src/simple-benchmarks/osek_priority_interleaving/isr_define/isr.c`
- `check-src/simple-benchmarks/osek_event_interleaving/isr_define/isr.c`

Each ISR source is placed under `isr_define/`, and each ISR body is wrapped in `__CPROVER_atomic_begin()` / `__CPROVER_atomic_end()`.

`check-src/simple-benchmarks/Interleaving Pipeline Checking.md` defines the pipeline:

1. Compile the original improved source with improved `goto-cc`.
2. Pass `--interleaving-project-root <project-root>`.
3. Pass `--interleaving-source-files <project-root>/isr_define/isr.c`.
4. Write `interleaving_harness.json`.
5. Run `aib <project-root> <manifest> <output-root> <output-root>/interleaving_harness_injected.json`.
6. Rebuild the injected tree using `project.translation_units` from the injected manifest.
7. Run improved `cbmc` on the injected goto binary.

The current benchmark framework partially implements this, but it still has two mismatches:

- Many `benchmark-sources` improved variants keep ISR code in `main.c` or top-level `isr.c` instead of `isr_define/isr.c`.
- `check-src/benchmarks/common/runner.py` rebuilds improved injected trees using the original manifest `sources`, not the injected manifest's `project.translation_units`.

## Target Benchmark Source Layout

Each normalized case should use this structure:

```text
check-src/benchmark-sources/<corpus>/cases/<case>/
  CASE.md
  stock-cprover-async/
    main.c
    ...
  improved-pipeline/
    .aibignore
    main.c
    task_define/
      tasks.c
      tasks.h
    isr_define/
      isr.c
      isr.h
    ...
```

For cases where the foreground code is still a single harness file, `task_define/` is optional. `isr_define/` is not optional for improved-pipeline headline cases.

Stock variant requirements:

- Keep explicit C_ASYNC_PROVER-compatible modeling, normally `__CPROVER_ASYNC_*:` labels or equivalent stock-CBMC interrupt launch code.
- Do not run `aib`.
- Compile and verify with stock `goto-cc` and stock `cbmc`.

Improved variant requirements:

- No active `__CPROVER_ASYNC_*:` labels in the improved source.
- ISR entry functions live in `isr_define/isr.c`.
- ISR declarations live in `isr_define/isr.h`.
- ISR bodies are atomic.
- Foreground/task code includes `isr_define/isr.h` only when prototypes are needed by the C compiler.
- `isr_define/isr.c` is passed through `--interleaving-source-files`.
- Rebuild after `aib` uses the injected manifest's `project.translation_units`.

## Task 1: Add Runner Support For The Real Injected Manifest Contract

**Files:**
- Modify: `check-src/benchmarks/common/runner.py`
- Modify: `check-src/benchmarks/tests/selftest.ps1`
- Modify: `check-src/benchmarks/PIPELINE.md`

- [ ] **Step 1: Add a unit-level selftest case for injected translation units**

Create a tiny test fixture under the PowerShell selftest temp directory with:

```json
{
  "project": {
    "project_root": "/tmp/original",
    "interleaving_source_files": ["isr_define/isr.c"],
    "translation_units": ["main.c", "isr_define/isr.c", "task_define/tasks.c"]
  },
  "interleaving": []
}
```

Expected behavior: runner helper returns these three translation units and later resolves them under the injected output root, not under the original source root.

- [ ] **Step 2: Implement `translation_units_from_manifest()`**

Add this helper to `runner.py`:

```python
def translation_units_from_manifest(manifest_path):
    data = json.loads(manifest_path.read_text(encoding="utf-8"))
    units = data.get("project", {}).get("translation_units", [])
    if not units:
        raise ValueError(f"{manifest_path}: missing project.translation_units")
    return units
```

- [ ] **Step 3: Use injected translation units after `aib`**

In `run_improved_pipeline()`, after successful `aib`, compile with:

```python
injected_sources = translation_units_from_manifest(injected_manifest)
improved_compile = [
    str(improved_gotocc),
    *rel_args(targeted, include_dirs_for(case, variant), "-I"),
    *define_args(case),
    *source_args(targeted, injected_sources),
    "-o",
    str(improved_out),
]
```

If there are `NO_INJECTION_CANDIDATES`, keep copying `original` to `targeted`, but write a synthetic injected manifest containing the original `variant_sources` as `project.translation_units` so the compile path stays identical.

- [ ] **Step 4: Add variant include dirs**

Add:

```python
def include_dirs_for(case, variant=None):
    variant_include_dirs = case.get("variant_include_dirs", {})
    if variant in variant_include_dirs:
        return variant_include_dirs[variant]
    return case["include_dirs"]
```

Replace direct `case["include_dirs"]` usage in compile commands with `include_dirs_for(case, variant)`.

- [ ] **Step 5: Add variant CBMC args**

Add manifest support:

```json
"cbmc_args": ["--unwinding-assertions"],
"variant_cbmc_args": {
  "stock_cprover_async": ["--os-api", "osek", "--osek-oil", "app.oil"],
  "improved_pipeline": ["--os-api", "osek", "--osek-oil", "app.oil"]
}
```

Add a helper:

```python
def cbmc_extra_args(case, variant, root):
    args = []
    args.extend(case.get("cbmc_args", []))
    args.extend(case.get("variant_cbmc_args", {}).get(variant, []))
    resolved = []
    path_options = {"--osek-oil"}
    index = 0
    while index < len(args):
        item = args[index]
        resolved.append(item)
        if item in path_options and index + 1 < len(args):
            index += 1
            value = Path(args[index])
            resolved.append(str(value if value.is_absolute() else root / value))
        index += 1
    return resolved
```

Append this result in `verify_args()` or at each verify command site.

- [ ] **Step 6: Verify runner support**

Run:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

Expected:

```text
selftest ok
```

Run:

```powershell
$py = "$env:USERPROFILE\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe"
Get-ChildItem .\check-src\benchmarks\common -Filter *.py | ForEach-Object { & $py -m py_compile $_.FullName; if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE } }
```

Expected: exit code `0`.

## Task 2: Refactor i-CBMC Improved Cases Into `isr_define`

**Files:**
- Modify directories under: `check-src/benchmark-sources/icbmc/cases/*/improved-pipeline/`
- Modify: `check-src/benchmarks/suites/icbmc-large.json`
- Modify: `check-src/benchmark-sources/icbmc/cases/*/CASE.md`

- [ ] **Step 1: Audit each enabled i-CBMC case**

For each enabled case in `icbmc-large.json`:

- `blink`
- `blink-bug`
- `rc-core`
- `rc-core-bug`

Run:

```powershell
rg -n "__CPROVER_ASYNC|pthread_create|VirtualizeTimerC_0_updateFromTimer_runTask|AlarmToTimerC_0_fired_runTask|show_protocols_ldvwrapper|ir_devnode_ldvwrapper|store_protocols_ldvwrapper" .\check-src\benchmark-sources\icbmc\cases\<case>
```

Expected:

- Stock variant contains active C_ASYNC_PROVER-style modeling.
- Improved variant contains no active C_ASYNC_PROVER launch labels.
- ISR functions listed in `isr_functions` exist exactly once in improved source.

- [ ] **Step 2: Move improved ISR definitions**

For each improved case, create:

```text
improved-pipeline/isr_define/isr.c
improved-pipeline/isr_define/isr.h
```

Move the functions listed in `isr_functions` from `improved-pipeline/main.c` into `isr_define/isr.c`.

If a moved ISR uses shared globals or helper functions from `main.c`, make those declarations visible through a case-local header:

```text
improved-pipeline/task_define/shared.h
```

Only move the minimum required declarations. Do not turn unrelated internal helpers into global declarations.

- [ ] **Step 3: Make every ISR atomic**

Each moved ISR body must follow this shape:

```c
void *example_isr(void *arg)
{
  (void)arg;

  __CPROVER_atomic_begin();
  /* original ISR body */
  __CPROVER_atomic_end();

  return 0;
}
```

For ISR functions returning non-pointer types, preserve the original return type and return value, but keep the side-effecting body inside the atomic block.

- [ ] **Step 4: Add `.aibignore` to each improved case**

Each improved case should ignore generated artifacts:

```text
# Generated benchmark artifacts
*.out
interleaving_harness.json
interleaving_harness_injected.json

# Upstream or local scratch output
*.i
*.log
```

If wildcard support is not available in `aib`, replace wildcard lines with exact generated file names used by that case.

- [ ] **Step 5: Update `icbmc-large.json`**

For each refactored case, set:

```json
"variant_sources": {
  "improved_pipeline": ["main.c", "isr_define/isr.c"]
},
"variant_include_dirs": {
  "improved_pipeline": [".", "isr_define", "task_define"]
},
"variant_isr_sources": {
  "improved_pipeline": ["isr_define/isr.c"]
}
```

Keep stock sources pointed at the stock root and stock C_ASYNC_PROVER file list.

- [ ] **Step 6: Smoke one case in Docker**

Run:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-large.json --case blink"
```

Expected:

- `manifest` phase exits `0`.
- `inject` phase is not `NO_INJECTION_CANDIDATES` unless the manifest genuinely has no candidate insertion lines.
- `compile` phase uses injected `project.translation_units`.

## Task 3: Refactor IntAbs Improved Cases Into `isr_define`

**Files:**
- Modify directories under: `check-src/benchmark-sources/intabs/cases/*/improved-pipeline/`
- Modify: `check-src/benchmarks/suites/intabs-large.json`
- Modify: `check-src/benchmark-sources/intabs/cases/*/CASE.md`

- [ ] **Step 1: Audit current IntAbs split**

Run:

```powershell
rg -n "__CPROVER_ASYNC|pthread_create|void \\*|int .*\\(" .\check-src\benchmark-sources\intabs\cases
```

Expected:

- Stock variants preserve C_ASYNC_PROVER modeling.
- Improved variants do not actively launch ISR/task functions with C_ASYNC_PROVER.
- Current top-level `improved-pipeline/isr.c` files contain the functions listed in `isr_functions`.

- [ ] **Step 2: Move top-level improved ISR files**

For each enabled IntAbs case with `improved-pipeline/isr.c`, move it to:

```text
improved-pipeline/isr_define/isr.c
```

Create:

```text
improved-pipeline/isr_define/isr.h
```

Update `main.c` includes only when prototypes or shared declarations are needed.

- [ ] **Step 3: Preserve driver code as ISR source when necessary**

Some IntAbs files, such as watchdog driver cases, contain driver code plus ISR/task functions in the same large source file. Do not shrink these files only to improve LOC accounting. If the full driver source is the ISR source, keep it as `isr_define/isr.c` and keep `main.c` as the foreground harness.

- [ ] **Step 4: Make every configured ISR atomic**

Wrap each configured `isr_functions` body with `__CPROVER_atomic_begin()` / `__CPROVER_atomic_end()`.

If the function has several early returns, refactor to one exit path so the atomic block is always closed.

- [ ] **Step 5: Update `intabs-large.json`**

For each refactored case, set:

```json
"variant_sources": {
  "improved_pipeline": ["main.c", "isr_define/isr.c"]
},
"variant_include_dirs": {
  "improved_pipeline": [".", "isr_define"]
},
"variant_isr_sources": {
  "improved_pipeline": ["isr_define/isr.c"]
}
```

Keep stock sources as `["main.c"]` unless stock has a deliberate multi-file C_ASYNC_PROVER model.

- [ ] **Step 6: Smoke one known comparable case in Docker**

Run:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-large.json --case sc520wdt-1"
```

Expected:

- `manifest`, `inject`, `compile`, and `verify` rows are written for improved.
- The raw manifest has `project.interleaving_source_files` equal to `["isr_define/isr.c"]` or the absolute path equivalent before filtering.

## Task 4: Reconcile Trampoline With The Same Contract

**Files:**
- Modify: `check-src/benchmarks/suites/trampoline-expanded.json`
- Modify or remove if redundant: `check-src/benchmarks/suites/trampoline-current.json`
- Modify or remove if redundant: `check-src/benchmarks/suites/trampoline-c-async.json`
- Modify: `check-src/benchmark-sources/trampoline/PROVENANCE.md`
- Modify: `check-src/benchmark-sources/README.md`

- [ ] **Step 1: Keep the full-source improved Trampoline layout**

The existing improved source already has:

```text
tests/functional/alarms_s1_non/isr_define/isr.c
```

Keep that path as the `isr_sources` value for improved pipeline.

- [ ] **Step 2: Remove suite duplication from the comparison path**

Use one comparable Trampoline suite with both variants:

```json
"variants": ["stock_cprover_async", "improved_pipeline"],
"variant_roots": {
  "stock_cprover_async": "check-src/benchmark-sources/trampoline/stock-cprover-async",
  "improved_pipeline": "check-src/benchmark-sources/trampoline/improved-pipeline"
}
```

Keep `trampoline-c-async.json` only if it is explicitly documented as stock-only diagnostic. Do not include stock-only suites in `benchmark.md`; they belong in `uncomparable.md`.

- [ ] **Step 3: Add OSEK verification args if the case requires OSEK semantics**

If the Trampoline case needs OSEK modeling, add:

```json
"cbmc_args": ["--unwinding-assertions"],
"variant_cbmc_args": {
  "stock_cprover_async": ["--os-api", "osek", "--osek-oil", "tests/functional/alarms_s1_non/alarms_s1_non.oil"],
  "improved_pipeline": ["--os-api", "osek", "--osek-oil", "tests/functional/alarms_s1_non/alarms_s1_non.oil"]
}
```

Use the real OIL path from the Trampoline source tree after auditing with:

```powershell
rg --files .\check-src\benchmark-sources\trampoline | rg "alarms_s1.*\.oil$"
```

## Task 5: Update Documentation To Match The Real Pipeline

**Files:**
- Modify: `check-src/benchmarks/PIPELINE.md`
- Modify: `check-src/benchmarks/README.md`
- Modify: `check-src/benchmark-sources/README.md`
- Modify: `check-src/benchmark.md`
- Modify: `check-src/uncomparable.md`

- [ ] **Step 1: Add the improved source contract**

Document that improved headline cases must have:

```text
improved-pipeline/isr_define/isr.c
```

or a clearly configured deeper path such as Trampoline's:

```text
tests/functional/alarms_s1_non/isr_define/isr.c
```

- [ ] **Step 2: Document stock vs improved modeling**

Add a table:

| Variant | Meaning | Required modeling |
| --- | --- | --- |
| `stock_cprover_async` | Stock CBMC baseline | C_ASYNC_PROVER-compatible explicit interrupt modeling |
| `improved_pipeline` | Improved CBMC pipeline | `goto-cc --interleaving-*`, `aib`, injected rebuild, improved `cbmc` |

- [ ] **Step 3: Document injected rebuild behavior**

State that after `aib`, runner compiles files from:

```text
<injected-output-root>/interleaving_pipeline_injected.json
```

using:

```json
project.translation_units
```

not from the original suite `sources` list.

## Task 6: Run Full Docker Benchmark And Regenerate Reports

**Files:**
- Modify generated output: `check-src/benchmarks/results/*.csv`
- Modify generated output: `check-src/benchmark.md`
- Modify generated output: `check-src/uncomparable.md`
- Modify generated output: `check-src/benchmark-sources/INVENTORY.md`

- [ ] **Step 1: Run structural checks**

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

Expected:

```text
selftest ok
```

- [ ] **Step 2: Run Docker smoke benchmarks**

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/local-smoke.json && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/osek-local.json"
```

Expected:

- Improved simple cases emit manifest and inject phases.
- OSEK cases pass their configured OSEK options to CBMC.

- [ ] **Step 3: Run headline Docker benchmarks**

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-large.json && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-large.json && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/trampoline-expanded.json"
```

Expected:

- Each enabled case has measured stock compile/verify rows.
- Each enabled improved case has measured manifest/inject/compile/verify rows.
- Improved compile logs show injected source paths.

- [ ] **Step 4: Regenerate inventory and reports**

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/corpus_inventory.py && python3 check-src/benchmarks/common/report_benchmark.py"
```

Expected:

```text
report rows loaded: <non-zero>
report: /repo/check-src/benchmark.md
uncomparable report: /repo/check-src/uncomparable.md
```

- [ ] **Step 5: Validate report split**

```powershell
rg -n "Not comparable:" .\check-src\benchmark.md
rg -n "Not comparable:|No measured CSV rows" .\check-src\uncomparable.md
```

Expected:

- First command has no matches.
- Second command lists non-comparable reasons only in `uncomparable.md`.

## Acceptance Criteria

- Every improved headline case has ISR source under `isr_define/` or an explicitly documented deeper `isr_define/` path.
- Every configured improved ISR function is atomic.
- Every stock headline case uses stock C_ASYNC_PROVER-compatible modeling and does not run `aib`.
- Runner rebuilds improved injected trees from injected manifest `project.translation_units`.
- OSEK cases can pass `--os-api osek` and `--osek-oil <file>` through suite JSON.
- Docker benchmark can regenerate CSV files plus both Markdown reports.
- `benchmark.md` contains only comparable cases.
- `uncomparable.md` contains non-comparable cases with explicit reasons.

