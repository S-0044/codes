#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_ITEMS 1000  
int *buffer;  
int bufferSize;
int in = 0;  
int out = 0; 

sem_t empty; 
sem_t full;  
pthread_mutex_t mutex;  

void *producer(void *param) {
    int item;
    int id = *(int *)param;
    for(int i = 0; i < MAX_ITEMS; i++) {
        item = rand() % 100;

        sem_wait(&empty);  
        pthread_mutex_lock(&mutex);  
        buffer[in] = item;
        printf("Producer %d: Insert Item %d at %d\n", id, item, in);
        in = (in + 1) % bufferSize;

        pthread_mutex_unlock(&mutex);  
        sem_post(&full);  

        sleep(1);  
    }
    pthread_exit(0);
}

void *consumer(void *param) {
    int item;
    int id = *(int *)param;
    for(int i = 0; i < MAX_ITEMS; i++) {

        sem_wait(&full);  
        pthread_mutex_lock(&mutex);  

        item = buffer[out];
        printf("Consumer %d: Remove Item %d from %d\n", id, item, out);
        out = (out + 1) % bufferSize;

        pthread_mutex_unlock(&mutex);  
        sem_post(&empty);  // Signal that there is an empty slot

        sleep(1);  // Sleep to simulate time taken to consume
    }
    pthread_exit(0);
}

int main() {
    int numProducers, numConsumers;

    
    printf("Enter the size of the buffer: ");
    scanf("%d", &bufferSize);
    buffer = (int *)malloc(bufferSize * sizeof(int));

    printf("Enter the number of producers: ");
    scanf("%d", &numProducers);

    printf("Enter the number of consumers: ");
    scanf("%d", &numConsumers);

    // Initialize semaphores and mutex
    sem_init(&empty, 0, bufferSize);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t producers[numProducers], consumers[numConsumers];
    int producerIds[numProducers], consumerIds[numConsumers];

    // Create producer threads
    for (int i = 0; i < numProducers; i++) {
        producerIds[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producerIds[i]);
    }

    // Create consumer threads
    for (int i = 0; i < numConsumers; i++) {
        consumerIds[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumerIds[i]);
    }

    // Join producer threads
    for (int i = 0; i < numProducers; i++) {
        pthread_join(producers[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < numConsumers; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    free(buffer);

    return 0;
}