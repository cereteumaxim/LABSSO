/* condvar.c - Lab 12, Part 2: the order.c problem of Lab 11, with a mutex and a condition variable.
 * Build: gcc -Wall -pthread -o condvar condvar.c
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

char message[32];
int ready = 0;                          /* the state: 1 when the message is written */
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t changed = PTHREAD_COND_INITIALIZER;

void *writer(void *arg) {
    (void)arg;
    sleep(1);
    pthread_mutex_lock(&lock);
    strcpy(message, "hello");
    ready = 1;
    printf("A: message written\n");
    pthread_cond_signal(&changed);      /* wake up one thread sleeping on "changed" */
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *reader(void *arg) {
    (void)arg;
    pthread_mutex_lock(&lock);
    while (!ready) {                    /* while, not if: check again after every wake-up */
        printf("B: not ready, I sleep\n");
        pthread_cond_wait(&changed, &lock);   /* unlock, sleep, lock again */
    }
    printf("B: I read \"%s\"\n", message);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    pthread_t a, b;
    pthread_create(&b, NULL, reader, NULL);
    pthread_create(&a, NULL, writer, NULL);
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    return 0;
}
