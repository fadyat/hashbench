#!/bin/bash

# Following script is used to build a flamegraphs for hashtable
# aggregation process. Done for determining the hotspots in the code.
#
# Required tools:
# - perf: sudo apt-get install linux-tools-common linux-tools-generic
# - flamegraph: git clone https://github.com/brendangregg/Flamegraph.git
#
# Usage: .sudo ./perf.sh [hashtable_type]
# Example: ./perf.sh flamegraph.svg


set -euo pipefail
hashtable_type=${1:-std::unordered_map}

perf record -F 99 -g ../build/ydb-hashtables-bench ${hashtable_type}
perf script | ../vendor/flamegraph/stackcollapse-perf.pl | ../vendor/flamegraph/flamegraph.pl > ${hashtable_type}.svg
