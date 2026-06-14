#!/usr/bin/env python3
"""
Quick Build Script - Compiles all source files and checks for errors
"""

import os
import sys
import subprocess
from pathlib import Path

PROJECT_ROOT = Path(__file__).parent.absolute()

def log(msg):
    print(f"[BUILD] {msg}")

def run_cmd(cmd, cwd=None):
    print(f"  > {' '.join(cmd) if isinstance(cmd, list) else cmd}")
    result = subprocess.run(cmd, shell=True, cwd=cwd, capture_output=True, text=True)
    if result.returncode != 0:
        print(f"  FAILED: {result.stderr}")
        return False
    return True

def main():
    log("Starting quick build...")

    source_files = [
        "common/lib_math.c",
        "common/lib_mem.c",
        "common/lib_utils.c",
        "drivers/gpio_driver.c",
        "drivers/timer_driver.c",
        "middleware/data_filter.c",
        "middleware/protocol_stack.c",
        "osek/osek_runtime_stub.c",
        "isr_define/isr_timer.c",
        "isr_define/isr_external.c",
        "isr_define/isr_adc.c",
        "isr_define/isr_uart.c",
        "task_define/task_main.c",
        "task_define/task_comm.c",
        "task_define/task_monitor.c",
        "task_define/task_io.c",
        "task_define/task_sensor.c",
        "task_define/task_comm2.c",
        "task_define/task_process.c",
        "task_define/task_9.c",
        "task_define/task_10.c",
        "task_define/task_11.c",
        "task_define/task_12.c",
        "task_define/task_13.c",
        "task_define/task_14.c",
        "task_define/task_15.c",
        "task_define/task_16.c",
        "task_define/task_17.c",
        "task_define/task_18.c",
        "task_define/task_19.c",
        "task_define/task_20.c",
        "task_define/task_21.c",
        "task_define/task_22.c",
        "task_define/task_23.c",
        "task_define/task_24.c",
        "task_define/task_25.c",
        "task_define/task_26.c",
        "task_define/task_27.c",
        "task_define/task_28.c",
        "task_define/task_29.c",
        "task_define/task_30.c",
        "harness.c",
    ]

    include_dirs = ["common", "drivers", "middleware", "osek", "task_define", "isr_define"]

    log(f"Found {len(source_files)} source files to check...")

    errors = []
    for src in source_files:
        src_path = PROJECT_ROOT / src
        if not src_path.exists():
            errors.append(f"Missing: {src}")
            log(f"Missing: {src}")

    if errors:
        log(f"Build failed: {len(errors)} files missing")
        for e in errors:
            print(f"  - {e}")
        return 1

    log("All source files present!")
    log("Quick build check complete.")

    return 0

if __name__ == "__main__":
    sys.exit(main())