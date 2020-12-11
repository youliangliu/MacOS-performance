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
    
    //Change sent message size here
    const int SEND_SIZE = 5000000;
    char msg[SEND_SIZE];
    for (int i = 0; i!=SEND_SIZE; i++) {
        msg[i] = 'k';
    }
    
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
    int bytes_sent;
    start_time = rdtsc();
    bytes_sent = send(connfd, msg, strlen(msg), 0);
    end_time = rdtsc();
    printf("Bytes send: %d\n",bytes_sent);
    printf("Message length: %lld\n",strlen(msg));
    printf("Clks: %lf\n",(double)(end_time-start_time));
    close(connfd);
    close(sockfd);
}

