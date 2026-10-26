#!/bin/bash
# Builds the 500-line access.log used in Lab 3 (format: DATE TIME USER STATUS PAGE).
# Every 5th request fails; users cycle user0..user6, pages cycle /page0../page3.
out=${1:-access.log}
for ((i = 1; i <= 500; i++)); do
    status=OK
    (( i % 5 == 0 )) && status=FAIL
    printf '2026-10-05 10:%02d user%d %s /page%d\n' $((i % 60)) $((i % 7)) "$status" $((i % 4))
done > "$out"
echo "generated $(wc -l < "$out") lines in $out"
