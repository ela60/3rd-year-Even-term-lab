#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<unistd.h>
#include<errno.h>


void set_cpu(pid_t pid, int cpu){
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu, &mask);
    if(sched_setaffinity(pid,sizeof(mask),&mask)==-1)
        printf("cant set affinity\n");
    else
        printf("set affinity\n");
}

void get_cpu(pid_t pid){
    cpu_set_t mask;
    CPU_ZERO(&mask);
    if(sched_getaffinity(pid,sizeof(mask),&mask)==-1){
        perror("sched_getaffinity failed");
        exit(EXIT_FAILURE);
    }else{
        printf("Process %d  affinity : ",pid);
        for(int i=0; i<CPU_SETSIZE; i++){
            if(CPU_ISSET(i,&mask)){
                printf("CPU %d ",i);
            }
        }
        printf("\n");
    }
}

int main(){
    pid_t pid = fork();
    printf("Initial cpu affinity: \n");
    get_cpu(pid);
    set_cpu(pid,2);

    printf("cpu affinity after setting: \n");
    get_cpu(pid);
    return 0;
}