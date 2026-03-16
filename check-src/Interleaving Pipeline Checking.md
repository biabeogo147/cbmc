$ProjectFileDir$

goto-cc check-src/t_isr.c -o check-src/t_isr.out
goto-instrument --show-isr-writes isr1,isr2 check-src/t_isr.out check-src/t_isr_optimized.out
aib check-src/t_isr.c path/to/interleaving_adding.json check-src/t_isr_added.c

```
Reading GOTO program from 'check-src/t_isr.out'
[POR] --- PHÂN TÍCH ISR: isr2 ---
 -> Ghi vào biến: x

[POR] --- PHÂN TÍCH LUỒNG CHÍNH ---
Hàm: main
  [Dòng 24] Đọc(isr2) 
  [Dòng 26] Đọc(task1) 
  [Dòng 27] Đọc(task2) 
  [Dòng 29] Đọc(x) 
Hàm: task2
  [Dòng 20] Đọc(x) Ghi(x) 
Hàm: task1
  [Dòng 16] Đọc(x) Ghi(x) 

Process finished with exit code 0
```