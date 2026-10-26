// args.c (xv6) -- show exactly what exec() delivered to the program.
// The xv6 shell does no globbing and no quote removal, so `args *.c "x y"`
// arrives here unchanged.

#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  int i;

  printf("argc = %d\n", argc);
  i = 0;
  while(i < argc){
    printf("argv[%d] = [%s]\n", i, argv[i]);
    i++;
  }
  exit(0);
}
