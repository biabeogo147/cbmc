# aib (interleaving block injector)

Build standalone (without full CBMC build):

```bash
g++ -std=c++17 -O2 -o aib src/lib-interleaving-block/aib.cpp
```

Build via CMake target (binary at `build/bin/aib`):

```bash
cmake -S . -B build
cmake --build build --target aib
```

Usage:

```bash
aib file.c file.json new_file.c
```
