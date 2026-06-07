param(
  [string]$Root = (Resolve-Path (Join-Path $PSScriptRoot "..\..\..")).Path
)

$ErrorActionPreference = "Stop"

function Assert-Path {
  param([string]$Path)
  if (-not (Test-Path -LiteralPath $Path)) {
    throw "Missing expected path: $Path"
  }
}

function Assert-Json {
  param([string]$Path)
  Assert-Path $Path
  Get-Content -LiteralPath $Path -Raw | ConvertFrom-Json | Out-Null
}

function Has-JsonProperty {
  param($Object, [string]$Name)
  return $Object.PSObject.Properties.Name.Contains($Name)
}

function Get-JsonProperty {
  param($Object, [string]$Name, $Default = $null)
  if (Has-JsonProperty $Object $Name) {
    return $Object.$Name
  }
  return $Default
}

function Get-VariantArray {
  param($Case, [string]$Field, [string]$Variant, $Default)
  $variantField = Get-JsonProperty $Case $Field
  if ($variantField -and (Has-JsonProperty $variantField $Variant)) {
    return @($variantField.$Variant)
  }
  return @($Default)
}

$checkSrc = Join-Path $Root "check-src"
$bench = Join-Path $checkSrc "benchmarks"
$pythonCommand = $null
$bundledPython = Join-Path $env:USERPROFILE ".cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe"
foreach ($candidate in @("python", "python3", $bundledPython, "py")) {
  if ((Test-Path -LiteralPath $candidate) -or (Get-Command $candidate -ErrorAction SilentlyContinue)) {
    & $candidate --version *> $null
    if ($LASTEXITCODE -ne 0) {
      continue
    }
    $pythonCommand = $candidate
    break
  }
}
if (-not $pythonCommand) {
  throw "Missing Python command: expected python, python3, or py"
}

Assert-Path (Join-Path $checkSrc "README.md")
Assert-Path (Join-Path $bench "manifest.schema.json")
Assert-Path (Join-Path $bench "run_suite.sh")
Assert-Path (Join-Path $bench "run_all.sh")
Assert-Path (Join-Path $bench "common\env.sh")
Assert-Path (Join-Path $bench "common\runner.py")
Assert-Path (Join-Path $bench "common\atomic_wrap_functions.py")
Assert-Path (Join-Path $bench "common\benchmark_inventory.py")
Assert-Path (Join-Path $checkSrc "benchmark.md")
foreach ($removedReport in @("uncomparable.md", "no-injection-failures.md")) {
  $removedPath = Join-Path $checkSrc $removedReport
  if (Test-Path -LiteralPath $removedPath) {
    throw "Legacy generated Markdown report must be removed: $removedPath"
  }
}

foreach ($legacyPath in @(
  (Join-Path $bench ("common\inject" + "_naive.py"))
)) {
  if (Test-Path -LiteralPath $legacyPath) {
    throw "Legacy benchmark file must be removed: $legacyPath"
  }
}

$suiteNames = @(
  "local-smoke",
  "osek-local",
  "trampoline-current",
  "trampoline-expanded",
  "icbmc-large",
  "icbmc-timeout-30m",
  "icbmc-timeout-30m-blink-highmem",
  "icbmc-timeout-30m-logger-stable",
  "intabs-large"
)

foreach ($removedPath in @(
  (Join-Path $bench "suites\trampoline-c-async.json"),
  (Join-Path $bench "results\trampoline-c-async.csv")
)) {
  if (Test-Path -LiteralPath $removedPath) {
    throw "Obsolete stock-only Trampoline suite artifact must be removed: $removedPath"
  }
}

