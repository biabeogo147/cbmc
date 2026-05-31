# CBMC Comparison Benchmark Refactor Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Refactor `check-src` into a reliable benchmark system that compares stock CBMC and the improved CBMC pipeline on sufficiently large interrupt/model-checking corpora.

**Architecture:** Keep all source corpora under `check-src/benchmark-sources`, separate collected upstream sources from runnable normalized benchmark cases, and require every headline case to have two variants: `stock-cprover-async` for stock CBMC and `improved-pipeline` for the improved interleaving pipeline. Add inventory, normalization, manifest, repeated-run, and reporting layers so `benchmark.md` is generated from validated Docker CSV results rather than hand-written from smoke runs.

**Tech Stack:** Python 3 runner/report scripts, JSON suite manifests, Docker Linux runs for RSS measurement, stock CBMC 5.95.0, improved CBMC/goto-cc/aib from `cmake-build-debug-cbmc/bin`.

---

## Execution Status - 2026-05-30

Implemented in the current repository:

- Added corpus inventory, candidate scan, normalization, and report-generation scripts.
- Added staged normalized i-CBMC and IntAbs large-case directories under `check-src/benchmark-sources/*/cases`.
- Added disabled `icbmc-large.json` and `intabs-large.json` manifests so staged external cases are visible but cannot be reported as headline results before validation.
- Updated the runner for warmups, repeated measured runs, `run_kind`, variant filtering, LOC gates, and line-buffered CSV output.
- Regenerated `check-src/benchmark.md` from Docker CSV data.
- Ran Docker validation and a full 1-warmup/5-measured-run `trampoline-current` benchmark.

External i-CBMC/IntAbs cases remain intentionally disabled because their improved-pipeline compile/inject/verify gates have not been completed yet. They are collected and staged, but not presented as headline speed/RAM evidence.

---

## Current State

- Trampoline has real runnable variants:
  - `check-src/benchmark-sources/trampoline/stock-cprover-async`
  - `check-src/benchmark-sources/trampoline/improved-pipeline`
- i-CBMC upstream corpus is collected:
  - `check-src/benchmark-sources/icbmc/upstream`
  - 232 C/H/I files, 216799 LOC
- IntAbs upstream corpus is collected:
  - `check-src/benchmark-sources/intabs/upstream/repository`
  - 120 C/H/I files, 87868 LOC
- i-CBMC/IntAbs Logger cases are smoke-only and must stay disabled until larger cases are normalized.
- `check-src/benchmarks/common/runner.py` already supports `stock_cprover_async` and `improved_pipeline`, but repeated runs, warmups, case-size gating, and generated benchmark reporting still need to be added.

## Refactor Rules

1. Do not run or report headline i-CBMC/IntAbs benchmark numbers until each enabled external case is large enough.
2. Minimum external headline suite gate:
   - at least 5 enabled cases per corpus, or
   - at least 5000 compile LOC per corpus if fewer cases are temporarily available.
3. Every enabled headline case must have both variants:
   - `stock_cprover_async`: source modeled with CPROVER async labels or equivalent stock-compatible async modeling.
   - `improved_pipeline`: source modeled for `goto-cc --interleaving-*` and `aib`.
4. Verification outcomes must be classified before speed/RAM comparisons:
   - `comparable`: same CBMC summary class and same selected property result.
   - `not_comparable`: unsupported concurrency, compile failure, timeout, memory kill, or different verification outcome.
5. `benchmark.md` must state when a comparison is not comparable instead of forcing a speedup/RAM-reduction headline.

## File Structure

### Create

- `check-src/benchmarks/common/corpus_inventory.py`
  - Counts C/H/I files and LOC for each corpus and candidate case.
  - Emits JSON and Markdown inventory.
- `check-src/benchmarks/common/candidate_scan.py`
  - Scans upstream i-CBMC/IntAbs folders for candidate C programs, async labels, pthread/thread metadata, likely ISR/task functions, `main`, and `assert`.
- `check-src/benchmarks/common/normalize_case.py`
  - Creates `stock-cprover-async` and `improved-pipeline` directories for a selected case.
  - Does only mechanical normalization needed for benchmark execution.
