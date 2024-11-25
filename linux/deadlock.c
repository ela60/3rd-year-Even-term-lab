#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

int f1();
int f2();
int f3();

pthread_mutex_t r1,r2,r3;

int main(){
    pthread_mutex_init(&r1,NULL);
    pthread_mutex_init(&r2,NULL);
    pthread_mutex_init(&r2,NULL);

    pthread_t t1,t2,t3;
    pthread_create(&t1,NULL,(void*)f1,NULL);
    pthread_create(&t2,NULL,(void*)f2,NULL);
    pthread_create(&t3,NULL,(void*)f3,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
}

int f1(){
    printf("t1 try to aquire r1.\n");
    pthread_mutex_lock(&r1);
    printf("t1 require r1.\n");
    sleep(1);
    printf("t1 try to aquire r2.\n");
    pthread_mutex_lock(&r2);
    printf("t1 require r2.\n");
}

int f2(){
    printf("t2 try to aquire r2.\n");
    pthread_mutex_lock(&r2);
    printf("t2 require r2.\n");
    sleep(1);
    printf("t2 try to aquire r3.\n");
    pthread_mutex_lock(&r3);
    printf("t2 require r3.\n");
}

int f3(){
    printf("t3 try to aquire r3.\n");
    pthread_mutex_lock(&r3);
    printf("t3 require r3.\n");
    sleep(1);
    printf("t3 try to aquire r1.\n");
    pthread_mutex_lock(&r1);
    printf("t2 require r1.\n");
}