$ErrorActionPreference = "Stop"

$sourceRoot = Split-Path -Parent $MyInvocation.MyCommand.Path
$repoRoot = Resolve-Path (Join-Path $sourceRoot "..\..")
$targetRoot = Join-Path $repoRoot "regression\cbmc"

$fixtures = Get-ChildItem -Path $sourceRoot -Directory | Where-Object {
  $_.Name -like "osek-event-*"
}

foreach($fixture in $fixtures)
{
  $destination = Join-Path $targetRoot $fixture.Name
  if(Test-Path $destination)
  {
    Remove-Item -Path $destination -Recurse -Force
  }

  Copy-Item -Path $fixture.FullName -Destination $destination -Recurse
  Write-Host "Synced $($fixture.Name) -> $destination"
}

