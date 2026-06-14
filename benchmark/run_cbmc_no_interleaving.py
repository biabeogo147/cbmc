import os
import subprocess
from pathlib import Path
from datetime import datetime

def run_cbmc_no_interleaving(target_dir, unwind_depth):
    target_path = Path(target_dir).expanduser().resolve()
    cbmc_bin = Path("/home/haven/Code/cbmc/build/bin/cbmc")
    
    # Flag Sanitization: Ensure unwind_depth is a positive integer
    try:
        unwind_val = int(unwind_depth)
        if unwind_val < 0:
            raise ValueError
    except (ValueError, TypeError):
        print(f"Invalid unwind depth '{unwind_depth}'. Defaulting to 10.")
        unwind_val = 10

    # CBMC options for automotive code:
    cbmc_options = [
        "--bounds-check",
        "--pointer-check",
        "--signed-overflow-check",
        "--unsigned-overflow-check",
        "--div-by-zero-check",
        "--unwind", str(unwind_val),
        "--unwinding-assertions",
        "--os-api", "osek",
        "--osek-oil", str(target_path / "app.oil"),
        "--function", "main"
    ]

    print(f"Scanning {target_path} for .c files...")
    
    all_c_files = list(target_path.rglob("*.c"))
    if not all_c_files:
        print("No .c files found in target directory.")
        return

    include_dirs = sorted(list(set(f.parent for f in all_c_files)))
    include_args = [f"-I{d}" for d in include_dirs]

    # Temporary binary location (will be moved to result folder on success)
    tmp_out = target_path / "harness.out"
    goto_cc_bin = Path("/home/haven/Code/cbmc/build/bin/goto-cc")
    
    cmd_gen = [str(goto_cc_bin)] + include_args + ["-o", str(tmp_out)] + [str(f) for f in all_c_files]
    print(f"Command to generate binary:\n{' '.join(cmd_gen)}")
    
    try:
        # 1. Generate the single binary
        subprocess.run(cmd_gen, check=True, capture_output=True)
        
        # 2. Run CBMC
        print(f"Running CBMC on {tmp_out}...")
        cbmc_cmd = [str(cbmc_bin), str(tmp_out)] + cbmc_options
        result = subprocess.run(cbmc_cmd, capture_output=True, text=True)
        
        # 3. Create result folder structure ONLY after successful execution
        # Format: result/projectname-YYYYMMDD_HHMMSS
        project_name = target_path.name
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        run_folder = Path("result") / f"{project_name}-{timestamp}"
        run_folder.mkdir(parents=True, exist_ok=True)
        
        # Move binary and save log
        final_out = run_folder / "harness.out"
        final_log = run_folder / "harness.log"
        
        # Move the binary from project root to result folder
        os.rename(tmp_out, final_out)
        
        with open(final_log, "w") as f:
            f.write(result.stdout)
            f.write(result.stderr)
        
        print(f"Verification complete. Results saved in: {run_folder}")
        print(f"Binary: {final_out}, Log: {final_log}")
        
    except subprocess.CalledProcessError as e:
        print(f"Error during execution: {e}")
        if tmp_out.exists():
            os.remove(tmp_out)
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
        if tmp_out.exists():
            os.remove(tmp_out)

if __name__ == "__main__":
    import sys
    target = sys.argv[1] if len(sys.argv) > 1 else "/home/haven/Code/cbmc/benchmark/test_cases"
    unwind = sys.argv[2] if len(sys.argv) > 2 else "10"
    run_cbmc_no_interleaving(target, unwind)
