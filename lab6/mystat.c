// mystat.c -- print the inode information that stat() returns
// for every path given on the command line.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

static const char *
kind(short type)
{
  switch(type){
  case T_DIR:    return "directory";
  case T_FILE:   return "file";
  case T_DEVICE: return "device";
  default:       return "unknown";
  }
}

int
main(int argc, char **argv)
{
  struct stat st;
  int i, failed = 0;

  if(argc < 2){
    fprintf(2, "Usage: mystat PATH...\n");
    exit(1);
  }

  for(i = 1; i < argc; i++){
    if(stat(argv[i], &st) < 0){
      fprintf(2, "mystat: %s: no such file\n", argv[i]);
      failed = 1;
      continue;
    }
    printf("%s: type=%s inode=%d links=%d size=%d\n",
           argv[i], kind(st.type), st.ino, st.nlink, (int)st.size);
  }
  exit(failed);
}
