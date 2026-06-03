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
