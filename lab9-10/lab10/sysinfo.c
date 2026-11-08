// sysinfo: show free memory and the number of processes, then change both
// on purpose and show them again.
#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

#define PAGE 4096

static struct sysinfo
show(char *when)
{
  struct sysinfo si;

  if (sysinfo(&si) < 0) {
    fprintf(2, "sysinfo: failed\n");
    exit(1);
  }
  printf("%s free %ld bytes (%ld pages), %ld processes\n",
         when, si.freemem, si.freemem / PAGE, si.nproc);
  return si;
}

int
main(void)
{
  struct sysinfo a, b;
  int pid, fd[2];
  char c;

  a = show("at start:            ");

  // 1. grow the heap by 10 pages: free memory must go down
  if (sbrk(10 * PAGE) == SBRK_ERROR) {
    fprintf(2, "sysinfo: sbrk failed\n");
    exit(1);
  }
  memset(sbrk(0) - 10 * PAGE, 1, 10 * PAGE); // touch the pages
  b = show("after sbrk(10 pages):");
  printf("  memory used: %ld pages\n", (a.freemem - b.freemem) / PAGE);

  // 2. a child that waits on a pipe: one more process
  pipe(fd);
  pid = fork();
  if (pid == 0) {
    close(fd[1]);
    read(fd[0], &c, 1); // blocks until the parent closes its end
    exit(0);
  }
  close(fd[0]);
  show("with a child alive:  ");
  close(fd[1]);
  wait(0);
  show("after wait:          ");

  // 3. a bad pointer must be refused, not crash the kernel
  if (sysinfo((struct sysinfo *)0xffffffffff) < 0)
    printf("bad pointer: sysinfo returned -1\n");
  exit(0);
}