- `check-src/benchmarks/common/report_benchmark.py`
  - Reads CSV files, computes median time/RSS, classifies comparability, and writes `check-src/benchmark.md`.
- `check-src/benchmarks/suites/icbmc-large.json`
  - Enabled only after at least the first large i-CBMC cases compile in both variants.
- `check-src/benchmarks/suites/intabs-large.json`
  - Enabled only after at least the first large IntAbs cases compile in both variants.
- `check-src/benchmark-sources/icbmc/cases/`
  - Normalized runnable i-CBMC cases.
- `check-src/benchmark-sources/intabs/cases/`
  - Normalized runnable IntAbs cases.
- `check-src/benchmark-sources/INVENTORY.md`
  - Generated corpus and case inventory.

### Modify

- `check-src/benchmarks/common/runner.py`
  - Implement `runs` and `warmups`.
  - Record `run_kind` as `warmup` or `measure`.
  - Add optional per-case `min_compile_loc`.
  - Add explicit command-line flags: `--case`, `--variant`, `--list-cases`.
- `check-src/benchmarks/manifest.schema.json`
  - Add schema for `variant_roots`, `min_compile_loc`, `expected_summary`, and `case_origin`.
- `check-src/benchmarks/run_all.sh`
  - Ensure it skips disabled suites and writes a combined summary.
- `check-src/benchmark.md`
  - Replace manual report with generated output from `report_benchmark.py`.
- `check-src/benchmark-sources/README.md`
  - Document candidate selection, normalization status, and size gates.
- `check-src/benchmarks/README.md`
  - Document repeated runs, generated report, and comparability rules.

---

## Task 1: Add Corpus Inventory Tool

**Files:**
- Create: `check-src/benchmarks/common/corpus_inventory.py`
- Create/update generated output: `check-src/benchmark-sources/INVENTORY.md`

- [ ] **Step 1: Create the inventory script**

Add `check-src/benchmarks/common/corpus_inventory.py`:

```python
#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

SOURCE_SUFFIXES = {".c", ".h", ".i"}


def count_source(root: Path):
    files = [p for p in root.rglob("*") if p.is_file() and p.suffix in SOURCE_SUFFIXES]
    loc = 0
    for path in files:
        loc += len(path.read_text(errors="ignore").splitlines())
    return {"files": len(files), "loc": loc}


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--json-out")
    parser.add_argument("--md-out", default="check-src/benchmark-sources/INVENTORY.md")
    args = parser.parse_args(argv)

    repo = Path(args.repo_root).resolve()
    roots = {
        "trampoline-stock-cprover-async": repo / "check-src/benchmark-sources/trampoline/stock-cprover-async",
        "trampoline-improved-pipeline": repo / "check-src/benchmark-sources/trampoline/improved-pipeline",
        "icbmc-upstream": repo / "check-src/benchmark-sources/icbmc/upstream",
        "icbmc-po-code": repo / "check-src/benchmark-sources/icbmc/upstream/extracted/po-code",
        "icbmc-seq-code": repo / "check-src/benchmark-sources/icbmc/upstream/extracted/seq-code",
        "icbmc-conc-code": repo / "check-src/benchmark-sources/icbmc/upstream/extracted/conc-code",
        "intabs-upstream": repo / "check-src/benchmark-sources/intabs/upstream/repository",
        "intabs-icbmc": repo / "check-src/benchmark-sources/intabs/upstream/repository/icbmc",
        "intabs-src-test": repo / "check-src/benchmark-sources/intabs/upstream/repository/src/test",
    }
    inventory = {}
    for name, root in roots.items():
        if root.exists():
            inventory[name] = {"path": root.relative_to(repo).as_posix(), **count_source(root)}

    if args.json_out:
        Path(args.json_out).write_text(json.dumps(inventory, indent=2) + "\n", encoding="utf-8")

    lines = [
        "# Benchmark Source Inventory",
        "",
        "| Corpus | Path | C/H/I files | LOC |",
        "| --- | --- | ---: | ---: |",
    ]
    for name, item in inventory.items():
        lines.append(f"| `{name}` | `{item['path']}` | {item['files']} | {item['loc']} |")
    Path(args.md_out).write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"inventory entries: {len(inventory)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
```