foreach ($suite in $suiteNames) {
  $suitePath = Join-Path $bench "suites\$suite.json"
  Assert-Json $suitePath
  $data = Get-Content -LiteralPath $suitePath -Raw | ConvertFrom-Json
  foreach ($field in @("suite_name", "description", "enabled", "cases")) {
    if (-not $data.PSObject.Properties.Name.Contains($field)) {
      throw "$suite.json missing required field: $field"
    }
  }
  foreach ($variant in @($data.variants)) {
    if ($variant -in @(("stock" + "_naive"), ("improved" + "_targeted"))) {
      throw "$suite.json uses legacy variant: $variant"
    }
  }
  foreach ($case in $data.cases) {
    foreach ($field in @(
      "name",
      "root",
      "sources",
      "include_dirs",
      "isr_sources",
      "isr_functions",
      "entry_function",
      "unwind",
      "timeout_sec",
      "memory_limit_mb"
    )) {
      if (-not $case.PSObject.Properties.Name.Contains($field)) {
        throw "$suite.json case missing required field: $field"
      }
    }
    if ($case.enabled -eq $false) {
      continue
    }
    $caseVariants = @($data.variants)
    if (Has-JsonProperty $case "variants") {
      $caseVariants = @($case.variants)
    }
    if (@($caseVariants).Count -eq 0) {
      $caseVariants = @("stock_cprover_async", "improved_pipeline")
    }
    foreach ($variant in $caseVariants) {
      $variantRoots = Get-JsonProperty $case "variant_roots"
      $caseRootValue = $case.root
      if ($variantRoots -and (Has-JsonProperty $variantRoots $variant)) {
        $caseRootValue = $variantRoots.$variant
      }
      $caseRoot = Join-Path $Root $caseRootValue
      Assert-Path $caseRoot
      $sources = Get-VariantArray $case "variant_sources" $variant @($case.sources)
      $isrSources = Get-VariantArray $case "variant_isr_sources" $variant @($case.isr_sources)
      $includeDirs = Get-VariantArray $case "variant_include_dirs" $variant @($case.include_dirs)
      foreach ($source in @($sources) + @($isrSources)) {
        Assert-Path (Join-Path $caseRoot $source)
      }
      foreach ($includeDir in @($includeDirs)) {
        Assert-Path (Join-Path $caseRoot $includeDir)
      }
    }
    if (@($case.isr_functions).Count -eq 0) {
      throw "$suite.json case has no isr_functions: $($case.name)"
    }
    if ($suite -in @(
      "icbmc-large",
      "icbmc-timeout-30m",
      "icbmc-timeout-30m-blink-highmem",
      "icbmc-timeout-30m-logger-stable",
      "intabs-large"
    ) -and $caseVariants -contains "improved_pipeline") {
      $variantIsrSources = Get-JsonProperty $case "variant_isr_sources"
      if (-not $variantIsrSources -or -not (Has-JsonProperty $variantIsrSources "improved_pipeline")) {
        throw "$suite.json enabled case must declare variant_isr_sources.improved_pipeline: $($case.name)"
      }
      $improvedIsrSources = @($variantIsrSources.improved_pipeline)
      if (@($improvedIsrSources).Count -eq 0) {
        throw "$suite.json enabled case has empty improved ISR source list: $($case.name)"
      }
      foreach ($source in $improvedIsrSources) {
        if ($source -notmatch "(^|/)isr_define/") {
          throw "$suite.json enabled improved case must use isr_define ISR source: $($case.name) -> $source"
        }
      }
    }
  }
}

$legacyTerms = @(("inject" + "_naive"), ("stock" + "_naive"), ("improved" + "_targeted"))
$docPaths = @(
  (Join-Path $checkSrc "README.md"),
  (Join-Path $bench "manifest.schema.json")
)
foreach ($docPath in $docPaths) {
  Assert-Path $docPath
  $docText = Get-Content -LiteralPath $docPath -Raw
  foreach ($term in $legacyTerms) {
    if ($docText -match [regex]::Escape($term)) {
      throw "Legacy term '$term' remains in $docPath"
    }
  }
}

$readme = Get-Content -LiteralPath (Join-Path $checkSrc "README.md") -Raw
$topLevelItems = Get-ChildItem -LiteralPath $checkSrc -Force |
  Where-Object { $_.Name -ne "benchmarks" -and $_.Name -ne "README.md" } |
  Select-Object -ExpandProperty Name

foreach ($item in $topLevelItems) {
  if ($readme -notmatch [regex]::Escape($item)) {
    throw "Top-level check-src item is not documented in README: $item"
  }
}

