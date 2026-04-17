#!/usr/bin/env python3
"""
OSEK CBMC Verification Automation Script

This script automates the CBMC verification process for the OSEK RTOS project.
It supports:
    - Compilation of source files to goto binaries
    - CBMC verification with interleaving analysis
    - Docker-based verification (for Linux CI/CD)
    - Local Windows execution (using goto-cc and goto-cbmc)
    - JSON configuration for project structure
    - Comprehensive reporting

Usage:
    python run_cbmc.py                    # Run verification with defaults
    python run_cbmc.py --build           # Build goto binaries only
    python run_cbmc.py --verify           # Run verification only
    python run_cbmc.py --docker           # Run in Docker container
    python run_cbmc.py --config <file>    # Use custom config file
    python run_cbmc.py --output <dir>     # Custom output directory
"""

import os
import sys
import json
import subprocess
import argparse
import shutil
from pathlib import Path
from datetime import datetime

# Project root directory
PROJECT_ROOT = Path(__file__).parent.absolute()
CONFIG_FILE = PROJECT_ROOT / "interleaving_harness.json"
OUTPUT_DIR = PROJECT_ROOT / "cbmc_output"


class CBMCAutomation:
    def __init__(self, config_path=None, output_dir=None, use_docker=False):
        self.use_docker = use_docker
        self.output_dir = Path(output_dir) if output_dir else OUTPUT_DIR
        self.output_dir.mkdir(exist_ok=True)

        # Load configuration
        config_path = config_path or CONFIG_FILE
        with open(config_path, 'r') as f:
            self.config = json.load(f)

        # Project paths
        self.project_root = self.config.get("project", {}).get(
            "project_root", "/tmp/cbmc/benchmark/test_cases/project_small"
        )
        self.translation_units = self.config.get("project", {}).get("translation_units", [])
        self.interleaving_files = self.config.get("project", {}).get("interleaving_source_files", [])
        self.interleaving = self.config.get("interleaving", [])

        # Determine include directories
        self.includes = ["include", "task_define", "isr_define", "common", "drivers", "middleware", "osek"]

        # Tool paths (can be overridden via environment)
        self.goto_cc = os.environ.get("GOTO_CC", "goto-cc")
        self.goto_cbmc = os.environ.get("GOTO_CBMC", "goto-cbmc")
        self.docker_image = os.environ.get("CBMC_DOCKER_IMAGE", "ghcr.io/diffblue/cbmc:latest")

    def log(self, message, level="INFO"):
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print(f"[{timestamp}] [{level}] {message}")

    def run_command(self, cmd, cwd=None, capture=True, check=True):
        """Execute a command and return result."""
        self.log(f"Running: {' '.join(cmd) if isinstance(cmd, list) else cmd}")

        if isinstance(cmd, str):
            shell = True
        else:
            shell = False

        try:
            if capture:
                result = subprocess.run(
                    cmd,
                    cwd=cwd,
                    shell=shell,
                    capture_output=True,
                    text=True
                )
            else:
                result = subprocess.run(
                    cmd,
                    cwd=cwd,
                    shell=shell
                )

            if check and result.returncode != 0:
                self.log(f"Command failed with exit code {result.returncode}", "ERROR")
                if capture and result.stderr:
                    self.log(f"stderr: {result.stderr}", "ERROR")
                return None

            return result
        except FileNotFoundError as e:
            self.log(f"Command not found: {cmd}", "ERROR")
            return None

    def build_goto_binaries(self):
        """Compile all source files to goto binaries."""
        self.log("Building goto binaries...")

        goto_binary = self.output_dir / "osek_project.out"
        json_output = self.output_dir / "interleaving_harness_generated.json"

        # Build include flags
        include_flags = []
        for inc in self.includes:
            include_flags.extend(["-I", str(PROJECT_ROOT / inc)])

        # Build command
        cmd = [
            self.goto_cc,
            *include_flags,
            f"--interleaving-project-root", str(PROJECT_ROOT),
            f"--interleaving-source-files", ",".join(self.interleaving_files),
            f"--interleaving-output", str(json_output),
        ]

        # Add all translation units
        for tu in self.translation_units:
            tu_path = PROJECT_ROOT / tu
            if tu_path.exists():
                cmd.append(str(tu_path))
            else:
                self.log(f"Warning: Translation unit not found: {tu_path}", "WARN")

        # Add harness
        harness_path = PROJECT_ROOT / "harness.c"
        if harness_path.exists():
            cmd.append(str(harness_path))

        cmd.extend([
            "-o", str(goto_binary)
        ])

        result = self.run_command(cmd, cwd=str(PROJECT_ROOT))

        if result is not None and result.returncode == 0:
            self.log(f"Successfully built goto binary: {goto_binary}")
            return True
        else:
            self.log("Failed to build goto binary", "ERROR")
            return False

    def run_cbmc_verification(self):
        """Run CBMC verification with interleaving analysis."""
        self.log("Running CBMC verification...")

        goto_binary = self.output_dir / "osek_project.out"

        if not goto_binary.exists():
            self.log(f"Goto binary not found: {goto_binary}", "ERROR")
            return False

        # CBMC options for interleaving analysis
        cbmc_flags = [
            "--unwind", "5",
            "--depth", "100",
            "--no-unwinding-assertions",
            "--partial-order", "--dfs",
        ]

        cmd = [
            self.goto_cbmc,
            str(goto_binary),
            *cbmc_flags,
        ]

        result = self.run_command(cmd, cwd=str(PROJECT_ROOT))

        report_path = self.output_dir / "cbmc_report.txt"

        if result is not None:
            with open(report_path, 'w') as f:
                f.write(f"CBMC Verification Report\n")
                f.write(f"Generated: {datetime.now().isoformat()}\n")
                f.write(f"=" * 60 + "\n\n")
                f.write(f"Command: {' '.join(cmd)}\n\n")
                f.write(f"STDOUT:\n{result.stdout}\n\n")
                if result.stderr:
                    f.write(f"STDERR:\n{result.stderr}\n")

            self.log(f"Verification report saved to: {report_path}")
            return result.returncode == 0

        return False

    def run_in_docker(self):
        """Run CBMC verification inside a Docker container."""
        self.log(f"Running in Docker: {self.docker_image}")

        # Check if Docker is available
        docker_check = self.run_command(["docker", "--version"], capture=True, check=False)
        if docker_check is None or docker_check.returncode != 0:
            self.log("Docker is not available. Falling back to local execution.", "WARN")
            return self.run_local()

        # Prepare Docker command
        docker_cmd = [
            "docker", "run", "--rm",
            "-v", f"{PROJECT_ROOT}:/app/project_small",
            "-w", "/app/project_small",
            self.docker_image,
            "sh", "-c",
            f"cd /app/project_small && python3 run_cbmc.py --build --verify --output /app/project_small/cbmc_output"
        ]

        result = self.run_command(docker_cmd, capture=True)

        if result is not None:
            self.log("Docker execution completed")
            # Copy results back
            return result.returncode == 0

        return False

    def run_local(self):
        """Run CBMC locally on Windows."""
        self.log("Running locally...")

        # Check for required tools
        for tool in [self.goto_cc, self.goto_cbmc]:
            tool_check = shutil.which(tool)
            if not tool_check:
                self.log(f"Warning: {tool} not found in PATH", "WARN")

        # Build and verify
        if self.build_goto_binaries():
            return self.run_cbmc_verification()

        return False

    def generate_summary_report(self):
        """Generate a summary report of the verification run."""
        report = {
            "timestamp": datetime.now().isoformat(),
            "project_root": str(PROJECT_ROOT),
            "translation_units_count": len(self.translation_units),
            "interleaving_functions": [item.get("name") for item in self.interleaving],
            "output_directory": str(self.output_dir),
        }

        # Check for generated files
        report_files = list(self.output_dir.glob("*"))
        report["generated_files"] = [str(f.name) for f in report_files]

        summary_path = self.output_dir / "summary_report.json"
        with open(summary_path, 'w') as f:
            json.dump(report, f, indent=2)

        self.log(f"Summary report saved to: {summary_path}")

        # Print summary
        print("\n" + "=" * 60)
        print("VERIFICATION SUMMARY")
        print("=" * 60)
        print(f"Project: {PROJECT_ROOT.name}")
        print(f"Source files: {len(self.translation_units)}")
        print(f"Interleaving functions: {len(self.interleaving)}")
        print(f"Output directory: {self.output_dir}")
        print(f"Generated files: {len(report_files)}")
        print("=" * 60)

        return report


