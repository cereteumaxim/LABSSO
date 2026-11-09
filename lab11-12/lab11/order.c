/* order.c - Lab 11, Part 3: thread B may read the message only after thread A wrote it.
 * The semaphore starts at 0, so sem_wait in B blocks until A calls sem_post.
 * Build: gcc -Wall -pthread -o order order.c
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

char message[32];
sem_t ready;                            /* 0 at the start: no message yet */

void *writer(void *arg) {
    (void)arg;
    sleep(1);                           /* the "work" before the message is ready */
    strcpy(message, "hello");
    printf("A: message written\n");
    sem_post(&ready);                   /* 0 -> 1: B can go on */
    return NULL;
}

void *reader(void *arg) {
    (void)arg;
    printf("B: waiting for the message...\n");
    sem_wait(&ready);                   /* sleeps while the value is 0 */
    printf("B: I read \"%s\"\n", message);
    return NULL;
}

int main(void) {
    sem_init(&ready, 0, 0);
    pthread_t a, b;
    pthread_create(&b, NULL, reader, NULL);     /* the reader is started first on purpose */
    pthread_create(&a, NULL, writer, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    sem_destroy(&ready);
    return 0;
}
