# ISR Benchmark Result

Ngay chay: 2026-05-30  
Moi truong: Docker `bkmeeting-vpcd-aimet:ubuntu22.04-py310`  
Benchmark suite: `check-src/benchmarks/suites/trampoline-current.json`  
Case: `trampoline-alarms-s1-non`  
Source root: `check-src/simple-benchmarks/trampoline`  
Quy mo source: 32 file C/H, 6599 LOC

## Toolchain

| Bien the | CBMC | goto-cc | Ghi chu |
| --- | --- | --- | --- |
| CBMC goc | 5.95.0 | goto-cc 5.95.0 | Lay tu image `diffblue/cbmc:5.95.0`, copy vao Docker run workspace |
| CBMC cai tien | 6.8.0 | goto-cc 6.8.0 | Dung binary trong `cmake-build-debug-cbmc/bin` |

Lenh benchmark da chay trong Docker:

```bash
docker run --rm \
  -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" \
  -w /repo \
  -e STOCK_CBMC=/repo/check-src/benchmarks/work/stock-toolchain/bin/cbmc \
  -e STOCK_GOTOCC=/repo/check-src/benchmarks/work/stock-toolchain/bin/goto-cc \
  -e IMPROVED_CBMC=/repo/cmake-build-debug-cbmc/bin/cbmc \
  -e IMPROVED_GOTOCC=/repo/cmake-build-debug-cbmc/bin/goto-cc \
  -e AIB=/repo/cmake-build-debug-cbmc/bin/aib \
  -e WORK=/repo/check-src/benchmarks/work/run-current \
  bkmeeting-vpcd-aimet:ubuntu22.04-py310 \
  bash -lc "python3 -m py_compile check-src/benchmarks/common/runner.py check-src/benchmarks/common/inject_naive.py && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/trampoline-current.json"
```

## Ket qua do duoc

Raw CSV: `check-src/benchmarks/results/trampoline-current.csv`

| Bien the | Phase | Exit code | Time (ms) | Peak RSS (MB) | Ket qua |
| --- | --- | ---: | ---: | ---: | --- |
| CBMC goc naive | compile | 0 | 32331 | 33.7 | OK |
| CBMC goc naive | verify | 10 | 549 | 32.3 | VERIFICATION FAILED |
| CBMC cai tien targeted | manifest | 0 | 31734 | 25.2 | OK |
| CBMC cai tien targeted | inject | 0 | 2984 | 4.1 | OK |
| CBMC cai tien targeted | compile | 0 | 32658 | 26.0 | OK |
| CBMC cai tien targeted | verify | 10 | 1866 | 28.6 | VERIFICATION FAILED |

## So sanh truc tiep

| So sanh | CBMC goc | CBMC cai tien | Chenh lech |
| --- | ---: | ---: | ---: |
| Compile time | 32331 ms | 32658 ms | cham hon 1.0% |
| Compile peak RSS | 33.7 MB | 26.0 MB | it RAM hon 22.7% |
| Verify time | 549 ms | 1866 ms | cham hon 239.9% |
| Verify peak RSS | 32.3 MB | 28.6 MB | it RAM hon 11.4% |
| Tong pipeline do duoc | 32880 ms | 69242 ms | cham hon 110.6% |
| Peak RSS lon nhat trong pipeline | 33.7 MB | 28.6 MB | it RAM hon 15.1% |

Ghi chu: `Tong pipeline do duoc` cua ban cai tien bao gom `manifest + inject + compile + verify`.
Voi CBMC goc, pipeline do duoc gom `compile + verify`; buoc chen ISR naive duoc ghi log rieng
nhung khong tinh thoi gian trong CSV hien tai.

## Ket qua verification

Hai bien the cung kiem tra cac property chinh va cho cung ket qua:

| Property | CBMC goc | CBMC cai tien |
| --- | --- | --- |
| `main.assertion.1` | SUCCESS | SUCCESS |
| `main.assertion.2` | FAILURE | FAILURE |
| `main.assertion.3` | FAILURE | FAILURE |

Ca hai log deu co canh bao:

```text
WARNING: Use --unwinding-assertions to obtain sound verification results
```

## ISR injection

| Bien the | So diem chen ISR |
| --- | ---: |
| CBMC goc naive | 741 |
| CBMC cai tien targeted | 6 |

Ban cai tien giam so diem chen ISR tu 741 xuong 6, tuc la giam 99.2%.

## Ket luan

Tren benchmark `trampoline-alarms-s1-non`, ban cai tien dang cho loi the ro ve kich thuoc
instrumentation va RAM: compile it RAM hon 22.7%, verify it RAM hon 11.4%, va tong peak RSS
pipeline it hon 15.1%. Tuy nhien, thoi gian compile hien tai cham hon 1.0%, thoi gian verify
rieng le cham hon CBMC goc 239.9%, va tong pipeline do duoc cham hon 110.6% vi phai them hai
buoc `manifest` va `inject`.

Vi vay ket qua hien tai nen duoc doc la: cai tien da thu hep manh so interleaving can chen va
giam RAM, nhung chua chung minh duoc speedup thoi gian tren case Trampoline nay.
