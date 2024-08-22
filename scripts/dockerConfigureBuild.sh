#! /bin/bash

set -eou pipefail

mkdir -p "$SYSINFO_BUILD"
(cd "$SYSINFO_BUILD"; cmake "$SYSINFO_SRC")

make -C "$SYSINFO_BUILD"

chmod -R ugo+rwx "$SYSINFO_BUILD"
