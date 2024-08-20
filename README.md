# sysinfo

A binary that collects some system info

## Quick Start

```bash
cmake -S . -B build
cmake --build build
build/sysinfo
```

## Contributing

```bash
podman run --rm -v ${PWD}:/src ghcr.io/cwpearson/clang-format-14 clang-format -i main.cpp cmake/version.hpp.in
```