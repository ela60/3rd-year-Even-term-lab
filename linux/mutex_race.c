#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

pthread_mutex_t m;

int x = 1;
int f1(){
    pthread_mutex_lock(&m);
    for (int i = 0; i < 100000; i++)
        x++;
    pthread_mutex_unlock(&m);    
}
int f2(){
    pthread_mutex_lock(&m);
    for(int i=0; i<100000; i++)
        x--;
    pthread_mutex_unlock(&m); 
}

int main(){
    pthread_t t1,t2;

    pthread_mutex_init(&m, NULL);

    pthread_create(&t1, NULL, (void *)f1, NULL);
    pthread_create(&t2,NULL,(void*)f2,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("Result : %d\n",x);
}