#include<stdio.h>
#include<sys/time.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int COUNT = 0;

void count(int x,int y){

    int c;
    for(c = 0;c<500000;c++){
        x += x;
        y += y;
    }
}


double line_count(){

    struct timeval time_before = {0};
    gettimeofday(&time_before,NULL);
    double line_time_before = time_before.tv_sec + time_before.tv_usec/(1000.00*1000.00);
    int i;
    for(i = 0;i < 10;i++){
        count(1,1);
    }
    struct timeval time_now = {0};
    gettimeofday(&time_now,NULL);
    double line_time_now = time_now.tv_sec + time_now.tv_usec/(1000.00*1000.00);
    double line_differ_time = line_time_now - line_time_before;
    return line_differ_time;

}

void count_pthread(){
    int c;
    int x = 1;
    int y = 1;
    for(c = 0;c<500000;c++){
        x += x;
        y += y;
    }
    COUNT--;

}

double threading_count(){

    struct timeval time_before = {0};
    gettimeofday(&time_before,NULL);
    double timed_before = time_before.tv_sec + time_before.tv_usec/(1000.00*1000.00);
    int c;
    int count = 0;
    for(c = 0;c < 10;c++){
        pthread_t t[10];
        if(pthread_create(&t[c],NULL,count_pthread,NULL) == -1){
            printf("fail to creat pthread t %d",c);
            exit(1);
        }else{
            COUNT++;
        }
        void *result;
        if(pthread_join(t[c],&result) == -1){
            printf("fail to recollect t");
            exit(1);
        }
    }

    while(1){
       if(COUNT <= 0){
            break;
       }
    }


    struct timeval time_now = {0};
    gettimeofday(&time_now,NULL);
    double timed_now = time_now.tv_sec + time_now.tv_usec/(1000.00*1000.00);
    double time = timed_now - timed_before;
    //printf("444444444444444444\n");
    return time;

}

double process_count(){

    struct timeval time_before = {0};
    gettimeofday(&time_before,NULL);
    double timed_before = time_before.tv_sec +time_before.tv_usec/(1000.00*1000.00);
    int c;
    for(c = 0;c < 10;c++){
       pid_t pid;
       if(pid<0){
        printf("fail creat process");
       } else if(pid == 0){
           exit(0);
       }
    }
    if(c >= 10){
        struct timeval time_now = {0};
        gettimeofday(&time_now,NULL);
        double timed_now = time_now.tv_sec +time_now.tv_usec/(1000.00*1000.00);
        double time = timed_now - timed_before;
        return time;
        }else{
        double time = 0.0;
        return time;

        }

}

int main(){

    printf("---Single Line CPU:%f\n",line_count());
    printf("---Multi Threading CPU:%f\n",threading_count());
    return 0;


}
