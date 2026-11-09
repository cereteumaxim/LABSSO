/* race.c - Lab 11, Part 1: two threads increment one shared counter with no protection.
 * Build: gcc -Wall -pthread -o race race.c   (no -O2, so counter++ really goes to memory)
 * Run:   ./race   (a few times: the result changes from run to run)
 */
#include <stdio.h>
#include <pthread.h>

#define N 1000000

long counter = 0;                       /* one variable, two threads */

void *add(void *arg) {
    (void)arg;
    for (int i = 0; i < N; i++)
        counter++;                      /* load, add 1, store: not one step */
    return NULL;
}

int main(void) {
    pthread_t a, b;
    pthread_create(&a, NULL, add, NULL);
    pthread_create(&b, NULL, add, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    printf("counter = %ld (expected %d)\n", counter, 2 * N);
    return 0;
}
