#!/bin/bash
log=access.log

echo "=== Q1: Cereri esuate ==="
grep -c FAIL "$log"

echo "=== Q2: Pagini distincte ==="
awk '{print $5}' "$log" | sort -u

echo "=== Q3: Accesari per pagina ==="
awk '{print $5}' "$log" | sort | uniq -c

echo "=== Q4: Utilizatorul cu cele mai multe esecuri ==="
grep FAIL "$log" | awk '{print $3}' | sort | uniq -c | sort -rn | head -1

echo "=== Q5: user3 total si esuate ==="
echo "total: $(grep -c ' user3 ' "$log"), failed: $(grep ' user3 ' "$log" | grep -c FAIL)"

echo "=== Q6: Ultimele 3 cereri esuate (ora si utilizator) ==="
grep FAIL "$log" | tail -3 | awk '{print $2, $3}'

echo "=== Q7: Shell-uri de login din /etc/passwd ==="
cut -d: -f7 /etc/passwd | sort | uniq -c

echo "=== Q8: Diferenta intre ls /etc si ls -l /etc ==="
echo "ls /etc: $(ls /etc | wc -l), ls -l /etc: $(ls -l /etc | wc -l)"
