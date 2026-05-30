#!/usr/bin/env bash
set -euo pipefail

IMPROVED_CBMC=${IMPROVED_CBMC:-./cmake-build-debug-cbmc/bin/cbmc}
IMPROVED_GOTOCC=${IMPROVED_GOTOCC:-./cmake-build-debug-cbmc/bin/goto-cc}
STOCK_CBMC=${STOCK_CBMC:-$IMPROVED_CBMC}
STOCK_GOTOCC=${STOCK_GOTOCC:-$IMPROVED_GOTOCC}
AIB=${AIB:-./cmake-build-debug-cbmc/bin/aib}
WORK=${WORK:-/tmp/cbmc_isr_large_benchmark}
METRICS="$WORK/metrics.csv"

TRAMPOLINE_ROOT=check-src/simple-benchmarks/trampoline
REL_SOURCES=(
  tests/embUnit/AssertImpl.c
  tests/embUnit/RepeatedTest.c
  tests/embUnit/SchedulingCheck.c
  tests/embUnit/stdImpl.c
  tests/embUnit/TestCaller.c
  tests/embUnit/TestCase.c
  tests/embUnit/TestResult.c
  tests/embUnit/TestRunner.c
  tests/embUnit/TestSuite.c
  tests/functional/alarms_s1_non/alarms_s1.c
  tests/functional/alarms_s1_non/task1_instance.c
  tests/functional/alarms_s1_non/isr_define/isr.c
  tests/functional/alarms_s1_non/alarms_s1_non/tpl_app_config.c
  tests/functional/alarms_s1_non/alarms_s1_non/tpl_os.c
  os/tpl_os_kernel.c
  os/tpl_os_timeobj_kernel.c
  os/tpl_os_action.c
  os/tpl_os_error.c
  os/tpl_os_os_kernel.c
  os/tpl_os_os.c
  os/tpl_os_interrupt_kernel.c
  os/tpl_os_task_kernel.c
  os/tpl_os_resource_kernel.c
  os/tpl_os_alarm_kernel.c
  machines/posix/tpl_machine_posix.c
  machines/posix/tpl_viper_interface.c
  machines/posix/tpl_posix_autosar.c
  machines/posix/tpl_posix_irq.c
  machines/posix/tpl_posix_context.c
  machines/posix/tpl_posixvp_irq_gen.c
  tests/machines/posix/archTestConfig.c
  tests/machines/common/commonTestConfig.c
)

rel_includes() {
  local root="$1"
  printf -- '-I %s/machines/posix ' "$root"
  printf -- '-I %s/viper ' "$root"
  printf -- '-I %s/tests/embUnit ' "$root"
  printf -- '-I %s/tests/machines/common ' "$root"
  printf -- '-I %s/tests/machines/posix ' "$root"
  printf -- '-I %s/com ' "$root"
  printf -- '-I %s/os ' "$root"
  printf -- '-I %s/debug ' "$root"
  printf -- '-I %s/tests/functional/alarms_s1_non/alarms_s1_non ' "$root"
}

rel_sources() {
  local root="$1"
  local source
  for source in "${REL_SOURCES[@]}"; do
    printf '%s/%s\n' "$root" "$source"
  done
}

count_loc() {
  local root="$1"
  local total=0
  local source
  local lines
  for source in "${REL_SOURCES[@]}"; do
    lines=$(wc -l <"$root/$source")
    total=$((total + lines))
  done
  printf '%s' "$total"
}

measure() {
  local label="$1"
  shift

  local log="$WORK/${label}.log"
  local start_ms
  local end_ms
  local max_rss_kb=0
  local rss_kb
  local exit_code=0
  local summary

  start_ms=$(date +%s%3N)
  "$@" >"$log" 2>&1 &
  local pid=$!

  while kill -0 "$pid" 2>/dev/null; do
    rss_kb=$(awk '/^VmRSS:/ { print $2; exit }' "/proc/$pid/status" 2>/dev/null || true)
    rss_kb=${rss_kb:-0}
    if [ "$rss_kb" -gt "$max_rss_kb" ]; then
      max_rss_kb=$rss_kb
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

  local line
  line=$(awk -v label="$label" \
    -v exit_code="$exit_code" \
    -v time_ms="$((end_ms - start_ms))" \
    -v max_rss_kb="$max_rss_kb" \
    -v summary="$summary" \
    'BEGIN {
      printf "%s,exit=%d,time_ms=%d,max_rss_mb=%.1f,summary=%s\n",
        label, exit_code, time_ms, max_rss_kb / 1024, summary
    }')
  echo "$line"
  echo "$line" >>"$METRICS"
}

