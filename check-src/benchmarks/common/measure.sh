#!/usr/bin/env bash
set -euo pipefail

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  label=${1:-smoke}
  shift || true
  start_ms=$(date +%s%3N)
  "$@" >/dev/null 2>&1
  exit_code=$?
  end_ms=$(date +%s%3N)
  printf '%s,exit=%d,time_ms=%d,max_rss_mb=0.0,summary=standalone\n' \
    "$label" "$exit_code" "$((end_ms - start_ms))"
  exit "$exit_code"
fi

measure_command() {
  local csv="$1"
  local benchmark="$2"
  local case_name="$3"
  local variant="$4"
  local phase="$5"
  local run_id="$6"
  shift 6

  local log="${csv}.${benchmark}.${case_name}.${variant}.${phase}.${run_id}.log"
  local start_ms end_ms pid rss_kb max_rss_kb=0 exit_code=0 summary

  start_ms=$(date +%s%3N)
  "$@" >"$log" 2>&1 &
  pid=$!

  while kill -0 "$pid" 2>/dev/null; do
    if [[ -r "/proc/$pid/status" ]]; then
      rss_kb=$(awk '/^VmRSS:/ { print $2; exit }' "/proc/$pid/status" 2>/dev/null || true)
      rss_kb=${rss_kb:-0}
      if [[ "$rss_kb" =~ ^[0-9]+$ ]] && [[ "$rss_kb" -gt "$max_rss_kb" ]]; then
        max_rss_kb=$rss_kb
      fi
    fi
    sleep 0.02
  done

  wait "$pid" || exit_code=$?
  end_ms=$(date +%s%3N)

  summary=$(awk '
    /VERIFICATION (SUCCESSFUL|FAILED)/ { s=$0 }
    /Failed properties:[[:space:]]*[0-9]+/ { s=s " | " $0 }
    /pointer handling for concurrency is unsound/ { s="CBMC_UNSUPPORTED_CONCURRENCY" }
    END { print s }
  ' "$log")

  printf '%s,%s,%s,%s,%s,%s,%d,%d,%.1f,%s\n' \
    "$benchmark" "$case_name" "$variant" "$phase" "$run_id" "$exit_code" \
    "$((end_ms - start_ms))" "$max_rss_kb" "$(awk -v rss="$max_rss_kb" 'BEGIN { print rss / 1024 }')" \
    "$summary" >>"$csv"
}
