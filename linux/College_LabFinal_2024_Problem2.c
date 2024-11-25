#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc !=5) {
        printf("Too few arguments\n");
        return 1;
    }

   
    char *parent_name = argv[1];
    char *child1_name = argv[2];
    char *child2_name = argv[3];
    char *child3_name = argv[4];

    printf("Parent Process: %s\n", parent_name);

    pid_t pids[3]; 
    char *child_names[] = {child1_name, child2_name, child3_name};


    // in the parrent process
    for (int i = 0; i < 3; i++) {
        pids[i] = fork(); 
        if (pids[i] < 0) {
            perror("Fork failed");
            return 1;
        } else if (pids[i] == 0) {
           
            printf("PID-%d (%s) started.\n", getpid(), child_names[i]);
            exit(0); 
        }
    }

    // In the parent process
    for (int i = 0; i < 3; i++) {
        int status;
        waitpid(pids[i], &status, 0);
        if (WIFEXITED(status)) {
            printf("Child %d (%s) successfully finished.\n", pids[i], child_names[i]);
        }
    }

    return 0;
}
