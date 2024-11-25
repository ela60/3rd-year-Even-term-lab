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
    // Generate unique key and access shared memory segment
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, sizeof(struct Message), 0666 | IPC_CREAT);
    struct Message *msg = (struct Message *)shmat(shmid, NULL, 0);

    while (1) {
        if (msg->turn == 2) {
            // Receiving message
            printf("Process 2 received: %s", msg->text);
            if (strncmp(msg->text, "Goodbye", 7) == 0) {
                break;
            }

            // Sending message
            printf("Process 2: ");
            fgets(msg->text, 1024, stdin);
            if (strncmp(msg->text, "Goodbye", 7) == 0) {
                msg->turn = 1; // Pass turn to Process 1
                break;
            }
            msg->turn = 1; // Pass turn to Process 1
        } else {
            // Waiting for Process 1
            sleep(1);
        }
    }

    // Detach and clean up shared memory
    shmdt(msg);
    shmctl(shmid, IPC_RMID, NULL); // Cleanup shared memory
    return 0;
}
