#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int counter = 0;
sem_t mutex;

void* increment(void* arg) {
    int i;
    for (i = 0; i < 100000; i++) {
        sem_wait(&mutex);   // TODO 1: enter critical section using semaphore
        counter++;
        sem_post(&mutex);   // TODO 2: leave critical section using semaphore
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    sem_init(&mutex, 0, 1);  // TODO 3: initialize binary semaphore mutex to 1

    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Final counter value: %d\n", counter);

    sem_destroy(&mutex);  // TODO 4: destroy semaphore

    return 0;
}