def main():
    parser = argparse.ArgumentParser(
        description="OSEK CBMC Verification Automation Script",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )

    parser.add_argument(
        "--build", action="store_true",
        help="Build goto binaries only"
    )
    parser.add_argument(
        "--verify", action="store_true",
        help="Run verification only"
    )
    parser.add_argument(
        "--docker", action="store_true",
        help="Run verification in Docker container"
    )
    parser.add_argument(
        "--config", type=str,
        help="Path to configuration JSON file"
    )
    parser.add_argument(
        "--output", type=str,
        help="Output directory for results"
    )
    parser.add_argument(
        "--tool-path", type=str,
        help="Custom path to goto-cc and goto-cbmc binaries"
    )

    args = parser.parse_args()

    # Initialize automation
    automation = CBMCAutomation(
        config_path=args.config,
        output_dir=args.output,
        use_docker=args.docker
    )

    # Override tool paths if specified
    if args.tool_path:
        os.environ["GOTO_CC"] = os.path.join(args.tool_path, "goto-cc")
        os.environ["GOTO_CBMC"] = os.path.join(args.tool_path, "goto-cbmc")

    # Determine action
    if args.docker:
        success = automation.run_in_docker()
    elif args.build:
        success = automation.build_goto_binaries()
    elif args.verify:
        success = automation.run_cbmc_verification()
    else:
        # Run full pipeline: build and verify
        success = automation.run_local()

    # Generate summary report
    if success:
        automation.generate_summary_report()

    # Exit with appropriate code
    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()