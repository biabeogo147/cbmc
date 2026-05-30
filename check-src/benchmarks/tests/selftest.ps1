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

$checkSrc = Join-Path $Root "check-src"
$bench = Join-Path $checkSrc "benchmarks"

Assert-Path (Join-Path $checkSrc "README.md")
Assert-Path (Join-Path $bench "manifest.schema.json")
Assert-Path (Join-Path $bench "run_suite.sh")
Assert-Path (Join-Path $bench "run_all.sh")
Assert-Path (Join-Path $bench "common\env.sh")
Assert-Path (Join-Path $bench "common\measure.sh")
Assert-Path (Join-Path $bench "common\inject_naive_isr.sh")
Assert-Path (Join-Path $bench "common\report.sh")
Assert-Path (Join-Path $bench "common\runner.py")
Assert-Path (Join-Path $bench "common\inject_naive.py")
Assert-Path (Join-Path $bench "VERIFICATION_PROTOCOL.md")

$suiteNames = @(
  "local-smoke",
  "osek-local",
  "trampoline-current",
  "trampoline-c-async",
  "trampoline-expanded",
  "icbmc-interrupts",
  "intabs-interrupts"
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
    $caseRoot = Join-Path $Root $case.root
    Assert-Path $caseRoot
    foreach ($source in @($case.sources) + @($case.isr_sources)) {
      Assert-Path (Join-Path $caseRoot $source)
    }
    foreach ($includeDir in @($case.include_dirs)) {
      Assert-Path (Join-Path $caseRoot $includeDir)
    }
    if (@($case.isr_functions).Count -eq 0) {
      throw "$suite.json case has no isr_functions: $($case.name)"
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

Write-Output "selftest ok"
