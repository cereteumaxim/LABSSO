# LABSSO: Operating Systems Laboratory Works

| Folder | Topic | Code |
|--------|-------|------|
| [`lab1`](lab1) | The OS as a resource manager (Linux) | `commands.sh` |
| [`lab2`](lab2) | Getting started with xv6 | `sleep.c`, `Makefile` |
| [`lab3`](lab3) | Shell, pipes and text filters | `gen_log.sh`, `oneliners.sh`, `report.sh` |
| [`lab4`](lab4) | The xv6 shell from the outside | `args_linux.c`, `args.c`, `Makefile` |
| [`lab5`](lab5) | The file system with your own hands | `commands.sh` |
| [`lab6`](lab6) | Inside the xv6 file system | `mystat.c`, `find.c`, `Makefile` |

Each folder contains the code and the lab report (`.docx`).

The xv6 programs (`sleep.c`, `args.c`, `mystat.c`, `find.c`) go in `xv6-riscv/user/`. The
`Makefile` in labs 2, 4 and 6 is the full xv6-riscv Makefile with those programs added to
`UPROGS`: copy it over `xv6-riscv/Makefile` and run `make qemu`.

The branches `lab1-2`, `lab3-4` and `lab5-6` hold the original report uploads.
