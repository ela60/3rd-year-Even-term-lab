#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipe1[2]; // Pipe for communication from Parent to Child
    int pipe2[2]; // Pipe for communication from Child to Parent
    pid_t pid;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) { 
        // Child Process
        char buffer[BUFFER_SIZE];

        while (1) {
            // Read message from Parent
            read(pipe1[0], buffer, BUFFER_SIZE);
            printf("Child received: %s\n", buffer);

            if (strcmp(buffer, "GoodBye") == 0) {
                printf("Child exiting...\n");
                break;
            }

            // Send response to Parent
            char response[BUFFER_SIZE];
            sprintf(response, "Message received: %s", buffer);
            write(pipe2[1], response, strlen(response) + 1);
        }

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
    } else { 
        // Parent Process
        char input[BUFFER_SIZE];
        char buffer[BUFFER_SIZE];

        while (1) {
            // Send message to Child
            printf("Parent: Enter message for Child: ");
            fgets(input, BUFFER_SIZE, stdin);
            input[strcspn(input, "\n")] = '\0'; // Remove newline
            write(pipe1[1], input, strlen(input) + 1);

            if (strcmp(input, "GoodBye") == 0) {
                printf("Parent exiting...\n");
                break;
            }

            // Read response from Child
            read(pipe2[0], buffer, BUFFER_SIZE);
            printf("Parent received: %s\n", buffer);
        }

        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
    }

    return 0;
}
