#!/bin/bash
# Lab 3, Part 4 -- one pipeline per question about access.log.
# Run it from the folder that contains access.log:   bash oneliners.sh
# Log line format:  DATE TIME USER STATUS PAGE

LOG=access.log
[ -r "$LOG" ] || { echo "oneliners.sh: $LOG not found in $(pwd)" >&2; exit 1; }

title() { printf '\n--- %s ---\n' "$*"; }

title "Q1. How many requests failed?"
awk '$4 == "FAIL"' "$LOG" | wc -l

title "Q2. Which distinct pages were requested?"
cut -d' ' -f5 "$LOG" | sort -u

title "Q3. How many hits did each page get?"
cut -d' ' -f5 "$LOG" | sort | uniq -c | sort -k2

title "Q4. Which user has the most failures? (all users tied for first place)"
awk '$4 == "FAIL" {print $3}' "$LOG" | sort | uniq -c | sort -k1,1nr -k2 |
    awk 'NR == 1 {max = $1} $1 == max'

title "Q5. user3: all requests vs failed requests"
awk '$3 == "user3" {all++; if ($4 == "FAIL") bad++}
     END {printf "all=%d failed=%d\n", all, bad}' "$LOG"

title "Q6. Time and user of the last 3 failures"
grep -w FAIL "$LOG" | tail -n 3 | cut -d' ' -f2,3

title "Q7. Login shells in /etc/passwd (count per shell)"
awk -F: '{print $NF}' /etc/passwd | sort | uniq -c | sort -nr

title "Q8. Lines printed by 'ls /etc' and by 'ls -l /etc'"
printf 'ls /etc    -> %s lines\n' "$(ls /etc | wc -l)"
printf 'ls -l /etc -> %s lines\n' "$(ls -l /etc | wc -l)"