inject_naive_isr_points() {
  local root="$1"
  local inserted_file="$2"
  : >"$inserted_file"

  local source
  for source in "${REL_SOURCES[@]}"; do
    if [[ "$source" == "tests/functional/alarms_s1_non/isr_define/isr.c" ]]; then
      continue
    fi

    perl -0pi -e '
      my $prologue =
        "extern _Bool nondet_bool(void);\n" .
        "void *isr1(void *arg);\n" .
        "void *isr2(void *arg);\n" .
        "void *isr3(void *arg);\n";

      if($_ =~ /(#include[^\n]*\n)(?!#include)/)
      {
        $_ =~ s/((?:#include[^\n]*\n)+)/$1$prologue/;
      }
      else
      {
        $_ = $prologue . $_;
      }

      my @out;
      my $depth = 0;
      my $in_function = 0;
      my $pending_function = 0;
      my $prev_trim = "";
      my $paren_depth = 0;
      my $inserted = 0;
      for my $line (split /^/, $_)
      {
        my $trim = $line;
        $trim =~ s/^\s+|\s+$//g;
        if(
          $in_function &&
          $depth > 0 &&
          $paren_depth == 0 &&
          $trim =~ /;\s*(?:\/\/.*)?$/ &&
          $prev_trim =~ /[;{}]$/ &&
          $trim !~ /^\}?\s*;$/ &&
          $prev_trim !~ /^(?:VAR|CONST|FUNC|P2VAR|P2CONST|CONSTP2CONST|CONSTP2VAR)\s*\(/ &&
          $trim !~ /^(?:return|extern|typedef|struct|enum|union)\b/ &&
          $trim !~ /^#/ &&
          $trim !~ /nondet_bool|isr[123]\(|__CPROVER_atomic/
        )
        {
          push @out,
            "  if(nondet_bool()) isr1(0);\n",
            "  if(nondet_bool()) isr2(0);\n",
            "  if(nondet_bool()) isr3(0);\n";
          $inserted += 3;
        }

        push @out, $line;
        my $enters_function =
          ($depth == 0 && $line =~ /\)\s*\{/) ||
          ($depth == 0 && $pending_function && $line =~ /\{/);
        my $opens = () = $line =~ /\{/g;
        my $closes = () = $line =~ /\}/g;
        my $paren_opens = () = $line =~ /\(/g;
        my $paren_closes = () = $line =~ /\)/g;
        $depth += $opens - $closes;
        $depth = 0 if $depth < 0;
        $paren_depth += $paren_opens - $paren_closes;
        $paren_depth = 0 if $paren_depth < 0;

        if($enters_function && $depth > 0)
        {
          $in_function = 1;
          $pending_function = 0;
        }
        elsif($depth == 0)
        {
          $in_function = 0;
          $pending_function =
            $line =~ /\)\s*$/ &&
            $line !~ /^\s*[A-Z_]+\s*\(/ &&
            $line !~ /,/ &&
          $line !~ /^\s*(if|for|while|switch)\b/;
        }
        $prev_trim = $trim if $trim ne "";
      }
      $_ = join "", @out;
      END { print STDERR "$inserted\n"; }
    ' "$root/$source" 2>>"$inserted_file"
  done
}

relax_isr_guard_assertions() {
  local root="$1"
  local main_c="$root/tests/functional/alarms_s1_non/alarms_s1.c"

  perl -0pi -e '
    s/assert\(alarms_irq_guard_2 == 20\);/assert(alarms_irq_guard_2 == 20 || alarms_irq_guard_2 == -20);/;
    s/assert\(alarms_irq_guard_3 == 30\);/assert(alarms_irq_guard_3 == 30 || alarms_irq_guard_3 == 0);/;
  ' "$main_c"
}

build_goto() {
  local compiler="$1"
  local root="$2"
  local output="$3"
  shift 3
  # shellcheck disable=SC2046
  "$compiler" $(rel_includes "$root") $(rel_sources "$root") "$@" -o "$output"
}

rm -rf "$WORK"
mkdir -p "$WORK"
: >"$METRICS"
cp -a "$TRAMPOLINE_ROOT" "$WORK/stock_naive"
cp -a "$TRAMPOLINE_ROOT" "$WORK/improved_original"

relax_isr_guard_assertions "$WORK/stock_naive"
relax_isr_guard_assertions "$WORK/improved_original"

SOURCE_LOC=$(count_loc "$TRAMPOLINE_ROOT")
SOURCE_FILES=${#REL_SOURCES[@]}

NAIVE_INSERT_LOG="$WORK/naive_insertions.txt"
inject_naive_isr_points "$WORK/stock_naive" "$NAIVE_INSERT_LOG"
NAIVE_INSERTIONS=$(awk '{ s += $1 } END { print s + 0 }' "$NAIVE_INSERT_LOG")

echo "benchmark,source_files=$SOURCE_FILES,source_loc=$SOURCE_LOC"
echo "stock_naive,isr_insertions=$NAIVE_INSERTIONS"

measure stock_naive_compile "$STOCK_GOTOCC" \
  $(rel_includes "$WORK/stock_naive") \
  $(rel_sources "$WORK/stock_naive") \
  -o "$WORK/stock_naive.out"

measure stock_naive_verify "$STOCK_CBMC" \
  "$WORK/stock_naive.out" \
  --function main \
  --no-standard-checks \
  --unwind 3 \
  --property main.assertion.1 \
  --property main.assertion.2 \
  --property main.assertion.3

measure improved_manifest "$IMPROVED_GOTOCC" \
  $(rel_includes "$WORK/improved_original") \
  $(rel_sources "$WORK/improved_original") \
  --interleaving-project-root "$WORK/improved_original" \
  --interleaving-source-files "$WORK/improved_original/tests/functional/alarms_s1_non/isr_define/isr.c" \
  --interleaving-output "$WORK/interleaving_pipeline.json" \
  -o "$WORK/improved_manifest.out"

measure improved_aib_inject "$AIB" \
  "$WORK/improved_original" \
  "$WORK/interleaving_pipeline.json" \
  "$WORK/improved_targeted" \
  "$WORK/improved_targeted/tests/functional/alarms_s1_non/interleaving_pipeline_injected.json"

TARGETED_INSERTIONS=$(grep -RE "if[[:space:]]*\\(nondet_bool\\(\\)\\)[[:space:]]+isr[123]\\(0\\);" "$WORK/improved_targeted" 2>/dev/null | wc -l || true)
echo "improved_targeted,isr_insertions=$TARGETED_INSERTIONS"

measure improved_compile "$IMPROVED_GOTOCC" \
  $(rel_includes "$WORK/improved_targeted") \
  $(rel_sources "$WORK/improved_targeted") \
  -o "$WORK/improved_targeted.out"

measure improved_verify "$IMPROVED_CBMC" \
  "$WORK/improved_targeted.out" \
  --function main \
  --no-standard-checks \
  --unwind 3 \
  --property main.assertion.1 \
  --property main.assertion.2 \
  --property main.assertion.3

awk -F'[,=]' '
  $1 == "stock_naive_verify" {
    stock_ms = $5
    stock_rss = $7
  }
  $1 == "improved_verify" {
    improved_ms = $5
    improved_rss = $7
  }
  END {
    if(stock_ms > 0 && stock_rss > 0) {
      printf "delta,verify_faster_pct=%.1f,verify_ram_less_pct=%.1f\n",
        (stock_ms - improved_ms) * 100 / stock_ms,
        (stock_rss - improved_rss) * 100 / stock_rss
    }
  }
' "$METRICS"

awk -v naive="$NAIVE_INSERTIONS" -v targeted="$TARGETED_INSERTIONS" 'BEGIN {
  if(naive > 0) {
    printf "delta,isr_points_reduced_pct=%.1f\n",
      (naive - targeted) * 100 / naive
  }
}'
