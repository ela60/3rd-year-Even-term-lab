#include<unistd.h>
#include<stdio.h>
int main(){
    char b[30];
    int n = read(0, b, 30);
    write(1,b,n);

}