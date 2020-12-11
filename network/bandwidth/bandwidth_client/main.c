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
    
    connect(sockfd, (struct sockaddr*)&serv_info, sizeof(serv_info));
    //GetRtt(sockfd);
    const int READ_SIZE = 1000000;
    char buff1[READ_SIZE];
    int received = -1;
    int total_received = 0;
    while (received!=0) {
        received = recv(sockfd, buff1, READ_SIZE-1, 0);
        total_received +=received;
    }
    close(sockfd);
    printf("Total received: %d\n", total_received);
}
