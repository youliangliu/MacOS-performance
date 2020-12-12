//
//  main.c
//  context
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

int main(int argc, const char * argv[]) {
    pthread_t thread;
    double count = 10;
    total = 0;
    total_square = 0;
    
    uint64_t time = 0;
    
    int true_count = 0;
    
    
    for (int i = 0; i != count; i++) {
        int fd[2];
        pipe(fd);
        uint64_t offset = rdtsc();
        pid_t pid = fork();
        if (pid == 0)
        {
            close(fd[0]);
            uint64_t time = rdtsc()-offset;
            write(fd[1], &time, sizeof(time));
            sleep(0.1);
            //close(fd[1]);
            exit(0);
        }
        else
        {
            close(fd[1]);
            read(fd[0], &time, sizeof(time));
            end_time = rdtsc()-offset;
            //printf("Main(%d) received: %lf\n", getpid(), (double)time);
            time = end_time-time;
            //printf("Result: %lf\n", (double)time);
            //if (time<150000) {
            if (time<200000) {
                total +=time;
                total_square += ((uint64_t)time)*((uint64_t)time);
                true_count++;
            }
            close(fd[0]);
            wait(NULL);
        }
    }
    
    double average = ((double)(total))/true_count;
    printf("Average switch: %lf\n", average);
    printf("Std switch: %lf\n", sqrt( ((double)total_square)/true_count-average*average));
    return 0;
    
}
