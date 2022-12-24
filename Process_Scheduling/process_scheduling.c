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
#include <sys/wait.h>

// function to execute test1.bash 
void *test1(void *arg){
    char *args[] = {"./test1.bash",NULL};
    execv(args[0],args);
    return NULL;
}

// function to execute test2.bash
void *test2(void *arg){
    char *args[] = {"./test2.bash",NULL};
    execv(args[0],args);
    return NULL;
}

// function to execute test3.bash
void *test3(void *arg){
    char *args[] = {"./test3.bash",NULL};
    execv(args[0],args);
    return NULL;
}

int main(){
    int x;
    struct timespec start, finish;
    for (int i=0;i<3;i++){
        clock_gettime(CLOCK_REALTIME, &start);
        x = fork();
        if (x == 0){
            if (i == 0){
                test1(NULL);
            }
            else if (i == 1){
                test2(NULL);
            }
            else if (i == 2){
                test3(NULL);
            }
        }
    }

    int status;
    for (int i=0;i<3;i++){
        wait(&status);
        clock_gettime(CLOCK_REALTIME, &finish);
        double elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("%f", elapsed);
        printf("\n");
    }
    return 0;
}