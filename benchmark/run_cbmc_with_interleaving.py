import os
import subprocess
from pathlib import Path

def run_cbmc_with_interleaving(target_dir):
    target_path = Path(target_dir).expanduser().resolve()
    cbmc_bin = Path("/home/haven/Code/cbmc/build/bin/cbmc")
    goto_inst_bin = Path("/home/haven/Code/cbmc/build/bin/goto-instrument")
    goto_cc_bin = Path("/home/haven/Code/cbmc/build/bin/goto-cc")
    output_dir = Path("benchmark_results_with_interleaving")
    output_dir.mkdir(parents=True, exist_ok=True)

    print(f"Scanning {target_path} for .c files...")
    
    # Collect all .c files in the target directory to avoid "no body for callee" errors
    all_c_files = list(target_path.rglob("*.c"))
    # Collect all directories containing .c files to use as include paths
    include_dirs = sorted(list(set(f.parent for f in all_c_files)))
    include_args = [f"-I{d}" for d in include_dirs]

    for c_file in all_c_files:
        rel_path = c_file.relative_to(target_path)
        out_file = output_dir / rel_path.with_suffix(".log")
        out_file.parent.mkdir(parents=True, exist_ok=True)
        
        tmp_out = c_file.with_suffix(".out")
        tmp_inst_out = c_file.with_suffix(".inst.out")
        
        print(f"\n--- File: {c_file} ---")
        
        # Build the command using all source files and include paths
        cmd_gen = [str(goto_cc_bin)] + include_args + ["-o", str(tmp_out)] + [str(f) for f in all_c_files]
        print(f"Command to generate binary:\n{' '.join(cmd_gen)}")
        
        try:
            # 1. Generate binary
            subprocess.run(cmd_gen, check=True, capture_output=True)
            
            # 2. Instrument (using 'isr' as default ISR name as per previous logic)
            subprocess.run([str(goto_inst_bin), "--show-isr-writes", "isr", str(tmp_out), str(tmp_inst_out)], check=True, capture_output=True)
            
            # CBMC options for automotive code:
            cbmc_options = [
                "--bounds-check",
                "--pointer-check",
                "--signed-overflow-check",
                "--unsigned-overflow-check",
                "--div-by-zero-check",
                "--unwind", "10",
                "--unwinding-assertions",
                "--os-api", "osek",
                "--osek-oil", str(target_path / "app.oil"),
                "--function", "main"
            ]

            # 3. Verify
            with open(out_file, "w") as f:
                cbmc_cmd = [str(cbmc_bin), str(tmp_inst_out)] + cbmc_options
                result = subprocess.run(cbmc_cmd, capture_output=True, text=True)
                f.write(result.stdout)
                f.write(result.stderr)
            
            # Cleanup
            os.remove(tmp_out)
            os.remove(tmp_inst_out)
            
        except subprocess.CalledProcessError as e:
            print(f"Error processing {c_file}: {e}")

if __name__ == "__main__":
    import sys
    target = sys.argv[1] if len(sys.argv) > 1 else "/home/haven/Code/cbmc/benchmark/test_cases"
    run_cbmc_with_interleaving(target)
