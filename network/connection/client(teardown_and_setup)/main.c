//
//  main.c
//  setup_and_teardown
//
//  Created by liuyang on 2020/12/11.
//  Copyright © 2020年 liuyang. All rights reserved.
//

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

int MAX = 100;
uint64_t start_time = 0;
uint64_t end_time = 0;

static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

int main()
{
    int sockfd;
    struct sockaddr_in serv_info;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_info, sizeof(serv_info));
    serv_info.sin_family = AF_INET;
    //Change IP here
    serv_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_info.sin_port = htons(PORT);
    
    start_time = rdtsc();
    connect(sockfd, (struct sockaddr*)&serv_info, sizeof(serv_info));
    end_time = rdtsc();
    printf("Setup overhead: %lf\n", (double)(end_time-start_time));
    start_time = rdtsc();
    close(sockfd);
    end_time = rdtsc();
    printf("Teardown overhead: %lf\n", (double)(end_time-start_time));
}
