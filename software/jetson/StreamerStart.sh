#!/usr/bin/env bash
# Run on Jetson Linux. PYTHON_BIN may point to a virtual environment's python.
set -euo pipefail
cd -- "$(dirname -- "${BASH_SOURCE[0]}")"
PYTHON_BIN="${PYTHON_BIN:-/usr/bin/python3}"
children=()

cleanup() {
    trap - EXIT INT TERM
    for pid in "${children[@]}"; do
        kill -TERM "$pid" 2>/dev/null || true
    done
    for pid in "${children[@]}"; do
        wait "$pid" 2>/dev/null || true
    done
}
trap cleanup EXIT
trap 'exit 0' INT TERM

"$PYTHON_BIN" -u GStreamerTest.py &
children+=("$!")
"$PYTHON_BIN" -u V5StreamerNX.py &
children+=("$!")

# Either process ending is unexpected. Stop its sibling and let systemd restart.
status=0
wait -n "${children[@]}" || status=$?
if (( status == 0 )); then status=1; fi
exit "$status"
