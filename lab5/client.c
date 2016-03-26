#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define ERR_EXIT(m) \
        do \
        { \
                perror(m); \
                exit(EXIT_FAILURE); \
        } while(0)

void udp_client(int sock)
{
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret;
    char sendbuf[1024] = {0};
    char recvbuf[1024] = {0};
    int i = 0;
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        i++;
        sendto(sock, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

        ret = recvfrom(sock, recvbuf, sizeof(recvbuf), 0, NULL, NULL);
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;
            ERR_EXIT("recvfrom");
        }
        printf("\nMessage %d---------Sending\n",i);
        fputs(recvbuf, stdout);
        printf("Message %d------- ------Ok.\n\n", i);
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sock);


}

int main(void)
{
    int sock;
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
        ERR_EXIT("socket");

    udp_client(sock);

    return 0;
}
