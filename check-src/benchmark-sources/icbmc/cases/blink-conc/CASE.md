# blink-conc

Origin: `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/blink/nobug/blink_conc.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 2

Harness notes:
- Removed TinyOS packed attributes from normalized copies so goto-cc can parse the conc-code source.
- Normalized TinyOS nx array declarators from `char unsigned (data[N]);` to `char unsigned data[N];`.
- Restored fixed-width typedefs that upstream leaves inside a `/* Lihao */` comment block.
- Removed duplicate `size_t` typedef because CBMC provides `size_t`.
- Removed duplicate internal `__int32_t` and `__uint32_t` typedefs because CBMC provides them.
- Normalized task signatures and async direct calls to match the existing `static void task(void)` prototypes.

ISR/task functions:
- `VirtualizeTimerC_0_updateFromTimer_runTask`
- `AlarmToTimerC_0_fired_runTask`
