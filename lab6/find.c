// find.c -- walk a directory tree and print every path whose last
// component equals NAME.  Usage: find DIR NAME

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

static char path[512];

// Return a pointer to the last component of p.
static char *
basename(char *p)
{
  char *s = p + strlen(p);
  while(s > p && s[-1] != '/')
    s--;
  return s;
}

// path[] holds the directory to scan; len is its current length.
static void
walk(int len, const char *name)
{
  struct dirent de;
  struct stat st;
  int fd, n;

  if((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "find: cannot open %s\n", path);
    return;
  }

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)
      continue;                         // free slot in the directory
    if(strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
      continue;                         // would loop forever
    if(len + 1 + DIRSIZ + 1 > sizeof(path)){
      fprintf(2, "find: path too long under %s\n", path);
      break;
    }

    // append "/<entry>" (names are not always NUL-terminated)
    path[len] = '/';
    memmove(path + len + 1, de.name, DIRSIZ);
    path[len + 1 + DIRSIZ] = 0;
    n = strlen(path);

    if(stat(path, &st) < 0){
      fprintf(2, "find: cannot stat %s\n", path);
    } else {
      if(strcmp(basename(path), name) == 0)
        printf("%s\n", path);
      if(st.type == T_DIR)
        walk(n, name);
    }
    path[len] = 0;                      // cut back to the parent
  }
  close(fd);
}

int
main(int argc, char **argv)
{
  struct stat st;

  if(argc != 3){
    fprintf(2, "Usage: find DIR NAME\n");
    exit(1);
  }
  if(strlen(argv[1]) >= sizeof(path) - DIRSIZ - 2){
    fprintf(2, "find: start path too long\n");
    exit(1);
  }
  if(stat(argv[1], &st) < 0 || st.type != T_DIR){
    fprintf(2, "find: %s is not a directory\n", argv[1]);
    exit(1);
  }

  strcpy(path, argv[1]);
  walk(strlen(path), argv[2]);
  exit(0);
}