- [ ] **Step 2: Run the inventory script**

Run in Docker:

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/corpus_inventory.py"
```

Expected:

```text
inventory entries: 9
```

- [ ] **Step 3: Verify inventory contains large corpora**

Run:

```powershell
Select-String -Path .\check-src\benchmark-sources\INVENTORY.md -Pattern "icbmc-upstream|intabs-upstream|216799|87868"
```

Expected: matches for i-CBMC and IntAbs upstream rows.

---

## Task 2: Add Candidate Scanner

**Files:**
- Create: `check-src/benchmarks/common/candidate_scan.py`
- Create generated output: `check-src/benchmark-sources/CANDIDATES.md`

- [ ] **Step 1: Create scanner script**

Add `check-src/benchmarks/common/candidate_scan.py`:

```python
#!/usr/bin/env python3
import argparse
import re
from dataclasses import dataclass
from pathlib import Path

SOURCE_SUFFIXES = {".c", ".i"}


@dataclass
class Candidate:
    name: str
    path: Path
    loc: int
    async_labels: int
    pthread_create: int
    verifier_threads: int
    assertions: int
    main_functions: int

    @property
    def score(self):
        return self.loc + self.async_labels * 500 + self.pthread_create * 500 + self.verifier_threads * 500 + self.assertions * 50


def inspect_file(path: Path, repo: Path):
    text = path.read_text(errors="ignore")
    loc = len(text.splitlines())
    return Candidate(
        name=path.with_suffix("").name,
        path=path.relative_to(repo),
        loc=loc,
        async_labels=len(re.findall(r"__CPROVER_ASYNC_", text)),
        pthread_create=len(re.findall(r"\bpthread_create\s*\(", text)),
        verifier_threads=len(re.findall(r"__VERIFIER_threads|__CPROVER_threads", text)),
        assertions=len(re.findall(r"\bassert\s*\(", text)),
        main_functions=len(re.findall(r"\bmain\s*\(", text)),
    )


