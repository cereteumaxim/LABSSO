# LABSSO: Operating Systems Laboratory Works

| Folder | Topic | Code |
|--------|-------|------|
| [`lab1`](lab1) | The OS as a resource manager (Linux) | `commands.sh` |
| [`lab2`](lab2) | Getting started with xv6 | `sleep.c`, `Makefile` |
| [`lab3`](lab3) | Shell, pipes and text filters | `gen_log.sh`, `oneliners.sh`, `report.sh` |
| [`lab4`](lab4) | The xv6 shell from the outside | `args_linux.c`, `args.c`, `Makefile` |
| [`lab5`](lab5) | The file system with your own hands | `commands.sh` |
| [`lab6`](lab6) | Inside the xv6 file system | `mystat.c`, `find.c`, `Makefile` |
| [`lab7-8`](https://github.com/cereteumaxim/LABSSO/tree/lab7-8/lab7-8) | Processes, redirection and pipes (Linux and xv6) | `run.c`, `zombie.c`, `redirect.c`, `pipeline.c`, `pingpong.c`, `primes.c`, `Makefile` |
| [`lab9-10`](https://github.com/cereteumaxim/LABSSO/tree/lab9-10/lab9-10) | System calls: strace on Linux, a new `trace` system call in xv6 | `syscalls.c`, `trace.c`, `trace.patch`, `sysinfo.c`, `sysinfo.h`, `sysinfo.patch`, `Makefile` |
| [`lab11-12`](https://github.com/cereteumaxim/LABSSO/tree/lab11-12/lab11-12) | Race conditions, semaphores, producer/consumer, readers/writers and deadlock (Linux) | `race.c`, `mutex.c`, `sem.c`, `order.c`, `parking.c`, `atomic.c`, `prodcons.c`, `condvar.c`, `readers.c`, `deadlock.c` |

Each folder contains the code and the lab report (`.docx`).

The xv6 programs (`sleep.c`, `args.c`, `mystat.c`, `find.c`) go in `xv6-riscv/user/`. The
`Makefile` in labs 2, 4 and 6 is the full xv6-riscv Makefile with those programs added to
`UPROGS`: copy it over `xv6-riscv/Makefile` and run `make qemu`.

Labs 7 and 8 are on the branch [`lab7-8`](https://github.com/cereteumaxim/LABSSO/tree/lab7-8), in the folder `lab7-8/`, with one combined report (`Lab7-8_CereteuMaxim_FAF-243.docx`).

Labs 9 and 10 are on the branch [`lab9-10`](https://github.com/cereteumaxim/LABSSO/tree/lab9-10), in the folder `lab9-10/`,
with one report per lab (`lab9/Lab9_CereteuMaxim_FAF-243.docx`, `lab10/Lab10_CereteuMaxim_FAF-243.docx`).
Lab 10 changes the xv6 kernel: `trace.patch` (the `trace` system call) and `sysinfo.patch` (the optional
`sysinfo` call) apply in this order with `git apply` inside `xv6-riscv/`; `Makefile` is the resulting xv6 Makefile.

Labs 11 and 12 are on the branch [`lab11-12`](https://github.com/cereteumaxim/LABSSO/tree/lab11-12), in the folder `lab11-12/`,
with one report per lab (`lab11/Lab11_CereteuMaxim_FAF-243.docx`, `lab12/Lab12_CereteuMaxim_FAF-243.docx`).
Build any program with `gcc -Wall -pthread -o NAME NAME.c` (no `-O2`).

The branches `lab1-2`, `lab3-4` and `lab5-6` hold the original report uploads.
