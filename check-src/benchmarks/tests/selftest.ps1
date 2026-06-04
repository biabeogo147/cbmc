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
Assert-Path (Join-Path $bench "VERIFICATION_PROTOCOL.md")

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
  "trampoline-c-async",
  "trampoline-expanded",
  "icbmc-large",
  "icbmc-timeout-30m",
  "icbmc-timeout-30m-blink-highmem",
  "icbmc-timeout-30m-logger-stable",
  "intabs-large"
)

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
  (Join-Path $bench "README.md"),
  (Join-Path $bench "PIPELINE.md"),
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
import pathlib
runner_path = pathlib.Path(r'$($bench)\common\runner.py')
manifest_path = pathlib.Path(r'$($runnerManifest)')
spec = importlib.util.spec_from_file_location('runner', runner_path)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
units = module.translation_units_from_manifest(manifest_path)
assert units == ['main.c', 'isr_define/isr.c', 'task_define/tasks.c'], units
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
report = module.build_report(rows, phases, manifests, 'uncomparable')
assert f'Not run: {reason}' in report, report
assert 'Suite is excluded from automatic' in report, report
assert 'run it explicitly when diagnostic evidence is needed.' in report, report
assert '## Uncomparable Summary' in report, report
assert '| Verification Failed vs Successful | 1 |' in report, report
assert '| Not Run / Disabled Cases | 1 |' in report, report
assert '| Stock Timeout | 0 |' in report, report
assert '| Improved Memory Limit | 0 |' in report, report
assert '## Verification Failed vs Successful' in report, report
assert '## Not Run / Disabled Cases' in report, report
assert report.count('### fixture-suite') == 2, report
assert '#### failed-success-fixture' in report, report
assert '#### disabled-fixture' in report, report
comparable_report = module.build_report([], {}, manifests, 'comparable')
assert 'fixture-suite' not in comparable_report, comparable_report
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
