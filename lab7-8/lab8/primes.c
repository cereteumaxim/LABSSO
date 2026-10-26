// primes.c -- primes from 2 to 35 with a chain of processes (optional part).
// The first process feeds 2..35 into a pipe.  Every stage reads its first
// number p (always a prime), prints it, and passes on to a new stage only the
// numbers that p does not divide.

#include "kernel/types.h"
#include "user/user.h"

static void stage(int in) __attribute__((noreturn));

static void
stage(int in)
{
  int p, n, fd[2];

  if(read(in, &p, sizeof(p)) != sizeof(p)){   // nothing left: end of the chain
    close(in);
    exit(0);
  }
  printf("prime %d\n", p);

  if(pipe(fd) < 0){
    fprintf(2, "primes: pipe failed\n");
    exit(1);
  }
  if(fork() == 0){
    close(in);                                // the next stage only needs fd[0]
    close(fd[1]);
    stage(fd[0]);
  }
  close(fd[0]);
  while(read(in, &n, sizeof(n)) == sizeof(n))
    if(n % p != 0)
      write(fd[1], &n, sizeof(n));
  close(in);
  close(fd[1]);                               // lets the next stage see EOF
  wait(0);
  exit(0);
}

int
main(void)
{
  int fd[2];

  if(pipe(fd) < 0){
    fprintf(2, "primes: pipe failed\n");
    exit(1);
  }
  if(fork() == 0){
    close(fd[1]);
    stage(fd[0]);
  }
  close(fd[0]);
  for(int i = 2; i <= 35; i++)
    write(fd[1], &i, sizeof(i));
  close(fd[1]);
  wait(0);
  exit(0);
}
