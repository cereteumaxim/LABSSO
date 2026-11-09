// semtry.c: shows both answers of sem_trydown (optional part of Lab 13).
#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  sem_init(4, 1);
  printf("sem 4 = 1, sem_trydown -> %d\n", sem_trydown(4));   // takes the unit: 0
  printf("sem 4 = 0, sem_trydown -> %d\n", sem_trydown(4));   // nothing left: -1 at once
  sem_up(4);
  printf("after sem_up, sem_trydown -> %d\n", sem_trydown(4)); // 0 again
  printf("bad id 9, sem_trydown -> %d\n", sem_trydown(9));    // -1
  exit(0);
}
