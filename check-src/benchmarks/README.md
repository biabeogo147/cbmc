# check-src Benchmarks

Thu muc nay la lop benchmark runner cho `check-src`. Source benchmark thuc te
nam o `check-src/simple-benchmarks`; cac file trong thu muc nay chi mo ta cach
chay, cach inject ISR, cach do thoi gian/RAM, va cach luu ket qua.

## Luong chay chinh

```text
suite json
  -> run_suite.sh
  -> common/runner.py
  -> stock_naive: inject_naive.py -> stock goto-cc -> stock cbmc
  -> improved_targeted: improved goto-cc manifest -> aib inject -> improved goto-cc -> improved cbmc
  -> results/<suite>.csv + work/logs
```

Hai bien the duoc so sanh:

| Bien the | Y nghia |
| --- | --- |
| `stock_naive` | Copy source tree, chen loi goi ISR nondeterministic vao nhieu diem statement bang `inject_naive.py`, bien dich bang CBMC/goto-cc goc, roi verify bang CBMC goc. |
| `improved_targeted` | Dung `goto-cc` cai tien de sinh interleaving manifest, dung `aib` de inject dung cac diem interleaving muc tieu, bien dich va verify bang CBMC/goto-cc cai tien. |

## Thu muc va file

| Path | Vai tro |
| --- | --- |
| `.gitignore` | Bo qua output sinh ra khi benchmark: `work/`, CSV/log trong `results/`, `summary.md`; giu lai `results/.gitkeep`. |
| `README.md` | Tai lieu nay: giai thich cau truc benchmark va y nghia tung config. |
| `VERIFICATION_PROTOCOL.md` | Quy tac report headline: ghi moi truong, version toolchain, dung cung function/unwind/property, report median, va chi so sanh khi ket qua verification tuong thich. |
| `manifest.schema.json` | JSON schema cho cac file suite trong `suites/`. Dung de biet field nao bat buoc va kieu du lieu mong doi. |
| `run_suite.sh` | Entrypoint chay mot suite: nap `common/env.sh`, roi goi `common/runner.py <suite.json>`. |
| `run_all.sh` | Quet tat ca `suites/*.json`, chi chay suite co top-level `enabled: true`. |
| `common/env.sh` | Thiet lap bien moi truong mac dinh: duong dan repo, CBMC/goto-cc goc/cai tien, `aib`, `WORK`, `RESULTS_DIR`, `PYTHON`. |
| `common/runner.py` | Runner chinh: validate manifest, copy source, chay cac phase, sample RSS tu `/proc/<pid>/status`, ghi CSV va log. |
| `common/inject_naive.py` | Tao source tree cho `stock_naive`; chen prologue `nondet_bool` va loi goi tung ISR sau cac statement hop le. |
| `common/inject_naive_isr.sh` | Wrapper shell cho `inject_naive.py`, tien dung khi can test injection thu cong. |
| `common/measure.sh` | Helper do command bang shell. Hien tai `runner.py` co logic do rieng, file nay giu cho script shell/legacy. |
| `common/report.sh` | Doc CSV trong `results/` va tao `results/summary.md` voi median verify time/RAM cho `stock_naive` va `improved_targeted`. |
| `common/validate_manifest.sh` | Kiem tra mot suite JSON: field bat buoc, root/source/include ton tai, va ISR function khong rong voi case enabled. |
| `importers/` | Placeholder script de import/normalize benchmark ngoai repo. Chua tu dong tai benchmark trong luong chay mac dinh. |
| `results/` | Noi luu CSV va summary report. `results/*.csv` la output sinh ra va dang bi ignore de tranh commit so lieu tam. |
| `results/.gitkeep` | Giu thu muc `results/` trong git du khong commit CSV. |
| `suites/` | Cac manifest JSON mo ta benchmark suite/case. Day la noi them benchmark moi. |
| `tests/selftest.ps1` | Structural test tren Windows: verify file framework ton tai, suite JSON parse duoc, enabled case co path hop le, va README top-level cua `check-src` co document cac item. |
| `work/` | Output tam sinh ra khi chay benchmark: source copy, injected tree, goto binary, logs, stock toolchain copy. Day la generated artifact va bi ignore. |

## Bien moi truong

`common/env.sh` doc cac bien moi truong duoc runner dung. Co the override khi chay
Docker/WSL/Linux:

