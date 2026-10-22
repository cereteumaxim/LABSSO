#!/bin/bash
log=$1
if [ -z "$log" ] || [ ! -f "$log" ]; then
  echo "Usage: $0 <logfile>" >&2
  exit 1
fi

total=$(wc -l < "$log")
fails=$(grep -c FAIL "$log")
echo "$total requests, $fails failed"

for u in user{0..6}; do
  cnt=$(grep "$u" "$log" | grep -c "FAIL")
  echo "$u: $cnt failures"
done
