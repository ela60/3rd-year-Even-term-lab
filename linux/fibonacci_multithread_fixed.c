#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100 

int fib_sequence[MAX_SIZE]; 
int count;                 
double average;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;   

int is_ready = 0; 

void* generate_fibonacci(void* arg) {
    int a = 0, b = 1;
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < count; i++) {
        fib_sequence[i] = a;
        int next = a + b;
        a = b;
        b = next;
    }
    is_ready = 1;                
    pthread_cond_broadcast(&cond); 
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* calculate_average(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!is_ready) { 
        pthread_cond_wait(&cond, &mutex);
    }
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += fib_sequence[i];
    }
    average = (count > 0) ? (double)sum / count : 0;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* display_sequence(void* arg) {
    pthread_mutex_lock(&mutex);
    while (!is_ready) { 
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Fibonacci sequence (n = %d): ", count);
    for (int i = 0; i < count; i++) {
        printf("%d ", fib_sequence[i]);
    }
    printf("\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    printf("Enter the number of Fibonacci numbers to generate: ");
    if (scanf("%d", &count) != 1 || count <= 0 || count > MAX_SIZE) {
        printf("Invalid input. Please enter a positive integer less than or equal to %d.\n", MAX_SIZE);
        return 1;
    }

    pthread_t fib_thread, avg_thread, disp_thread;

   
    pthread_create(&fib_thread, NULL, generate_fibonacci, NULL);
    pthread_create(&avg_thread, NULL, calculate_average, NULL);
    pthread_create(&disp_thread, NULL, display_sequence, NULL);

   
    pthread_join(fib_thread, NULL);
    pthread_join(avg_thread, NULL);
    pthread_join(disp_thread, NULL);

   
    printf("Average of Fibonacci series: %.2f\n", average);

    return 0;
}
