#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <sys/resource.h>

pthread_t threadA;
pthread_attr_t attrA;
struct sched_param paramA;

pthread_t threadB;
pthread_attr_t attrB;
struct sched_param paramB;

pthread_t threadC;
pthread_attr_t attrC;
struct sched_param paramC;

// function which counts from 1 to 2**32
void countA(){
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    unsigned long long int i;
    for(i = 0; i < 4294967296; i++){
        //do nothing
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec)*1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("Time taken by OTHER: %f seconds\n", time_taken);
}

void countB(){
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    unsigned long long int i;
    for(i = 0; i < 4294967296; i++){
        //do nothing
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec)*1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("Time taken by FIFO: %f seconds\n", time_taken);
}

void countC(){
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    unsigned long long int i;
    for(i = 0; i < 4294967296; i++){
        //do nothing
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec)*1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
    printf("Time taken by RR: %f seconds\n", time_taken);
}

void thrA(){
    int x=pthread_attr_init(&attrA);
    int y=pthread_attr_setinheritsched(&attrA, PTHREAD_EXPLICIT_SCHED);
    int z=pthread_attr_setschedpolicy(&attrA, SCHED_OTHER);
    paramA.sched_priority = 1;
    pthread_attr_setschedparam(&attrA, &paramA);
    if (x!=0 || y!=0 || z!=0){
        printf("Error in pthread initialization");
    }
}

void thrB(){
    int p=pthread_attr_init(&attrB);
    int q=pthread_attr_setinheritsched(&attrB, PTHREAD_EXPLICIT_SCHED);
    int r=pthread_attr_setschedpolicy(&attrB, SCHED_FIFO);
    paramB.sched_priority = 1;
    pthread_attr_setschedparam(&attrB, &paramB);
    if (p!=0 || q!=0 || r!=0){
        printf("Error in pthread initialization");
    }
}

void thrC(){
    int d=pthread_attr_init(&attrC);
    int e=pthread_attr_setinheritsched(&attrC, PTHREAD_EXPLICIT_SCHED);
    int f=pthread_attr_setschedpolicy(&attrC, SCHED_RR);
    paramC.sched_priority = 1;
    pthread_attr_setschedparam(&attrC, &paramC);
    if (d != 0 || e != 0 || f != 0){
        printf("Error in pthread initialization");
    }
}

int main(){
    thrA();
    thrB();
    thrC();
    int ret1=pthread_create(&threadA, &attrA, (void *)countA, NULL);
    int ret2=pthread_create(&threadB, &attrB, (void *)countB, NULL);
    int ret3=pthread_create(&threadC, &attrC, (void *)countC, NULL);
    if (ret1 != 0 || ret2 != 0 || ret3 != 0){
        printf("Error in creating threads");
    }
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);
}