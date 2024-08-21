#! /bin/bash

set -eou pipefail

cmake -S "$SYSINFO_SRC" -B "$SYSINFO_BUILD"

cmake --build "$SYSINFO_BUILD"

chmod -R ugo+rwx "$SYSINFO_BUILD"
