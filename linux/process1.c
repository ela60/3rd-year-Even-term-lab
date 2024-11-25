#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct Message {
    int turn;           // 1: Process 1's turn, 2: Process 2's turn
    char text[1024];    // Shared message buffer
};

int main() {
    // Generate unique key and create shared memory segment
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(struct Message), 0666 | IPC_CREAT);
    struct Message *msg = (struct Message *)shmat(shmid, NULL, 0);

    msg->turn = 1; // Start with Process 1's turn

    while (1) {
        if (msg->turn == 1) {
            // Sending message
            printf("Process 1: ");
            fgets(msg->text, 1024, stdin);
            if (strncmp(msg->text, "Goodbye", 7) == 0) {
                msg->turn = 2; // Pass turn to Process 2
                break;
            }
            msg->turn = 2; // Pass turn to Process 2
        } else {
            // Waiting for Process 2
            sleep(1);
        }
    }

    // Detach and clean up shared memory
    shmdt(msg);
    return 0;
}
