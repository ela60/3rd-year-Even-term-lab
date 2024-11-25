#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;    // Mutex for synchronization
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;       // Condition variable for signaling

int shared_data = 0;                                  // Shared data
int data_ready = 0;                                   // Flag to indicate data is ready

void* producer(void* arg) {
    // Lock the mutex
    pthread_mutex_lock(&mutex);
    
    // Produce data
    shared_data = 42;
    printf("Producer: produced data %d\n", shared_data);
    
    // Signal the consumer that data is ready
    data_ready = 1;
    pthread_cond_signal(&cond);
    
    // Unlock the mutex
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void* consumer(void* arg) {
    // Lock the mutex
    pthread_mutex_lock(&mutex);
    
    // Wait until data is ready
    while (!data_ready) {
        pthread_cond_wait(&cond, &mutex);
    }
    
    // Consume data
    printf("Consumer: consumed data %d\n", shared_data);
    
    // Unlock the mutex
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    // Create the producer thread
    if (pthread_create(&producer_thread, NULL, producer, NULL) != 0) {
        perror("Failed to create producer thread");
        exit(EXIT_FAILURE);
    }
    
    // Create the consumer thread
    if (pthread_create(&consumer_thread, NULL, consumer, NULL) != 0) {
        perror("Failed to create consumer thread");
        exit(EXIT_FAILURE);
    }
    
    // Wait for the producer thread to finish
    if (pthread_join(producer_thread, NULL) != 0) {
        perror("Failed to join producer thread");
        exit(EXIT_FAILURE);
    }
    
    // Wait for the consumer thread to finish
    if (pthread_join(consumer_thread, NULL) != 0) {
        perror("Failed to join consumer thread");
        exit(EXIT_FAILURE);
    }
    
    // Destroy the mutex and condition variable
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    
    return 0;
}