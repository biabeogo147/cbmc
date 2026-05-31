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
Assert-Path (Join-Path $bench "common\measure.sh")
Assert-Path (Join-Path $bench "common\inject_naive_isr.sh")
Assert-Path (Join-Path $bench "common\report.sh")
Assert-Path (Join-Path $bench "common\runner.py")
Assert-Path (Join-Path $bench "common\inject_naive.py")
Assert-Path (Join-Path $bench "common\atomic_wrap_functions.py")
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
