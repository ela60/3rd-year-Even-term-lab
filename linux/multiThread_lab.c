#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

// Global variable shared between threads
int global_counter = 0;

// Mutex to protect the global variable
pthread_mutex_t mutex;

// Function for threads without mutex (causing inconsistency)
void *increment_without_mutex(void *arg) {
    for (int i = 0; i < 100000; i++) {
        global_counter++; // Critical section
    }
    return NULL;
}

// Function for threads with mutex (solving inconsistency)
void *increment_with_mutex(void *arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex); // Lock mutex before accessing critical section
        global_counter++;          // Critical section
        pthread_mutex_unlock(&mutex); // Unlock mutex after accessing critical section
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Demonstrate inconsistency
    global_counter = 0; // Reset global counter
    printf("Demonstrating data inconsistency:\n");

    pthread_create(&thread1, NULL, increment_without_mutex, NULL);
    pthread_create(&thread2, NULL, increment_without_mutex, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of global_counter (without mutex): %d\n", global_counter);

    // Demonstrate consistency with mutex
    global_counter = 0; // Reset global counter
    pthread_mutex_init(&mutex, NULL); // Initialize mutex

    printf("\nSolving inconsistency with mutex:\n");

    pthread_create(&thread1, NULL, increment_with_mutex, NULL);
    pthread_create(&thread2, NULL, increment_with_mutex, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of global_counter (with mutex): %d\n", global_counter);

    pthread_mutex_destroy(&mutex); // Destroy mutex

    return 0;
}
