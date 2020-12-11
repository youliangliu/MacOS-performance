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

void GetRtt(int sockfd)
{
    char buff[MAX];
    char receive_buff[MAX];
    while(1) {
        bzero(buff, sizeof(buff));
        bzero(receive_buff, sizeof(buff));
        char send[] = "12345678901234567890123456789012\n";
        for (int i = 0; i!=33; i++) {
            buff[i] = send[i];
        }

        start_time = rdtsc();
        write(sockfd, buff, sizeof(buff));
        read(sockfd, receive_buff, sizeof(receive_buff));
        end_time = rdtsc();
        
        if ((strncmp(receive_buff, "end", 3)) == 0) {
            break;
        }
    }
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
    GetRtt(sockfd);
    printf("Rtt: %lf\n", (double)(end_time-start_time));
    
    close(sockfd);
}
