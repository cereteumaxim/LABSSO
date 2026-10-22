#!/bin/bash
# Lab 1 - The OS as a resource manager (Linux terminal)

# System info
whoami
uname -a
uptime

# Part 1: Files and directories
mkdir -p ~/os-lab1 && cd ~/os-lab1
mkdir demo && cd demo
echo "hello operating systems" > note.txt
cp note.txt copy.txt
mv copy.txt renamed.txt
ls -l
chmod 600 note.txt
ls -l note.txt

# Part 2: Processes
ps aux | head -5
ps aux | wc -l
sleep 300 &
PID=$!
cat /proc/$PID/status | head -3
top -b -n 1 | head -5

# Part 3: Memory
free -h
grep VmRSS /proc/$PID/status
kill $PID

# Part 4: Devices and storage
ls -l /dev | head -4
lsblk
