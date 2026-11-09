/* sem.c - Lab 11, Part 2.2: the same lock, built from a semaphore that starts at 1.
 * Build: gcc -Wall -pthread -o sem sem.c
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 1000000

long counter = 0;
sem_t s;

void *add(void *arg) {
    (void)arg;
    for (int i = 0; i < N; i++) {
        sem_wait(&s);                   /* 1 -> 0 and go in; if it is 0, wait */
        counter++;
        sem_post(&s);                   /* 0 -> 1: the next thread may go in */
    }
    return NULL;
}

int main(void) {
    sem_init(&s, 0, 1);                 /* 0 = shared by the threads of this process, start at 1 */
    pthread_t a, b;
    pthread_create(&a, NULL, add, NULL);
    pthread_create(&b, NULL, add, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    printf("counter = %ld (expected %d)\n", counter, 2 * N);
    sem_destroy(&s);
    return 0;
}
