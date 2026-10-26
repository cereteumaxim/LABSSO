// pingpong.c -- one byte goes parent -> child through p2c and comes back
// child -> parent through c2p.  Each read() blocks until the other side
// has written, so the output order is always ping, then pong.

#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int p2c[2], c2p[2];     // parent-to-child, child-to-parent
  char b;

  if(pipe(p2c) < 0 || pipe(c2p) < 0){
    fprintf(2, "pingpong: pipe failed\n");
    exit(1);
  }
  if(fork() == 0){
    close(p2c[1]); close(c2p[0]);       // the ends the child does not use
    if(read(p2c[0], &b, 1) != 1){       // blocks until the parent writes
      fprintf(2, "pingpong: child read failed\n");
      exit(1);
    }
    printf("%d: received ping\n", getpid());
    write(c2p[1], &b, 1);               // send the same byte back
    exit(0);
  }
  close(p2c[0]); close(c2p[1]);         // the ends the parent does not use
  b = 'x';
  write(p2c[1], &b, 1);
  if(read(c2p[0], &b, 1) != 1){         // blocks until the child answers
    fprintf(2, "pingpong: parent read failed\n");
    exit(1);
  }
  printf("%d: received pong\n", getpid());
  wait(0);
  exit(0);
}
