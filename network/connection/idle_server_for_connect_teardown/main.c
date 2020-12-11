//
//  main.c
//  idle_server_for_connect_teardown
//
//  Created by liuyang on 2020/12/11.
//  Copyright © 2020年 liuyang. All rights reserved.
//

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/types.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
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
    
    
    //Socket
    int sockfd, connfd, len;
    struct sockaddr_in serve_info, client;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serve_info, sizeof(serve_info));
    
    serve_info.sin_family = AF_INET;
    //Change IP here
    serve_info.sin_addr.s_addr = htonl(INADDR_ANY);
    serve_info.sin_port = htons(PORT);
    
    bind(sockfd, (struct sockaddr*)&serve_info, sizeof(serve_info));
    listen(sockfd, 5);
    
    len = sizeof(client);
    printf("Wait connection...\n");
    connfd = accept(sockfd, (struct sockaddr*)&client, &len);
    
    //start to send:
    sleep(5);
    close(sockfd);
}

