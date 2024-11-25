#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<iostream>
#include <string.h>
#include<bits/stdc++.h>
#include<string>
using namespace std;

int main(){
    char *pipePath = "miju";
    if(access(pipePath,F_OK)==0){
        cout<<"Pipe is alrady creaded"<<endl;
    }
    else{
        int pipe_flag = mkfifo(pipePath,0666);
        if(pipe_flag<0){
            cout<<"Pipe is not created."<<endl;
            return 0;
        }else{
            cout<<"Pipe is creaded"<<endl;
        }
    }
    int pipe_id = open(pipePath,O_RDWR);
    if(pipe_id==-1){
        cout<<"Couldn't find this pipe"<<endl;
        return 1;
    }
    int send = 1;
    while(true){
        if(send){
            char msg[100];
            int msg_id = read(STDIN_FILENO, msg, 100);
            int msg_id2 = read(STDIN_FILENO, msg, 100);
            if(msg_id==-1){
                cout<<"Could not read the message"<<endl;
                return 1;
            }

            msg[msg_id] = '\0';
            write(pipe_id, msg, strlen(msg));
            if(msg[0]=='b'&&msg[1]=='y'&&msg[2]=='e'){
                return 0;
            }
        }
        else{
            char msg[100];
            int msg_id = read(pipe_id, msg, 100);
            if(msg_id==-1){
                cout<<"Could not read the message"<<endl;
                return 1;
            }

            msg[msg_id] = '\0';
            write(STDOUT_FILENO, msg, strlen(msg));
            if(msg[0]=='b'&&msg[1]=='y'&&msg[2]=='e'){
                return 0;
            }
        }
        send ^= 1;
    }
}