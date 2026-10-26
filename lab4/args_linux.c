/* args_linux.c -- Linux twin of args.c.
 * Prints argc and every argv[i] between brackets, so we can see what bash
 * did to the command line (globbing, quote removal) before calling execve().
 */
#include <stdio.h>

int main(int argc, char **argv)
{
    char **p;
    int i = 0;

    printf("argc = %d\n", argc);
    for (p = argv; *p != NULL; p++, i++)
        printf("argv[%d] = [%s]\n", i, *p);
    return 0;
}
