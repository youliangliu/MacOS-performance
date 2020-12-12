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
int fd[2];

void *func() {
    uint64_t time = rdtsc();
    write(fd[1], (void*)&time, sizeof(uint64_t));
    sleep(0.1);
    pthread_exit(NULL);
}
int main(int argc, const char * argv[]) {
    int count = 10;
    int true_count = 0;
    uint64_t total = 0;
    uint64_t total_square = 0;
    uint64_t time = 0;
    for (int i = 0; i != count; i++) {
        uint64_t start_time;
        uint64_t end_time;
        
        pthread_t thread;
        pipe(fd);
        pthread_create(&thread, NULL, func, NULL);

        read(fd[0], (void*)&start_time, sizeof(uint64_t));
        end_time = rdtsc();
        time = end_time-start_time;
        if(time<100000){
            total +=time;
            total_square += ((uint64_t)time)*((uint64_t)time);
            true_count++;
        }
        pthread_join(thread, NULL);
    }
    
    double average = ((double)(total))/true_count;
    printf("Average switch: %lf\n", average);
    printf("Std switch: %lf\n", sqrt( ((double)total_square)/true_count-average*average));
    return 0;
    
    
}
