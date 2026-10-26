#!/bin/bash
# Lab 5 -- the file system with your own hands.
# Every experiment runs in a scratch folder, so the script can be repeated.

WORK=$HOME/os-lab5
section() { printf '\n===== %s =====\n' "$*"; }
rm -rf "$WORK" && mkdir -p "$WORK" && cd "$WORK" || exit 1

section "Part 1 - the tree and the file types"
ls /
ls -ld /etc /etc/passwd /bin /dev/null /tmp
ls -l /dev | grep -E '^[bc]' | head -n 12
file /usr/bin/ls /etc/passwd /bin
du -sh /var/log /usr 2>/dev/null

section "Part 2 - inodes and links"
echo hello > notes.txt
stat notes.txt
ln notes.txt hard.txt                 # second name, same inode
ls -li notes.txt hard.txt
rm notes.txt                          # only the name goes away
cat hard.txt
ls -li hard.txt
ln -s hard.txt soft.txt               # new inode that stores a path
ls -li hard.txt soft.txt
cat soft.txt
rm hard.txt
cat soft.txt                          # now a dangling link
ls -l soft.txt

mkdir d && stat -c '%n links=%h' d
mkdir d/x d/y && stat -c '%n links=%h' d

echo x > one.txt
stat -c '%n size=%s bytes, blocks=%b' one.txt
du -h one.txt
truncate -s 1G big.img                # sparse file
ls -lh big.img
du -h big.img
rm big.img

section "Part 3 - permissions"
echo secret > s.txt
chmod 600 s.txt && ls -l s.txt
chmod 000 s.txt && cat s.txt
chmod u+r s.txt && cat s.txt
umask
touch new.txt && mkdir newdir && ls -ld new.txt newdir

mkdir box && echo hi > box/f
chmod u=r,go= box                     # read but no search
ls box
cat box/f
chmod u=x,go= box                     # search but no read
ls box
cat box/f
chmod 755 box

ls -l /usr/bin/passwd
ls -ld /tmp
cat /etc/shadow
ls -l /etc/shadow

section "Part 4 - disks and the kernel as files"
lsblk
df -h /
findmnt -n /
grep -c '^processor' /proc/cpuinfo
head -n 3 /proc/meminfo
head -n 5 /proc/self/status
ls -l /proc/self/fd
