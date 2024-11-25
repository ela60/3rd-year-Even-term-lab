#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(){
    int fd[2],n;
    pipe(fd);
    char b[1024];
    pid_t p = fork();
    if(p>0){
        printf("Passing values to the child: \n");
        write(fd[1],"Hello Likha\n",12);
    }
    else{
        printf("Receiving the values from paren: \n");
        n = read(fd[0],b,1024);
        write(1,b,n);
    }
}