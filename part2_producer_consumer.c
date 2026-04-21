#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void* producer(void* arg) {
    int item;
    for (item = 1; item <= ITEMS; item++) {
        sem_wait(&empty);   // wait for an empty slot
        sem_wait(&mutex);   // enter critical section

        buffer[in] = item;
        printf("Produced: %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // leave critical section
        sem_post(&full);    // signal that a new item is available
    }
    return NULL;
}

void* consumer(void* arg) {
    int i, item;
    for (i = 1; i <= ITEMS; i++) {
        sem_wait(&full);    // wait for a filled slot
        sem_wait(&mutex);   // enter critical section

        item = buffer[out];
        printf("Consumed: %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);   // leave critical section
        sem_post(&empty);   // signal that a slot is now empty
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);  // buffer starts fully empty
    sem_init(&full, 0, 0);             // buffer starts with 0 filled slots
    sem_init(&mutex, 0, 1);            // binary semaphore for mutual exclusion

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
