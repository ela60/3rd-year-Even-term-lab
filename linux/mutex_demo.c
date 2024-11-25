#include <stdio.h>
#include <pthread.h>

int global_variable = 0;  // Shared global variable
pthread_mutex_t lock;     // Mutex for synchronization

// Function without mutex: causes inconsistency
void* increment_without_mutex(void* arg) {
    for (int i = 0; i < 1000000; ++i) {
        global_variable++;  // Increment without synchronization
    }
    return NULL;
}

// Function with mutex: solves inconsistency
void* increment_with_mutex(void* arg) {
    for (int i = 0; i < 1000000; ++i) {
        pthread_mutex_lock(&lock);  // Acquire lock
        global_variable++;         // Increment safely
        pthread_mutex_unlock(&lock);  // Release lock
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Case 1: Without Mutex
    global_variable = 0;
    printf("Case 1: Without Mutex\n");
    pthread_create(&thread1, NULL, increment_without_mutex, NULL);
    pthread_create(&thread2, NULL, increment_without_mutex, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final value (without mutex): %d\n", global_variable);

    // Case 2: With Mutex
    pthread_mutex_init(&lock, NULL);  // Initialize mutex
    global_variable = 0;
    printf("\nCase 2: With Mutex\n");
    pthread_create(&thread1, NULL, increment_with_mutex, NULL);
    pthread_create(&thread2, NULL, increment_with_mutex, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("Final value (with mutex): %d\n", global_variable);

    pthread_mutex_destroy(&lock);  // Destroy mutex
    return 0;
}
