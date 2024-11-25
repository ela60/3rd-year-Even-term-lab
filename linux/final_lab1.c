#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Check if the number of arguments is three
    if (argc != 4) {
        fprintf(stderr, "Usage: %s parent_process num1 num2\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Assign variables from command-line arguments
    char *parent_name = argv[1];
    int num1 = atoi(argv[2]);
    int num2 = atoi(argv[3]);
    int result = 0;

    printf("result = %d\n", result);

    // Create the first child process for addition
    pid_t pid_addition = fork();
    if (pid_addition < 0) {
        perror("Failed to fork for addition");
        exit(EXIT_FAILURE);
    }

    if (pid_addition == 0) {
        // Child process: addition
        result = num1 + num2;
        printf("ChildProcess-%d: addition_result = %d\n", getpid(), result);
        exit(EXIT_SUCCESS);
    }

    // Create the second child process for subtraction
    pid_t pid_subtraction = fork();
    if (pid_subtraction < 0) {
        perror("Failed to fork for subtraction");
        exit(EXIT_FAILURE);
    }

    if (pid_subtraction == 0) {
        // Child process: subtraction
        result = num1 - num2;
        printf("ChildProcess-%d: subtraction_result = %d\n", getpid(), result);
        exit(EXIT_SUCCESS);
    }

    // Parent process waits for both children to finish
    int status;
    pid_t finished_pid;

    while ((finished_pid = wait(&status)) > 0) {
        if (WIFEXITED(status)) {
            printf("Child %d successfully finished.\n", finished_pid);
        } else {
            printf("Child %d terminated abnormally.\n", finished_pid);
        }
    }

    return 0;
}
