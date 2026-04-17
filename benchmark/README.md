# Benchmark

### Folder structure

- /bin: compiled binaries from goto-cc
- /scripts: automate compiling 
- /log: saved data from analyzing binaries
- /test_cases: projects used to test the new implementations

### Test cases information

- https://github.com/langroodi/Adaptive-AUTOSAR
- project_small: 
  - self-written tests that runs dummy tasks (~30-40 tasks) with difference priorities
  - tested with goto-cc. use ```generate_build_cmd.py``` to get the interleaved goto-cc command.
  - intentionally added Time-of-Check-to-Time-of-Use Race Condition (task_main.c)