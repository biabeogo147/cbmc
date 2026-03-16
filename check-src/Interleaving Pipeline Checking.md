$ProjectFileDir$

goto-cc check-src/t_isr.c -o check-src/t_isr.out
goto-instrument --show-interleaving-checking isr1,isr2 check-src/t_isr.out check-src/t_isr_optimized.out check-src/interleaving_adding_config.json
aib check-src/t_isr.c check-src/interleaving_adding_config.json check-src/t_isr_added.c