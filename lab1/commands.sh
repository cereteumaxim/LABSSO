#!/bin/bash
# Lab 1 -- the operating system as a resource manager.
# Each part looks at one resource the kernel hands out: files, CPU time
# (processes), memory and devices.  Safe to run more than once.

WORK=$HOME/os-lab1
section() { printf '\n===== %s =====\n' "$*"; }

section "Machine"
echo "user: $(whoami)   host: $(hostname)"
uname -srm
uptime -p

section "Part 1 - files and directories"
rm -rf "$WORK" && mkdir -p "$WORK/demo" && cd "$WORK/demo" || exit 1
echo "hello operating systems" > note.txt
cp note.txt copy.txt
mv copy.txt renamed.txt
ls -l
chmod 600 note.txt
ls -l note.txt
ls -ld /etc /dev /home /usr

section "Part 2 - processes"
ps -o pid,ppid,user,comm -p 1
ls -l /sbin/init
echo "processes right now: $(ps -e --no-headers | wc -l)"
sleep 300 &
SPID=$!
grep -E '^(Name|State|PPid)' /proc/$SPID/status
top -b -n 1 | head -n 5

section "Part 3 - memory"
free -h
swapon --show
grep -E '^Vm(Size|RSS)' /proc/$SPID/status
kill $SPID

section "Part 4 - devices and storage"
ls -l /dev | head -n 6
ls -l /dev/null /dev/tty /dev/sda 2>/dev/null
lsblk -o NAME,SIZE,TYPE,MOUNTPOINTS
findmnt -n -o SOURCE,FSTYPE /