$allowedMarkdown = @(
  "check-src/README.md",
  "check-src/benchmark.md"
)
$actualMarkdown = Get-ChildItem -LiteralPath $checkSrc -Recurse -Filter *.md |
  Where-Object { $_.FullName -notmatch "\\benchmarks\\work\\" } |
  ForEach-Object { $_.FullName.Replace($Root + "\", "").Replace("\", "/") } |
  Sort-Object
$extraMarkdown = $actualMarkdown | Where-Object { $allowedMarkdown -notcontains $_ }
if ($extraMarkdown) {
  throw "Unexpected Markdown files under check-src: $($extraMarkdown -join ', ')"
}

$benchmarkText = Get-Content -LiteralPath (Join-Path $checkSrc "benchmark.md") -Raw
if ($benchmarkText -match "trampoline-c-async") {
  throw "benchmark.md must not include the obsolete stock-only trampoline-c-async suite"
}
foreach ($required in @("Stock output", "Improved output", "Correct output", "Full measured time", "Peak RSS")) {
  if ($benchmarkText -notmatch [regex]::Escape($required)) {
    throw "benchmark.md missing comparison field: $required"
  }
}
foreach ($required in @(
  "Column guide:",
  "This table describes the source corpus size used to judge benchmark scale.",
  "This table shows which suite manifests are active, staged, and large enough for headline reporting.",
  "This table identifies partial benchmark runs that should be rerun before final analysis.",
  "This table counts correctness verdicts across measured cases.",
  "This table groups diagnostic cases by the reason they are not clean same-output comparisons."
)) {
  if ($benchmarkText -notmatch [regex]::Escape($required)) {
    throw "benchmark.md missing table explanation: $required"
  }
}
foreach ($forbidden in @("Not reported because the suite is not headline-ready", "Not reported for not-comparable verification outcomes")) {
  if ($benchmarkText -match [regex]::Escape($forbidden)) {
    throw "benchmark.md still suppresses performance comparison: $forbidden"
  }
}

$runnerTestDir = Join-Path ([System.IO.Path]::GetTempPath()) ("cbmc-runner-manifest-" + [System.Guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $runnerTestDir | Out-Null
try {
  $runnerManifest = Join-Path $runnerTestDir "interleaving_pipeline_injected.json"
  Set-Content -LiteralPath $runnerManifest -Encoding ASCII -Value @"
{
  "project": {
    "project_root": "/tmp/original",
    "interleaving_source_files": ["isr_define/isr.c"],
    "translation_units": ["main.c", "isr_define/isr.c", "task_define/tasks.c"]
  },
  "interleaving": []
}
"@
  $runnerScript = @"
import importlib.util
import json
import pathlib
runner_path = pathlib.Path(r'$($bench)\common\runner.py')
manifest_path = pathlib.Path(r'$($runnerManifest)')
spec = importlib.util.spec_from_file_location('runner', runner_path)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
units = module.translation_units_from_manifest(manifest_path)
assert units == ['main.c', 'isr_define/isr.c', 'task_define/tasks.c'], units
raw_interleavings = pathlib.Path(r'$($runnerTestDir)') / 'raw_interleavings.json'
filtered_interleavings = pathlib.Path(r'$($runnerTestDir)') / 'filtered_interleavings.json'
(pathlib.Path(r'$($runnerTestDir)') / 'main.c').write_text('''
void initialize(void) {
  int setup = 0;
}

void runtime(void) {
  int active = 1;
}
''', encoding='utf-8')
raw_interleavings.write_text(json.dumps({
    'project': {
        'project_root': r'$($runnerTestDir)',
        'interleaving_source_files': ['isr_define/isr.c'],
        'translation_units': ['main.c', 'isr_define/isr.c', 'task_define/tasks.c'],
    },
    'interleaving': [
        {
            'name': 'isr',
            'line_added_block_with_file': [
                {'file': 'isr_define/isr.c', 'line': 10},
                {'file': 'main.c', 'line': [3, 7]},
            ],
        },
        {
            'name': 'other',
            'line_added_block_with_file': [
                {'file': 'main.c', 'line': 30},
            ],
        },
    ],
}), encoding='utf-8')
count = module.filtered_interleaving_manifest(raw_interleavings, filtered_interleavings, ['isr'])
assert count == 1, count
filtered = json.loads(filtered_interleavings.read_text(encoding='utf-8'))
sites = filtered['interleaving'][0]['line_added_block_with_file']
assert sites == [{'file': 'main.c', 'line': [7]}], sites
assert filtered['project']['interleaving_source_files'] == ['main.c', 'task_define/tasks.c'], filtered
"@
  $runnerScriptPath = Join-Path $runnerTestDir "check_runner_manifest.py"
  Set-Content -LiteralPath $runnerScriptPath -Encoding ASCII -Value $runnerScript
  & $pythonCommand $runnerScriptPath
  if ($LASTEXITCODE -ne 0) {
    throw "runner.py did not read injected manifest translation_units"
  }
} finally {
  Remove-Item -LiteralPath $runnerTestDir -Recurse -Force
}

$reportTestDir = Join-Path ([System.IO.Path]::GetTempPath()) ("cbmc-report-disabled-" + [System.Guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $reportTestDir | Out-Null
try {
  $reportScript = @"
import importlib.util
import pathlib
report_path = pathlib.Path(r'$($bench)\common\report_benchmark.py')
spec = importlib.util.spec_from_file_location('report_benchmark', report_path)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
reason = 'Disabled fixture has no normalized ISR source.'
manifests = {
    'fixture-suite': {
        'suite_name': 'fixture-suite',
        'enabled': False,
        'variants': ['stock_cprover_async', 'improved_pipeline'],
        'cases': [
            {
                'name': 'disabled-fixture',
                'enabled': False,
                'reason': reason,
                'root': '',
                'sources': [],
            },
            {
                'name': 'failed-success-fixture',
                'enabled': True,
                'root': '',
                'sources': [],
            }
        ],
    }
}
rows = [
    {
        'benchmark': 'fixture-suite',
        'case': 'failed-success-fixture',
        'variant': 'stock_cprover_async',
        'phase': 'verify',
        'run_kind': 'measure',
        'exit_code': '10',
        'time_ms': '100',
        'max_rss_mb': '20',
        'summary': 'VERIFICATION FAILED',
    },
    {
        'benchmark': 'fixture-suite',
        'case': 'failed-success-fixture',
        'variant': 'improved_pipeline',
        'phase': 'verify',
        'run_kind': 'measure',
        'exit_code': '0',
        'time_ms': '50',
        'max_rss_mb': '10',
        'summary': 'VERIFICATION SUCCESSFUL',
    },
]
phases = module.summarize(rows)
rows_with_stale = rows + [{
    'benchmark': 'deleted-suite',
    'case': 'stale-case',
    'variant': 'stock_cprover_async',
    'phase': 'verify',
    'run_kind': 'measure',
    'exit_code': '0',
    'time_ms': '1',
    'max_rss_mb': '1',
    'summary': 'VERIFICATION SUCCESSFUL',
}]
filtered = module.filter_rows_to_known_suites(rows_with_stale, manifests)
assert all(row['benchmark'] != 'deleted-suite' for row in filtered), filtered
audit_records = {
    ('fixture-suite', 'failed-success-fixture'): {
        'correctness_verdict': 'improved_correct',
        'correct_variant': 'improved_pipeline',
        'correctness_action': 'fixture_action_keep_diagnostic',
        'evidence': 'fixture evidence for improved correctness',
    }
}
report = module.build_report(rows, phases, manifests, audit_records=audit_records)
assert f'Not run: {reason}' in report, report
assert 'Suite is excluded from automatic' in report, report
assert 'run it explicitly when diagnostic evidence is needed.' in report, report
assert '## Benchmark Scope' in report, report
assert '## Suite Coverage' in report, report
assert '## Correctness Results' in report, report
assert '## Diagnostic Results' in report, report
assert '## Per-Suite Case Measurements' in report, report
assert '### Diagnostic Summary' in report, report
assert '| Verification Failed vs Successful | 1 |' in report, report
assert '| Not Run / Disabled Cases | 1 |' in report, report
assert '| Stock Timeout | 0 |' in report, report
assert '| Improved Memory Limit | 0 |' in report, report
assert '#### Verification Failed vs Successful' in report, report
assert '#### Not Run / Disabled Cases' in report, report
assert '| fixture-suite | failed-success-fixture | failed | success |' in report, report
assert '| fixture-suite | disabled-fixture | missing | missing |' in report, report
assert '### Correctness Summary' in report, report
assert 'improved_correct' in report and '| 1 |' in report, report
assert 'same_outcome_comparable' in report and '| 0 |' in report, report
assert '### Correctness Wins' in report, report
assert 'Column guide:' in report, report
assert 'This table counts correctness verdicts across measured cases.' in report, report
assert '| fixture-suite | failed-success-fixture | improved_pipeline |' in report, report
assert 'Stock output' in report, report
assert 'Improved output' in report, report
assert 'Correct output' in report, report
assert 'improved is 50.0% faster' in report, report
assert 'improved uses 50.0% less RAM' in report, report
assert 'Not reported because the suite is not headline-ready' not in report, report
assert 'Not reported for not-comparable verification outcomes' not in report, report
empty_report = module.build_report([], {}, manifests)
assert 'No CSV rows were loaded.' in empty_report, empty_report
stock_memory = {
    'verify': {
        'summary': 'MEMORY_LIMIT_EXCEEDED_14000MB',
        'exit_code': '-9',
    }
}
improved_no_candidates = {
    'inject': {
        'summary': 'NO_INJECTION_CANDIDATES',
        'exit_code': '0',
    },
    'verify': {
        'summary': '',
        'exit_code': '6',
    },
}
is_comparable, comparison_reason = module.comparable(stock_memory, improved_no_candidates)
assert not is_comparable
assert comparison_reason == 'Not comparable: stock verification hit the memory limit.', comparison_reason
"@
  $reportScriptPath = Join-Path $reportTestDir "check_disabled_report_reason.py"
  Set-Content -LiteralPath $reportScriptPath -Encoding ASCII -Value $reportScript
  & $pythonCommand $reportScriptPath
  if ($LASTEXITCODE -ne 0) {
    throw "report_benchmark.py did not report the disabled-case reason"
  }
} finally {
  Remove-Item -LiteralPath $reportTestDir -Recurse -Force
}

$auditTestDir = Join-Path ([System.IO.Path]::GetTempPath()) ("cbmc-benchmark-inventory-" + [System.Guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $auditTestDir | Out-Null
try {
  $auditScript = @"
import csv
import importlib.util
import json
import pathlib

root = pathlib.Path(r'$auditTestDir')
suite_dir = root / 'suites'
results_dir = root / 'results'
out_path = root / 'audit' / 'benchmark-inventory.csv'
suite_dir.mkdir(parents=True)
results_dir.mkdir(parents=True)

def write_suite(name, case_name, stock_root, improved_root):
    (suite_dir / f'{name}.json').write_text(json.dumps({
        'suite_name': name,
        'enabled': False,
        'variants': ['stock_cprover_async', 'improved_pipeline'],
        'cases': [{
            'name': case_name,
            'root': improved_root,
            'variant_roots': {
                'stock_cprover_async': stock_root,
                'improved_pipeline': improved_root,
            },
            'sources': ['main.c'],
            'include_dirs': ['.'],
            'isr_sources': ['isr_define/isr.c'],
            'variant_isr_sources': {'improved_pipeline': ['isr_define/isr.c']},
            'isr_functions': ['isr'],
            'entry_function': 'main',
            'properties': [],
            'unwind': 3,
            'timeout_sec': 30,
            'memory_limit_mb': 1024,
        }],
    }), encoding='utf-8')

write_suite(
    'icbmc-timeout-30m',
    'logger2-conc',
    'check-src/benchmark-sources/icbmc/cases/logger2-conc/stock-cprover-async',
    'check-src/benchmark-sources/icbmc/cases/logger2-conc/improved-pipeline',
)
write_suite(
    'icbmc-timeout-30m-logger-stable',
    'logger2-conc',
    'check-src/benchmark-sources/icbmc/cases/logger2-conc/stock-cprover-async',
    'check-src/benchmark-sources/icbmc/cases/logger2-conc/improved-pipeline',
)
write_suite(
    'icbmc-large',
    'blink',
    'check-src/benchmark-sources/icbmc/cases/blink/stock-cprover-async',
    'check-src/benchmark-sources/icbmc/cases/blink/improved-pipeline',
)

fields = [
    'benchmark',
    'case',
    'variant',
    'phase',
    'run',
    'run_kind',
    'exit_code',
    'time_ms',
    'max_rss_kb',
    'max_rss_mb',
    'summary',
]
rows = [
    ['icbmc-timeout-30m', 'logger2-conc', 'stock_cprover_async', 'verify', '1', 'measure', '10', '100', '1024', '1.0', 'VERIFICATION FAILED'],
    ['icbmc-timeout-30m', 'logger2-conc', 'improved_pipeline', 'verify', '1', 'measure', '6', '10', '512', '0.5', ''],
    ['icbmc-timeout-30m-logger-stable', 'logger2-conc', 'stock_cprover_async', 'verify', '1', 'measure', '10', '100', '1024', '1.0', 'VERIFICATION FAILED'],
    ['icbmc-timeout-30m-logger-stable', 'logger2-conc', 'improved_pipeline', 'verify', '1', 'measure', '6', '10', '512', '0.5', ''],
    ['icbmc-large', 'blink', 'stock_cprover_async', 'verify', '1', 'measure', '-9', '100', '1024', '1.0', 'MEMORY_LIMIT_EXCEEDED_1024MB'],
    ['icbmc-large', 'blink', 'improved_pipeline', 'inject', '1', 'measure', '0', '10', '512', '0.5', 'NO_INJECTION_CANDIDATES'],
]
with (results_dir / 'fixture.csv').open('w', newline='', encoding='utf-8') as csv_file:
    writer = csv.writer(csv_file)
    writer.writerow(fields)
    writer.writerows(rows)

module_path = pathlib.Path(r'$($bench)\common\benchmark_inventory.py')
spec = importlib.util.spec_from_file_location('benchmark_inventory', module_path)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
inventory = module.collect_inventory(root, suite_dir, results_dir)
assert len(inventory) == 2, inventory
logger_rows = [row for row in inventory if row['case'] == 'logger2-conc']
assert len(logger_rows) == 1, inventory
assert logger_rows[0]['suite'] == 'icbmc-timeout-30m-logger-stable', logger_rows
blink_rows = [row for row in inventory if row['case'] == 'blink']
assert len(blink_rows) == 1, inventory
assert blink_rows[0]['needs_no_injection_audit'] == 'true', blink_rows
module.write_inventory(inventory, out_path)
with out_path.open(newline='', encoding='utf-8') as csv_file:
    written = list(csv.DictReader(csv_file))
assert len(written) == 2, written
"@
  $auditScriptPath = Join-Path $auditTestDir "check_benchmark_inventory.py"
  Set-Content -LiteralPath $auditScriptPath -Encoding ASCII -Value $auditScript
  & $pythonCommand $auditScriptPath
  if ($LASTEXITCODE -ne 0) {
    throw "benchmark_inventory.py did not deduplicate audit inventory"
  }
} finally {
  Remove-Item -LiteralPath $auditTestDir -Recurse -Force
}

$evidenceTestDir = Join-Path ([System.IO.Path]::GetTempPath()) ("cbmc-evidence-case-" + [System.Guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $evidenceTestDir | Out-Null
try {
  $evidenceScript = @"
import importlib.util
import pathlib

module_path = pathlib.Path(r'$($bench)\common\run_evidence_case.py')
spec = importlib.util.spec_from_file_location('run_evidence_case', module_path)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)

manifest = {
    'suite_name': 'fixture-suite',
    'enabled': True,
    'variants': ['stock_cprover_async', 'improved_pipeline'],
    'cases': [
        {
            'name': 'target',
            'root': 'improved',
            'variant_roots': {
                'stock_cprover_async': 'stock',
                'improved_pipeline': 'improved',
            },
            'sources': ['main.c'],
            'include_dirs': ['.'],
            'isr_sources': ['isr_define/isr.c'],
            'isr_functions': ['isr'],
            'entry_function': 'main',
            'properties': [],
            'unwind': 3,
            'cbmc_args': ['--trace'],
        },
        {
            'name': 'other',
            'root': 'other',
            'sources': ['main.c'],
            'include_dirs': ['.'],
            'isr_sources': ['isr.c'],
            'isr_functions': ['isr'],
            'entry_function': 'main',
            'properties': [],
            'unwind': 3,
        },
    ],
}
evidence_manifest, selected = module.build_evidence_manifest(
    manifest,
    'target',
    'fixture-suite__target__evidence',
    enable_trace=True,
    enable_json_ui=False,
)
assert selected['name'] == 'target', selected
assert evidence_manifest['suite_name'] == 'fixture-suite__target__evidence', evidence_manifest
assert len(evidence_manifest['cases']) == 1, evidence_manifest['cases']
args = evidence_manifest['cases'][0]['cbmc_args']
assert args.count('--trace') == 1, args
assert '--stop-on-fail' in args, args
"@
  $evidenceScriptPath = Join-Path $evidenceTestDir "check_evidence_manifest.py"
  Set-Content -LiteralPath $evidenceScriptPath -Encoding ASCII -Value $evidenceScript
  & $pythonCommand $evidenceScriptPath
  if ($LASTEXITCODE -ne 0) {
    throw "run_evidence_case.py did not build the expected trace manifest"
  }
} finally {
  Remove-Item -LiteralPath $evidenceTestDir -Recurse -Force
}

$globalScanTestDir = Join-Path ([System.IO.Path]::GetTempPath()) ("cbmc-global-scan-" + [System.Guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $globalScanTestDir | Out-Null
try {
  $scanRoot = Join-Path $globalScanTestDir "case\improved-pipeline"
  New-Item -ItemType Directory -Path (Join-Path $scanRoot "isr_define") -Force | Out-Null
  Set-Content -LiteralPath (Join-Path $scanRoot "main.c") -Encoding ASCII -Value @"
int shared;
int only_main;

void helper(void) {
  only_main++;
}

int main(void) {
  helper();
  if (shared) {
    only_main++;
  }
  return 0;
}
"@
  Set-Content -LiteralPath (Join-Path $scanRoot "isr_define\isr.c") -Encoding ASCII -Value @"
extern int shared;

void isr(void) {
  __CPROVER_atomic_begin();
  shared = 1;
  __CPROVER_atomic_end();
}
"@
  $globalScanScript = @"
import importlib.util
import pathlib

module_path = pathlib.Path(r'$($bench)\common\global_effect_scan.py')
spec = importlib.util.spec_from_file_location('global_effect_scan', module_path)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)

repo_root = pathlib.Path(r'$globalScanTestDir')
manifest = {'suite_name': 'fixture-suite'}
case = {
    'name': 'global-fixture',
    'variant_roots': {'improved_pipeline': 'case/improved-pipeline'},
    'sources': ['main.c'],
    'variant_isr_sources': {'improved_pipeline': ['isr_define/isr.c']},
    'isr_sources': ['isr_define/isr.c'],
    'isr_functions': ['isr'],
    'entry_function': 'main',
}
row = module.scan_case(repo_root, manifest, case, 'global-fixture-id')
assert row['verdict'] == 'no_injection_false', row
assert row['candidate_globals'] == 'shared', row
assert row['candidate_details'] == 'shared:isr=isr:main=main', row
"@
  $globalScanScriptPath = Join-Path $globalScanTestDir "check_global_effect_scan.py"
  Set-Content -LiteralPath $globalScanScriptPath -Encoding ASCII -Value $globalScanScript
  & $pythonCommand $globalScanScriptPath
  if ($LASTEXITCODE -ne 0) {
    throw "global_effect_scan.py did not flag ISR/main shared global"
  }
} finally {
  Remove-Item -LiteralPath $globalScanTestDir -Recurse -Force
}

$improvedCaseTestDir = Join-Path ([System.IO.Path]::GetTempPath()) ("cbmc-improved-structure-" + [System.Guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $improvedCaseTestDir | Out-Null
try {
  $improvedCaseScript = @"
import importlib.util
import json
import pathlib
import re

root = pathlib.Path(r'$Root')
atomic_path = root / 'check-src/benchmarks/common/atomic_wrap_functions.py'
spec = importlib.util.spec_from_file_location('atomic_wrap_functions', atomic_path)
atomic = importlib.util.module_from_spec(spec)
spec.loader.exec_module(atomic)

def strip_comments(text):
    return re.sub(r'//.*?$|/\*.*?\*/', '', text, flags=re.MULTILINE | re.DOTALL)

def strip_if_zero(text):
    previous = None
    while previous != text:
        previous = text
        text = re.sub(r'(?ms)^\s*#if\s+0\b.*?^\s*#endif\b.*?$', '', text)
    return text

issues = []
for suite_name in (
    'icbmc-large',
    'icbmc-timeout-30m',
    'icbmc-timeout-30m-blink-highmem',
    'icbmc-timeout-30m-logger-stable',
    'intabs-large',
):
    manifest_path = root / f'check-src/benchmarks/suites/{suite_name}.json'
    manifest = json.loads(manifest_path.read_text())
    for case in manifest['cases']:
        if case.get('enabled', True) is False:
            continue
        improved_root = root / case['variant_roots']['improved_pipeline']
        main_text = strip_if_zero(strip_comments((improved_root / 'main.c').read_text(errors='ignore')))
        if re.search(r'(?m)^\s*(?:__CPROVER_ASYNC_\w*\s*:|pthread_create\s*\()', main_text):
            issues.append(f'{suite_name}/{case["name"]}: improved main has active async or pthread launch')
        for source in case['variant_isr_sources']['improved_pipeline']:
            source_text = (improved_root / source).read_text(errors='ignore')
            for function in case['isr_functions']:
                matches = atomic.function_matches(source_text, function)
                if len(matches) != 1:
                    issues.append(f'{suite_name}/{case["name"]}/{function}: expected one ISR definition, found {len(matches)}')
                    continue
                _, open_brace, close_brace = matches[0]
                body = strip_comments(source_text[open_brace + 1:close_brace]).strip()
                if not body.startswith('__CPROVER_atomic_begin();'):
                    issues.append(f'{suite_name}/{case["name"]}/{function}: ISR is not atomic from function entry')
                returns = list(re.finditer(r'\breturn\b[^;]*;', body))
                for return_match in returns:
                    prefix = body[:return_match.start()]
                    if not re.search(r'__CPROVER_atomic_end\(\);\s*$', prefix):
                        issues.append(f'{suite_name}/{case["name"]}/{function}: return is not guarded by atomic_end')
                if not returns and not body.endswith('__CPROVER_atomic_end();'):
                    issues.append(f'{suite_name}/{case["name"]}/{function}: ISR has no final atomic_end')

assert not issues, '\n'.join(issues)
"@
  $improvedCaseScriptPath = Join-Path $improvedCaseTestDir "check_improved_case_structure.py"
  Set-Content -LiteralPath $improvedCaseScriptPath -Encoding ASCII -Value $improvedCaseScript
  & $pythonCommand $improvedCaseScriptPath
  if ($LASTEXITCODE -ne 0) {
    throw "Enabled external improved-pipeline cases failed structural validation"
  }
} finally {
  Remove-Item -LiteralPath $improvedCaseTestDir -Recurse -Force
}

$atomicTestDir = Join-Path ([System.IO.Path]::GetTempPath()) ("cbmc-atomic-wrap-" + [System.Guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $atomicTestDir | Out-Null
try {
  $atomicFixture = Join-Path $atomicTestDir "fixture.c"
  Set-Content -LiteralPath $atomicFixture -Encoding ASCII -Value @"
int shared;

void isr_fixture(void) {
  if (shared) {
    return;
  }
  shared++;
}
"@
  & $pythonCommand (Join-Path $bench "common\atomic_wrap_functions.py") $atomicFixture isr_fixture | Out-Null
  if ($LASTEXITCODE -ne 0) {
    throw "atomic_wrap_functions.py failed on fixture"
  }
  $atomicOutput = Get-Content -LiteralPath $atomicFixture -Raw
  if ($atomicOutput -notmatch "__CPROVER_atomic_begin\(\);") {
    throw "atomic wrapper did not add atomic begin"
  }
  if ($atomicOutput -notmatch "__CPROVER_atomic_end\(\);\s*return;") {
    throw "atomic wrapper did not guard early return"
  }
  if ($atomicOutput -match "#define\s+__CPROVER_atomic_begin") {
    throw "atomic wrapper must not replace CBMC atomic builtins with no-op macros"
  }
} finally {
  Remove-Item -LiteralPath $atomicTestDir -Recurse -Force
}

Write-Output "selftest ok"
