#!/bin/bash
# Lab 5 - The File System with Your Own Hands
mkdir -p ~/os-lab5 && cd ~/os-lab5

# Part 1: The tree and the file types
ls /
ls -ld /etc /etc/passwd /bin /dev/null /tmp
ls -l /dev | head -n 15
file /usr/bin/ls /etc/passwd /bin
du -sh /var/log 2>/dev/null; du -sh /usr 2>/dev/null

# Part 2: Inodes and links
echo hello > notes.txt
stat notes.txt
ln notes.txt hard.txt
ls -li notes.txt hard.txt
rm notes.txt
cat hard.txt; ls -li hard.txt
ln -s hard.txt soft.txt
ls -li hard.txt soft.txt
cat soft.txt
rm hard.txt
cat soft.txt; ls -l soft.txt
mkdir d; ls -ld d
mkdir d/x d/y; ls -ld d
echo x > one.txt; ls -l one.txt; du -h one.txt
truncate -s 1G big.img; ls -lh big.img; du -h big.img
rm big.img

# Part 3: Permissions
echo secret > s.txt
chmod 600 s.txt; ls -l s.txt
chmod 000 s.txt; cat s.txt
chmod u+r s.txt; cat s.txt
umask; touch new.txt; mkdir newdir; ls -ld new.txt newdir
mkdir box; echo hi > box/f
chmod u=r,go= box; ls box; cat box/f
chmod u=x,go= box; ls box; cat box/f
chmod 755 box
ls -l /usr/bin/passwd; ls -ld /tmp
cat /etc/shadow
ls -l /etc/shadow

# Part 4: Disks and the kernel as files
lsblk
df -h
mount | grep " / "
grep -c processor /proc/cpuinfo
head -3 /proc/meminfo
head -5 /proc/self/status
ls -l /proc/self/fd
