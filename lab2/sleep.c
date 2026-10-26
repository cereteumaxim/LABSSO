// sleep.c -- suspend the shell for a given number of timer ticks.
// In the current xv6 the system call is called pause(); one tick
// is about 1/10 of a second in QEMU.

#include "kernel/types.h"
#include "user/user.h"

static int
is_number(const char *s)
{
  if(*s == 0)
    return 0;
  for(; *s; s++)
    if(*s < '0' || *s > '9')
      return 0;
  return 1;
}

int
main(int argc, char **argv)
{
  if(argc != 2 || !is_number(argv[1])){
    fprintf(2, "Usage: sleep TICKS (a non-negative integer)\n");
    exit(1);
  }

  pause(atoi(argv[1]));
  exit(0);
}
