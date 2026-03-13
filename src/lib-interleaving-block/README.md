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

If you use CLion with Docker toolchain, build in CLion's Docker build directory
(the workspace in this environment uses `cmake-build-debug-docker/`):

```bash
cmake -S . -B cmake-build-debug-docker
cmake --build cmake-build-debug-docker --target aib
```


If CLion reload does not show `aib` (usually due missing CBMC dependencies such as
`flex`/`bison` in the selected toolchain), use a dedicated CMake profile with:

```bash
cmake -S . -B cmake-build-debug-docker -DAIB_ONLY=ON
cmake --build cmake-build-debug-docker --target aib
```

This config builds only `aib` and skips the full CBMC tree.

Expected binary path in that setup:

```bash
./cmake-build-debug-docker/bin/aib
```

Usage:

```bash
./cmake-build-debug-docker/bin/aib file.c file.json new_file.c
# or
./build/bin/aib file.c file.json new_file.c
```
