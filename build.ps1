param(
    [string]$Compiler = "gcc"
)

$ErrorActionPreference = "Stop"
$buildDir = Join-Path $PSScriptRoot "build"
$target = Join-Path $buildDir "sortlab.exe"

New-Item -ItemType Directory -Force -Path $buildDir | Out-Null

$sources = Get-ChildItem -Path (Join-Path $PSScriptRoot "src") -Filter "*.c" |
    ForEach-Object { $_.FullName }

& $Compiler -std=c11 -Wall -Wextra -O2 -I"$PSScriptRoot\include" @sources -o $target

Write-Host "Executavel gerado em: $target"
