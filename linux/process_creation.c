#include<stdio.h>
#include<unistd.h>

int main(){
    pid_t pid = fork();
    if(pid==0){
        printf("Child process pid : %d and its parent pid is %d\n",getpid(),getppid());

    }else{
        printf("Parent process pid : %d\n",getpid());
    }
    return 0;
}