/* pipeline3.c -- the shell command   ls /usr/bin | grep x | wc -l
 * built by hand: two pipes, three children.
 *
 *   ls  --a-->  grep x  --b-->  wc -l
 *
 * Each child moves its pipe ends onto 0/1 with dup2 and then closes all four
 * original descriptors; the parent closes them too, otherwise grep and wc
 * would never see end-of-file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

static int a[2], b[2];

static void close_all(void)
{
    close(a[0]); close(a[1]);
    close(b[0]); close(b[1]);
}

/* start one stage: `in`/`out` are the descriptors that become 0 and 1
 * (-1 = keep the terminal) */
static pid_t stage(int in, int out, char *const argv[])
{
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) {
        if (in >= 0)  dup2(in, 0);
        if (out >= 0) dup2(out, 1);
        close_all();
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(127);
    }
    return pid;
}

int main(void)
{
    char *ls[]   = { "ls", "/usr/bin", NULL };
    char *grep[] = { "grep", "x", NULL };
    char *wc[]   = { "wc", "-l", NULL };

    if (pipe(a) < 0 || pipe(b) < 0) { perror("pipe"); return 1; }

    stage(-1,   a[1], ls);
    stage(a[0], b[1], grep);
    stage(b[0], -1,   wc);

    close_all();
    for (int i = 0; i < 3; i++)
        wait(NULL);
    return 0;
}
