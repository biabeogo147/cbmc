# Interleaving Pipeline Checking

## Current Pipeline

```sh
# Get into the preprocessor container
docker exec -it preprocessor bash
gcc -E -P harness.c -I isr_define -I task_define -o harness.i

goto-cc check-src/t_isr.c -o check-src/t_isr.out
goto-instrument --interleaving-checking isr1,isr2 --interleaving-output check-src/interleaving_adding_config.json check-src/t_isr.out check-src/t_isr_optimized.out
aib check-src/t_isr.c check-src/interleaving_adding_config.json check-src/t_isr_added.c
```

## Using interleaving-analysis in goto-cc

Use the shared analysis directly from `goto-cc`

```sh
goto-cc check-src/t_isr.c --interleaving-checking isr1,isr2 --interleaving-output check-src/interleaving_adding_config.json -o check-src/t_isr.out
```