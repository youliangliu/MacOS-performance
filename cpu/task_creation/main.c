//
//  main.c
//  task
//
//  Created by liuyang on 2020/12/10.
//  Copyright © 2020年 liuyang. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

uint64_t end_time, start_time;
uint64_t total = 0;
uint64_t total_square = 0;

void threadFunc(){
    end_time = rdtsc();
    total +=end_time-start_time;
    total_square += (end_time-start_time)*(end_time-start_time);
    //printf("result: %lf\n", (double)(end_time-start_time));
}

int main(int argc, const char * argv[]) {
    pthread_t thread;
    double count = 20;
    total = 0;
    total_square = 0;
    
    for (int i = 0; i != count; i++) {
        start_time = rdtsc();
        pthread_create(&thread, NULL, threadFunc, NULL);
        pthread_join(thread, NULL);
    }
    
    double average = ((double)(total))/count;
    printf("Average thread: %lf\n", average);
    printf("Std thread: %lf\n", sqrt( ((double)total_square)/count-average*average));
    
    
    int time = 0;
    total = 0;
    total_square = 0;
    int true_count = 0;
    
    
    for (int i = 0; i != count; i++) {
        int fd[2];
        pipe(fd);
        start_time = rdtsc();
        pid_t pid = fork();
        end_time = rdtsc();
        if (pid == 0)
        {
            close(fd[0]);
            //printf("Child: %lf\n", (double)(end_time-start_time));
            time = (int)(end_time-start_time);
            write(fd[1], &time, sizeof(time));
            close(fd[1]);
            exit(0);
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            read(fd[0], &time, sizeof(time));
            if (time > (int)(end_time-start_time)) {
                //printf("big!\n");
                time = (int)(end_time-start_time);
            }
            //printf("Main(%d) received: %d\n", getpid(), time);
            if (time<1500000) {
                total +=time;
                total_square += ((uint64_t)time)*((uint64_t)time);
                true_count++;
            }
            close(fd[0]);
        }
    }
    average = ((double)(total))/true_count;
    printf("Average process: %lf\n", average);
    printf("Std process: %lf\n", sqrt( ((double)total_square)/true_count-average*average));
    return 0;
    
}
