#!/usr/bin/env python3
"""
Generate goto-cc command for CBMC interleaving analysis.
Outputs a shell-compatible command string for use in Docker/CI environments.
"""

import os
import json
import sys
from pathlib import Path


def generate_build_command(config_path=None, project_root=None):
    """
    Generate goto-cc command for building the OSEK project with interleaving support.

    Args:
        config_path: Path to interleaving_harness.json (default: ./interleaving_harness.json)
        project_root: Docker path for the project (default: /tmp/cbmc/benchmark/test_cases/project_small)

    Returns:
        str: Shell command for goto-cc
    """
    if config_path is None:
        config_path = Path(__file__).parent / "interleaving_harness.json"
    else:
        config_path = Path(config_path)

    if project_root is None:
        docker_root = "/tmp/cbmc/benchmark/test_cases/project_small"
    else:
        docker_root = project_root

    if not config_path.exists():
        print(f"Error: Config file not found: {config_path}", file=sys.stderr)
        sys.exit(1)

    with open(config_path, 'r') as f:
        config = json.load(f)

    project_config = config.get("project", {})

    # Build include directories
    include_dirs = ["include", "task_define", "isr_define", "common", "drivers", "middleware", "osek"]
    include_flags = []
    for inc in include_dirs:
        include_flags.append(f"-I{docker_root}/{inc}")

    # Interleaving project root
    proj_root_flag = f"--interleaving-project-root {docker_root}"

    # Interleaving source files (comma-separated list)
    interleaving_files = project_config.get("interleaving_source_files", [])
    isr_files = " ".join([f"{docker_root}/{f}" for f in interleaving_files])
    isr_src_flag = f"--interleaving-source-files {isr_files}"

    # Interleaving output JSON
    json_out_flag = f"--interleaving-output {docker_root}/interleaving_harness.json"

    # Translation units (positional arguments)
    translation_units = project_config.get("translation_units", [])
    tu_args = []
    for tu in translation_units:
        tu_path = tu.lstrip('/')
        tu_args.append(f"{docker_root}/{tu_path}")

    # Output binary
    output_flag = f"-o {docker_root}/interleaved.out"

    # Build command
    parts = []

    # Include flags
    parts.extend(include_flags)

    # Project root
    parts.append(proj_root_flag)

    # Source files
    parts.append(isr_src_flag)

    # Output JSON
    parts.append(json_out_flag)

    # Translation units
    parts.extend(tu_args)

    # Output binary
    parts.append(output_flag)

    return "goto-cc " + " ".join(parts)


def main():
    if len(sys.argv) > 1:
        config_path = sys.argv[1]
    else:
        config_path = None

    if len(sys.argv) > 2:
        project_root = sys.argv[2]
    else:
        project_root = None

    cmd = generate_build_command(config_path, project_root)
    print(cmd)


if __name__ == "__main__":
    main()