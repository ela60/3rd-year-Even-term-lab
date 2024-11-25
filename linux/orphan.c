#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>

int main(){
    pid_t c = fork();

    if(c==0){
        sleep(20);
        printf("Child Process\n Child PID : %d\n", getpid());
    }
    else{
        // wait(NULL);
        sleep(10);
        printf("Parent process\n Parent PID : %d\n", getpid());
    }
}