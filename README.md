# sysinfo

A linux tool that prints some system info.

## Precompiled Binaries

Available at [Releases](https://github.com/cwpearson/sysinfo/releases/latest)

| Arch | Binary |
|-|-|
| `arm64`/`aarch64` | `sysinfo-arm64` |
| `amd64` | `sysinfo-amd64` | 

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

## Roadmap

- [ ] armv7
- [x] ppc64le
- [x] CI: test binary