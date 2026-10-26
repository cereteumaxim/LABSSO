#!/bin/bash
# Lab 3, Part 5 -- summary of an access log.
# Usage: ./report.sh LOGFILE
# Exit codes: 0 = report printed, 1 = missing/unreadable file.

if [ "$#" -ne 1 ]; then
    echo "usage: $(basename "$0") LOGFILE" >&2
    exit 1
fi

file=$1
if [ ! -f "$file" ] || [ ! -r "$file" ]; then
    echo "$(basename "$0"): cannot read '$file'" >&2
    exit 1
fi

total=$(wc -l < "$file")
failed=$(awk '$4 == "FAIL"' "$file" | wc -l)

echo "Total requests : $total"
echo "Failed requests: $failed"
echo "Failures per user:"
awk '{ seen[$3] = 1 } $4 == "FAIL" { bad[$3]++ }
     END { for (u in seen) printf "  %-8s %3d\n", u, bad[u] }' "$file" | sort
