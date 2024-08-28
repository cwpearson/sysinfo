# sysinfo

A linux tool that prints some system info.

## Quick Start: Precompiled Binaries

Download from [Latest Release](https://github.com/cwpearson/sysinfo/releases/latest)

|OS | Arch | Binary |
|-|-|-|
| Linux | `arm64`/`aarch64` | `sysinfo-linux-arm64` |
| Linux | `amd64` | `sysinfo-linux-amd64` |
| Linux | `ppc64le` | `sysinfo-linux-ppc64le` |
| macOS | `amd64` | `sysinfo-macos-amd64` |
| macOS | `arm` | `sysinfo-macos-arm` |

## Example

```
==sysinfo== date ==sysinfo==
[redacted]

==sysinfo== whoami ==sysinfo==
[redacted]

==sysinfo== hostname ==sysinfo==
[redacted]

==sysinfo== cat /etc/os-release ==sysinfo==
NAME="Red Hat Enterprise Linux Server"
VERSION="7.9 (Maipo)"
ID="rhel"
ID_LIKE="fedora"
VARIANT="Server"
VARIANT_ID="server"
VERSION_ID="7.9"
PRETTY_NAME="Red Hat Enterprise Linux Server 7.9 (Maipo)"
ANSI_COLOR="0;31"
CPE_NAME="cpe:/o:redhat:enterprise_linux:7.9:GA:server"
HOME_URL="https://www.redhat.com/"
BUG_REPORT_URL="https://bugzilla.redhat.com/"

REDHAT_BUGZILLA_PRODUCT="Red Hat Enterprise Linux 7"
REDHAT_BUGZILLA_PRODUCT_VERSION=7.9
REDHAT_SUPPORT_PRODUCT="Red Hat Enterprise Linux"
REDHAT_SUPPORT_PRODUCT_VERSION="7.9"

==sysinfo== uname -a ==sysinfo==
Linux [redacted] 4.14.0-115.35.1.3chaos.ch6a.ppc64le #1 SMP Wed Jul 21 17:12:16 PDT 2021 ppc64le ppc64le ppc64le GNU/Linux

==sysinfo== lscpu ==sysinfo==
Architecture:          ppc64le
Byte Order:            Little Endian
CPU(s):                128
On-line CPU(s) list:   0-127
Thread(s) per core:    4
Core(s) per socket:    16
Socket(s):             2
NUMA node(s):          6
Model:                 2.3 (pvr 004e 1203)
Model name:            POWER9, altivec supported
CPU max MHz:           3800.0000
CPU min MHz:           2300.0000
L1d cache:             32K
L1i cache:             32K
L2 cache:              512K
L3 cache:              10240K
NUMA node0 CPU(s):     0-63
NUMA node8 CPU(s):     64-127
NUMA node252 CPU(s):
NUMA node253 CPU(s):
NUMA node254 CPU(s):
NUMA node255 CPU(s):

==sysinfo== module list ==sysinfo==

Currently Loaded Modules:
  1) base-gcc/8.3.1                           3) spectrum-mpi/rolling-release   5) StdEnv (S)
  2) clang/ibm-16.0.6-cuda-11.2.0-gcc-8.3.1   4) cuda/11.2.0

  Where:
   S:  Module is Sticky, requires --force to unload or purge

==sysinfo== cmake --version ==sysinfo==
cmake version 3.14.5

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```

## Compile from Source

* Requires a C++11 compiler and CMake 3.1

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

- [ ] armv7 precompiled binary
- [x] arm64 precompiled binary
- [x] ppc64le precompiled binary
- [x] CI: test binary
  - [ ] ppc64le
- [x] macOS-amd64 precompiled binary
- [x] macOS-arm precompiled binary
- Nvidia software stuff
  - [x] `nvcc --version`
  - [x] `nvidia-smi`
- ROCm software stuff
  - [x] `rocm-smi`
- Intel stuff
- [x] numactl
- [ ] CMake 3.27 deprecated compatibility with CMake < 3.5
- mpi stuff
  - [x] `mpirun --version`
  - [x] `mpicc --version`
  - [ ] `mpichversion`
  - [ ] `ompi_info` 