| Bien | Mac dinh | Tac dung |
| --- | --- | --- |
| `IMPROVED_CBMC` | `$REPO_ROOT/cmake-build-debug-cbmc/bin/cbmc` | CBMC ban cai tien dung cho `improved_targeted` verify. |
| `IMPROVED_GOTOCC` | `$REPO_ROOT/cmake-build-debug-cbmc/bin/goto-cc` | goto-cc ban cai tien dung de sinh manifest va compile source da inject. |
| `STOCK_CBMC` | `$IMPROVED_CBMC` | CBMC goc dung cho `stock_naive`. Khi benchmark that su, nen tro den binary goc, vi du copy tu `diffblue/cbmc`. |
| `STOCK_GOTOCC` | `$IMPROVED_GOTOCC` | goto-cc goc dung cho `stock_naive` compile. |
| `AIB` | `$REPO_ROOT/cmake-build-debug-cbmc/bin/aib` | Tool inject interleaving theo manifest do improved `goto-cc` sinh ra. |
| `WORK` | `/tmp/cbmc_check_src_benchmarks` | Thu muc tam chua source copy, injected tree va logs. Trong Docker hien tai thuong set ve `/repo/check-src/benchmarks/work/run-current`. |
| `RESULTS_DIR` | `$BENCHMARK_DIR/results` | Thu muc ghi CSV/summary. |
| `PYTHON` | `python3` | Python interpreter de chay runner va helper. |

## Cau truc suite JSON

Moi file trong `suites/*.json` co mot top-level suite va mot danh sach `cases`.
Duong dan trong manifest la relative tu repo root.

### Top-level fields

| Field | Bat buoc | Runner hien tai dung? | Y nghia |
| --- | --- | --- | --- |
| `suite_name` | Co | Co | Ten suite, dung lam prefix console/log va ten CSV `results/<suite_name>.csv`. |
| `description` | Co | Metadata | Mo ta ngan ve suite. |
| `enabled` | Co | Co trong `run_all.sh` | `run_all.sh` chi chay suite co `enabled: true`; `run_suite.sh` van chay manifest duoc chi dinh truc tiep. |
| `runs` | Khong | Chua enforce trong `runner.py` | So lan do mong muon theo protocol. Hien tai runner chi ghi run `1`; field nay de giu y do benchmark lap lai. |
| `warmups` | Khong | Chua enforce trong `runner.py` | So warmup mong muon theo protocol. Hien tai chua sinh run warmup. |
| `variants` | Khong | Metadata | Liet ke bien the can so sanh, mac dinh y nghia la `stock_naive` va `improved_targeted`. Runner hien tai chay hai bien the nay co dinh. |
| `cases` | Co | Co | Mang case benchmark. Case disabled se bi bo qua. |

### Case fields

| Field | Bat buoc | Runner hien tai dung? | Y nghia |
| --- | --- | --- | --- |
| `name` | Co | Co | Ten case, dung trong console, CSV, log file va `work/<suite>/<case>/`. |
| `enabled` | Khong | Co | `false` thi runner va selftest bo qua case. |
| `reason` | Khong | Metadata | Ly do case disabled hoac ghi chu normalization. |
| `root` | Co | Co | Thu muc goc cua source case, relative tu repo root. Runner copy thu muc nay vao `work/`. |
| `sources` | Co | Co | Danh sach file compile bang `goto-cc`, relative tu `root`. |
| `include_dirs` | Co | Co | Danh sach include dir, relative tu `root`; runner convert thanh `-I<root>/<dir>`. |
| `isr_sources` | Co | Co | File chua ISR. `stock_naive` khong chen ISR vao cac file nay; `improved_targeted` truyen cac file nay cho `--interleaving-source-files`. |
| `isr_functions` | Co | Co voi `stock_naive` | Ten function ISR de `inject_naive.py` chen loi goi `if(nondet_bool()) isr(...);`. Improved pipeline lay diem inject tu manifest cua `goto-cc`. |
| `entry_function` | Co | Co | Gia tri cho `cbmc --function`. Thuong la `main`. |
| `properties` | Khong | Co | Danh sach property truyen bang `--property`. Neu rong, CBMC check theo cau hinh mac dinh cua command. |
| `unwind` | Co | Co | Gia tri cho `cbmc --unwind`. |
| `defines` | Khong | Chua enforce | Placeholder cho macro define compile, chua duoc runner them vao command. |
| `expected_result` | Khong | Metadata | Ghi ky vong so sanh, hien dung de doc/report, chua enforce. |
| `timeout_sec` | Co | Chua enforce | Gioi han thoi gian mong muon; runner hien tai chua kill process theo timeout. |
| `memory_limit_mb` | Co | Chua enforce | Gioi han RAM mong muon; runner hien tai chi sample RSS, chua enforce limit. |