def scan(root: Path, repo: Path):
    candidates = []
    for path in root.rglob("*"):
        if not path.is_file() or path.suffix not in SOURCE_SUFFIXES:
            continue
        item = inspect_file(path, repo)
        if item.main_functions and (item.async_labels or item.pthread_create or item.verifier_threads or item.assertions):
            candidates.append(item)
    return sorted(candidates, key=lambda item: item.score, reverse=True)


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--limit", type=int, default=30)
    parser.add_argument("--md-out", default="check-src/benchmark-sources/CANDIDATES.md")
    args = parser.parse_args(argv)

    repo = Path(args.repo_root).resolve()
    roots = [
        ("i-CBMC", repo / "check-src/benchmark-sources/icbmc/upstream/extracted"),
        ("IntAbs", repo / "check-src/benchmark-sources/intabs/upstream/repository"),
    ]
    lines = ["# Benchmark Candidate Scan", ""]
    for label, root in roots:
        items = scan(root, repo)[: args.limit]
        lines += [
            f"## {label}",
            "",
            "| Path | LOC | async labels | pthread_create | thread metadata | assert | score |",
            "| --- | ---: | ---: | ---: | ---: | ---: | ---: |",
        ]
        for item in items:
            lines.append(
                f"| `{item.path.as_posix()}` | {item.loc} | {item.async_labels} | "
                f"{item.pthread_create} | {item.verifier_threads} | {item.assertions} | {item.score} |"
            )
        lines.append("")
    Path(args.md_out).write_text("\n".join(lines), encoding="utf-8")
    print(f"candidate report: {args.md_out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
```

- [ ] **Step 2: Run candidate scan**

Run:

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/candidate_scan.py --limit 30"
```

Expected:

```text
candidate report: check-src/benchmark-sources/CANDIDATES.md
```

- [ ] **Step 3: Choose first normalization batch**

Use `CANDIDATES.md` to select:

```text
i-CBMC preferred first batch:
- po-code/blink/blink.c
- po-code/rc-core/rc_core.c
- po-code/logger1+2/logger2.c
- seq-code/brake/nobug/brake2_3_por_seq.c
- conc-code/brake/nobug/cprover/brake2_3_conc_cprover.c

IntAbs preferred first batch:
- icbmc/i2c_pca_isa_3/main.c
- icbmc/i8xx_tco_3/main.c
- icbmc/wdt_pci_3/main.c
- src/test/brake4/main.c
- src/test/logger3/main.c
```

If any listed file is missing, stop and update the selection in this plan before implementation.

---

## Task 3: Add Normalized Case Layout and Smoke Gate

**Files:**
- Create: `check-src/benchmark-sources/icbmc/cases/README.md`
- Create: `check-src/benchmark-sources/intabs/cases/README.md`
- Modify: `check-src/benchmark-sources/README.md`

- [ ] **Step 1: Add normalized case README files**

Create `check-src/benchmark-sources/icbmc/cases/README.md`:

```markdown
# i-CBMC Normalized Benchmark Cases

Each case directory must contain:

- `stock-cprover-async/`
- `improved-pipeline/`
- `CASE.md`

Do not enable a case in `icbmc-large.json` until both variants compile in Docker.
The corpus-level suite must have at least 5 enabled cases or at least 5000
compile LOC before `benchmark.md` can report it as a headline benchmark.
```

Create `check-src/benchmark-sources/intabs/cases/README.md`:

```markdown
# IntAbs Normalized Benchmark Cases

Each case directory must contain:

- `stock-cprover-async/`
- `improved-pipeline/`
- `CASE.md`

Do not enable a case in `intabs-large.json` until both variants compile in Docker.
The corpus-level suite must have at least 5 enabled cases or at least 5000
compile LOC before `benchmark.md` can report it as a headline benchmark.
```

- [ ] **Step 2: Update benchmark source README**

In `check-src/benchmark-sources/README.md`, add this policy section:

```markdown
## Headline Benchmark Gate

External i-CBMC and IntAbs benchmark suites are headline-ready only when:

- the suite has at least 5 enabled normalized cases, or at least 5000 compile LOC;
- every enabled case has `stock-cprover-async` and `improved-pipeline` variants;
- both variants compile in Docker;
- verification outcomes are classified as comparable or explicitly not comparable.
```

- [ ] **Step 3: Run selftest**

Run:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

Expected:

```text
selftest ok
```

---

## Task 4: Implement Repeated Runs and Warmups in Runner

**Files:**
- Modify: `check-src/benchmarks/common/runner.py`

- [ ] **Step 1: Add CSV field `run_kind`**

Modify the CSV field list in `runner.py`:

```python
fields = [
    "benchmark",
    "case",
    "variant",
    "phase",
    "run",
    "run_kind",
    "exit_code",
    "time_ms",
    "max_rss_kb",
    "max_rss_mb",
    "summary",
]
```

Every `writer.writerow` call must include `"run_kind": "measure"` or `"run_kind": "warmup"`. Prepare rows should use `"run_kind": "prepare"`.

- [ ] **Step 2: Pass run kind into `measure`**

Change the signature:

```python
def measure(..., run_id, run_kind, command, timeout_sec=None, memory_limit_mb=None):
```

Write `run_kind` into both success and command-start-failure CSV rows.

- [ ] **Step 3: Add repeated run loop**

In `run_case`, replace one-shot variant execution with:

```python
warmups = int(manifest.get("warmups", 0))
runs = int(manifest.get("runs", 1))
for run_kind, total in [("warmup", warmups), ("measure", runs)]:
    for run_index in range(1, total + 1):
        run_variant_set(csv_writer, manifest_path, suite, case, manifest, work_root, logs, variants, run_index, run_kind)
```

Implement `run_variant_set(...)` by moving the current per-case body into that helper and making `case_work` include run kind/id:

```python
case_work = work_root / suite / name / f"{run_kind}-{run_index}"
```

- [ ] **Step 4: Preserve backward compatibility**

When a manifest omits `runs` and `warmups`, expected behavior is:

```text
warmups = 0
runs = 1
```

- [ ] **Step 5: Verify dry-run does not create repeated output**

Run:

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 -m py_compile check-src/benchmarks/common/runner.py && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/trampoline-current.json --dry-run"
```

Expected:

```text
trampoline-current:trampoline-alarms-s1-non
```

---

## Task 5: Add Case-Size Gate

**Files:**
- Modify: `check-src/benchmarks/common/runner.py`
- Modify: `check-src/benchmarks/manifest.schema.json`

- [ ] **Step 1: Add compile LOC helper**

Add to `runner.py`:

```python
def compile_loc(root, sources):
    total = 0
    for source in sources:
        path = root / source
        total += len(path.read_text(errors="ignore").splitlines())
    return total
```

- [ ] **Step 2: Validate `min_compile_loc`**

In `validate_manifest`, after checking sources:

```python
min_compile_loc = int(case.get("min_compile_loc", 0))
if min_compile_loc:
    for variant in variants_for(manifest, case):
        root = case_root(case, variant)
        loc = compile_loc(root, case["sources"])
        if loc < min_compile_loc:
            raise ValueError(f"{case['name']}:{variant}: compile LOC {loc} < min_compile_loc {min_compile_loc}")
```

- [ ] **Step 3: Update schema**

Add optional fields under case properties in `manifest.schema.json`:

```json
"min_compile_loc": { "type": "integer", "minimum": 0 },
"case_origin": { "type": "string" },
"expected_summary": { "type": "string" }
```

- [ ] **Step 4: Verify smoke cases stay disabled**

Run:

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-interrupts.json --dry-run && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-interrupts.json --dry-run"
```

Expected: no enabled cases printed.

---

## Task 6: Normalize First Large i-CBMC Batch

**Files:**
- Create directories under `check-src/benchmark-sources/icbmc/cases/<case-name>/`
- Create/update: `check-src/benchmarks/suites/icbmc-large.json`

- [ ] **Step 1: Create case directories**

For each selected i-CBMC case, create:

```text
check-src/benchmark-sources/icbmc/cases/<case-name>/stock-cprover-async/
check-src/benchmark-sources/icbmc/cases/<case-name>/improved-pipeline/
check-src/benchmark-sources/icbmc/cases/<case-name>/CASE.md
```

Use case names:

```text
blink
rc-core
logger2
brake-seq-2-3
brake-conc-2-3
```

- [ ] **Step 2: Copy stock source**

Copy the selected upstream files into `stock-cprover-async` without removing existing `__CPROVER_ASYNC_*` labels.

Use this source mapping:

```text
blink -> icbmc/upstream/extracted/po-code/blink/blink.c
rc-core -> icbmc/upstream/extracted/po-code/rc-core/rc_core.c
logger2 -> icbmc/upstream/extracted/po-code/logger1+2/logger2.c
brake-seq-2-3 -> icbmc/upstream/extracted/seq-code/brake/nobug/brake2_3_por_seq.c plus required brake support files from the same directory
brake-conc-2-3 -> icbmc/upstream/extracted/conc-code/brake/nobug/cprover/brake2_3_conc_cprover.c plus required brake support files from the same directory
```

- [ ] **Step 3: Create improved source**

Copy the same sources into `improved-pipeline`, then remove only `__CPROVER_ASYNC_*:` labels from foreground source. Do not remove the ISR/task functions themselves.

For single-file cases, if `aib` fails because an ISR function has no insertion site, split the file into:

```text
main.c
isr.c
model.h
model.c
```

Keep the split minimal:

- declarations and globals in `model.h`/`model.c`;
- foreground `main` and driver code in `main.c`;
- async/task/ISR functions in `isr.c`.

- [ ] **Step 4: Write `CASE.md` per case**

Each `CASE.md` must include:

```markdown
# <case-name>

Origin: `<upstream relative path>`

Normalization:
- `stock-cprover-async`: preserves CPROVER async modeling.
- `improved-pipeline`: removes async labels and exposes ISR/task functions through `isr_sources`.

Compile files:
- `<file list used by manifest>`

ISR/task functions:
- `<function list used by manifest>`
```

- [ ] **Step 5: Create disabled manifest first**

Create `check-src/benchmarks/suites/icbmc-large.json` with:

```json
{
  "suite_name": "icbmc-large",
  "description": "Large i-CBMC interrupt benchmark cases normalized from CPROVER interrupt artifacts.",
  "enabled": false,
  "runs": 5,
  "warmups": 1,
  "variants": ["stock_cprover_async", "improved_pipeline"],
  "cases": []
}
```

- [ ] **Step 6: Add cases one by one**

For each case, add a manifest entry only after both variants compile. Each enabled entry must include:

```json
"min_compile_loc": 500,
"case_origin": "check-src/benchmark-sources/icbmc/upstream/..."
```

The suite stays top-level disabled until at least 5 cases compile.

---

## Task 7: Normalize First Large IntAbs Batch

**Files:**
- Create directories under `check-src/benchmark-sources/intabs/cases/<case-name>/`
- Create/update: `check-src/benchmarks/suites/intabs-large.json`

- [ ] **Step 1: Create case directories**

Use case names:

```text
i2c-pca-isa-3
i8xx-tco-3
wdt-pci-3
brake4
logger3
```

Each case must contain:

```text
stock-cprover-async/
improved-pipeline/
CASE.md
```

- [ ] **Step 2: Copy stock source**

Use this source mapping:

```text
i2c-pca-isa-3 -> intabs/upstream/repository/icbmc/i2c_pca_isa_3/main.c
i8xx-tco-3 -> intabs/upstream/repository/icbmc/i8xx_tco_3/main.c
wdt-pci-3 -> intabs/upstream/repository/icbmc/wdt_pci_3/main.c
brake4 -> intabs/upstream/repository/src/test/brake4/main.c plus required same-folder support source if needed
logger3 -> intabs/upstream/repository/src/test/logger3/main.c
```

- [ ] **Step 3: Normalize stock async model**

If the source uses pthreads:

```c
pthread_create(&t1, 0, task_name, 0);
```

replace in the stock variant with:

```c
__CPROVER_ASYNC_1:
task_name(0);
```

Keep each function body unchanged unless CBMC cannot compile a missing platform type.

- [ ] **Step 4: Normalize improved model**

For the improved variant:

- remove pthread/async launch syntax from `main`;
- keep foreground setup code in `main`;
- move task/ISR functions into `isr.c` if needed;
- pass `isr.c` through manifest `isr_sources`.

- [ ] **Step 5: Create disabled manifest first**

Create `check-src/benchmarks/suites/intabs-large.json`:

```json
{
  "suite_name": "intabs-large",
  "description": "Large IntAbs interrupt benchmark cases normalized from chunghasung/intabs.",
  "enabled": false,
  "runs": 5,
  "warmups": 1,
  "variants": ["stock_cprover_async", "improved_pipeline"],
  "cases": []
}
```

- [ ] **Step 6: Add cases one by one**

For each case, add a manifest entry only after both variants compile. Each enabled entry must include:

```json
"min_compile_loc": 500,
"case_origin": "check-src/benchmark-sources/intabs/upstream/repository/..."
```

The suite stays top-level disabled until at least 5 cases compile.

---

## Task 8: Add Benchmark Report Generator

**Files:**
- Create: `check-src/benchmarks/common/report_benchmark.py`
- Modify: `check-src/benchmark.md` only through generated output

- [ ] **Step 1: Create report generator**

Add `report_benchmark.py` with these responsibilities:

```text
Inputs:
- check-src/benchmarks/results/*.csv
- check-src/benchmarks/suites/*.json
- check-src/benchmark-sources/INVENTORY.md

Outputs:
- check-src/benchmark.md

Rules:
- ignore warmup rows;
- compute median per suite/case/variant/phase;
- compute full pipeline time by summing phase medians;
- compute peak RSS as max phase median RSS;
- mark comparisons not comparable when summaries differ or stock reports unsupported concurrency;
- never report speedup for not-comparable verification outcomes.
```

- [ ] **Step 2: Implement median helper**

Use Python standard library:

```python
from statistics import median
```

- [ ] **Step 3: Verify report generator on existing CSV**

Run:

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/report_benchmark.py --dry-run"
```

Expected:

```text
report rows loaded:
```

The exact row count depends on which CSV files exist.

---

## Task 9: Docker Verification Protocol

**Files:**
- Modify: `check-src/benchmarks/VERIFICATION_PROTOCOL.md`
- Modify: `check-src/benchmarks/README.md`

- [ ] **Step 1: Add required command block**

Document this command template:

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm `
  -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" `
  -w /repo `
  -e STOCK_CBMC=/repo/check-src/benchmarks/work/stock-toolchain/bin/cbmc `
  -e STOCK_GOTOCC=/repo/check-src/benchmarks/work/stock-toolchain/bin/goto-cc `
  -e IMPROVED_CBMC=/repo/cmake-build-debug-cbmc/bin/cbmc `
  -e IMPROVED_GOTOCC=/repo/cmake-build-debug-cbmc/bin/goto-cc `
  -e AIB=/repo/cmake-build-debug-cbmc/bin/aib `
  -e WORK=/repo/check-src/benchmarks/work/run-headline `
  -e RESULTS_DIR=/repo/check-src/benchmarks/results `
  bkmeeting-vpcd-aimet:ubuntu22.04-py310 `
  bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-large.json && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-large.json && python3 check-src/benchmarks/common/report_benchmark.py"
```

- [ ] **Step 2: Add failure interpretation**

Document:

```text
Exit 0: command succeeded.
Exit 10: CBMC verification failed and can still be a valid comparable result if both variants match.
Exit 6 or CBMC_UNSUPPORTED_CONCURRENCY: not comparable.
TIMEOUT_AFTER_*: not comparable.
MEMORY_LIMIT_EXCEEDED_*: not comparable.
Compile failure: not comparable.
```

---

## Task 10: Final Validation Before Benchmark Claims

**Files:**
- All files touched by previous tasks

- [ ] **Step 1: Structural selftest**

Run:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

Expected:

```text
selftest ok
```

- [ ] **Step 2: Python compile check**

Run:

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 -m py_compile check-src/benchmarks/common/*.py"
```

Expected: exit code 0.

- [ ] **Step 3: Dry-run enabled headline suites**

Run:

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/trampoline-current.json --dry-run && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-large.json --dry-run && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-large.json --dry-run"
```

Expected:

```text
trampoline-current:trampoline-alarms-s1-non
icbmc-large:<five or more enabled large cases>
intabs-large:<five or more enabled large cases>
```

- [ ] **Step 4: Run full Docker benchmark**

Run the command documented in Task 9.

Expected:

```text
results: /repo/check-src/benchmarks/results/icbmc-large.csv
results: /repo/check-src/benchmarks/results/intabs-large.csv
```

- [ ] **Step 5: Verify generated `benchmark.md`**

Check that `benchmark.md` contains:

```text
Stock CPROVER async
Improved pipeline
Comparable
Not comparable
Median
Peak RSS
```

If i-CBMC or IntAbs has fewer than 5 enabled large cases and less than 5000 compile LOC, the report must explicitly say the suite is not headline-ready.

---

## Completion Criteria

This refactor is complete only when:

- `check-src/benchmark-sources/INVENTORY.md` exists and shows large i-CBMC/IntAbs corpora.
- `check-src/benchmark-sources/CANDIDATES.md` exists and lists ranked candidates.
- `icbmc-large.json` and `intabs-large.json` contain large normalized cases, not Logger-only smoke cases.
- `runner.py` records warmups/measured runs separately.
- `report_benchmark.py` generates `check-src/benchmark.md`.
- Docker benchmark has been run after the large suites are enabled.
- `benchmark.md` reports speed/RAM percentages only for comparable outcomes and explicitly marks unsupported/different verification outcomes.
