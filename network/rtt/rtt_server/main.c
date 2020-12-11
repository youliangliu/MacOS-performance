//
//  main.c
//  rtt
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
#define PORT 8080

int MAX = 100;

void Rtt(int sockfd)
{
    char buff[MAX];
    char send_buff[MAX];
    while(1) {
        bzero(buff, MAX);
        bzero(send_buff, MAX);
        char reply[] = "end\n";
        for (int i = 0; i!=4; i++) {
            send_buff[i] = reply[i];
        }
        
        read(sockfd, buff, sizeof(buff));
        write(sockfd, send_buff, sizeof(send_buff));
        
        if (strncmp("end", send_buff, 3) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}

// Driver function
int main()
{
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
    connfd = accept(sockfd, (struct sockaddr*)&client, &len);
    Rtt(connfd);
    close(sockfd);
}