## Cac suite hien co

| Suite | Enabled | Muc dich |
| --- | --- | --- |
| `local-smoke.json` | Co | Smoke test nho cho single-file ISR, file da inject san, va multi-file ISR toy case trong `simple-benchmarks`. Nen chay nhanh de kiem tra framework. |
| `osek-local.json` | Co | OSEK event/priority local demos. Mot so regression case disabled vi chua co ISR source rieng. |
| `trampoline-current.json` | Co | Benchmark chinh hien tai: Trampoline `alarms_s1_non`, 32 source file, ISR `isr1/isr2/isr3`, property `main.assertion.1..3`. |
| `trampoline-c-async.json` | Co | Tree Trampoline lich su dung de so sanh voi cach CPROVER async. |
| `trampoline-expanded.json` | Khong | Placeholder de mo rong them case Trampoline lon hon sau khi stub hardware-specific input. |
| `icbmc-interrupts.json` | Khong | Placeholder cho benchmark interrupt tu i-CBMC/CProver artifact sau khi import va ghi ro license/provenance. |
| `intabs-interrupts.json` | Khong | Placeholder cho benchmark IntAbs interrupt-driven sau khi import va normalize helper `__VERIFIER_*`. |

## Output va log

CSV co cac cot:

| Cot | Y nghia |
| --- | --- |
| `benchmark` | Ten suite. |
| `case` | Ten case. |
| `variant` | `stock_naive` hoac `improved_targeted`. |
| `phase` | `prepare`, `compile`, `verify`, `manifest`, hoac `inject`. |
| `run` | Run id. Hien tai runner ghi `1` cho phase do va `0` cho prepare. |
| `exit_code` | Exit code command. CBMC tra `10` khi verification failed. |
| `time_ms` | Wall-clock time do runner do. |
| `max_rss_kb` / `max_rss_mb` | Peak RSS sample tu `/proc/<pid>/status`. Can Linux/WSL/Docker de co so nay. |
| `summary` | Dong tom tat tu log, vi du `VERIFICATION FAILED`, `VERIFICATION SUCCESSFUL`, hoac loi start command. |

Log chi tiet nam trong `$WORK/logs` voi ten:

```text
<suite>.<case>.<variant>.<phase>.<run>.log
```

Source tam trong `$WORK/<suite>/<case>/`:

| Thu muc/file | Y nghia |
| --- | --- |
| `original/` | Source goc copy tu `root`. |
| `stock_naive/` | Source da inject naive ISR cho CBMC goc. |
| `improved_original/` | Source copy cho improved `goto-cc` sinh manifest. |
| `improved_targeted/` | Source da `aib` inject theo interleaving manifest. |
| `stock_naive.out` | GOTO binary cua `stock_naive`. |
| `improved_manifest.out` | GOTO binary tao trong phase manifest. |
| `improved_targeted.out` | GOTO binary cua source targeted da inject. |
| `interleaving_pipeline.json` | Manifest do improved `goto-cc` sinh ra. |
| `stock_naive_insertions.csv` | So diem inject naive theo tung source va tong `TOTAL`. |

## Cach them benchmark moi

1. Dat source o `check-src/simple-benchmarks/<ten-case>` hoac import vao
   `check-src/external` neu la artifact ngoai.
2. Tao hoac sua file `check-src/benchmarks/suites/<suite>.json`.
3. Dien `root`, `sources`, `include_dirs`, `isr_sources`, `isr_functions`,
   `entry_function`, `unwind`, `timeout_sec`, `memory_limit_mb`.
4. Chay dry-run:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/<suite>.json --dry-run
```

5. Chay benchmark that trong Docker/WSL/Linux de lay RSS:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/<suite>.json
```

6. Neu can summary tu CSV:

```bash
bash check-src/benchmarks/common/report.sh check-src/benchmarks/results
```
