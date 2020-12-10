//
//  main.c
//  221_proj
//
//  Created by liuyang on 2020/11/16.
//  Copyright © 2020年 liuyang. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}
int main(int argc, const char * argv[]) {
    int f = open("map_file.txt", O_RDWR);
    if (f < 0) {
        printf("Open error\n");
        return -1;
    }
    unsigned int page_size = 4096*10;
    unsigned int file_length = 77203089;
    //    char write_buf[1] = {'2'};
    //    for (int i = 0; i!=file_length; i++) {
    //        if (write(f, write_buf, 1)<0) {
    //            printf("Write error\n");
    //            return -1;
    //        }
    //    }
    char* map =(char*) mmap(NULL, file_length, PROT_READ | PROT_WRITE, MAP_SHARED, f, 0);
    
    uint64_t start_time;
    uint64_t end_time;
    char tem;
    uint64_t overhead = 100;
    uint64_t overhead_loop = 6;
    
    start_time = rdtsc();
    int i;
    for (i = 0; i < 100; i++)
    {
        //tem = map[(((i+1)*page_size) % (f - 1))];
        tem = map[(i+1)*page_size];
    }
    //sleep(1);
    end_time = rdtsc();
    
    double average = (double)(end_time-start_time - overhead) / 100;
    printf("Time: %lf\n", average);
    //printf("Time: %lf\n", (double)(end_time-start_time));
    //printf("CLK: %d\n", CLOCKS_PER_SEC);
    munmap(map, file_length);
    close(f);
    return 0;
}
