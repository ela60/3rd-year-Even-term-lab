#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
void create_child_process(const char *child_name) {
    pid_t pid = fork();

    if (pid == 0) {
        printf("%s (PID: %d) is created.\n", child_name, getpid());
        sleep(5);
        exit(0);
    }
}
int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);

    printf("Parent process PID: %d\n", getpid());
    for (int i = 2; i < argc; i++) {
        create_child_process(argv[i]);
    }
    for (int i = 2; i < argc; i++) {
        sleep(5);
    }
    return 0;
}