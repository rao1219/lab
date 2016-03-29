// 不好玩
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define ECHOMAX 255

int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;
    char echoBuffer[ECHOMAX];
    unsigned short echoServPort;
    int recvMsgSize;

    if(argc != 2)
    {
        printf("Usage:%s <UDP SERVER PORT>\n",argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);

    /* Create socket for sending /receiving datagrams*/
    if((sock = socket(PF_INET,SOCK_DGRAM,0)) < 0)
    {
        printf("socket() failed.\n");
        exit(1);
    }

    /* Construct local address structure */
    memset(&echoServAddr,0,sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);// 任意地址，不确定地址
    echoServAddr.sin_port = htons(echoServPort);

    /* Bind to the local address */
    if((bind(sock,(struct sockaddr *)&echoServAddr,sizeof(echoServAddr))) < 0)
    {
        printf("bind() failed.\n");
        exit(1);
    }
    printf("Waiting for connection...\n");

    int pid = fork();
    if(pid ==0){
        while(1){
            memset(echoBuffer,0,sizeof(echoBuffer));
            /* Set the size of the in-out parameter */
            cliAddrLen = sizeof(echoClntAddr);

            /* Block until receive message from a client */
            if((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX,0,(struct sockaddr *)&echoClntAddr,&cliAddrLen))<0)
            {
                perror("recvfrom() failed.\n");
                exit(1);
            }
            printf("From %s\t",inet_ntoa((struct in_addr)echoClntAddr.sin_addr));
            printf("Message:%s\n",echoBuffer);
        }
    }
    else{
        /* Send received datagram back to the client */
        while(1){
        memset(echoBuffer,0,sizeof(echoBuffer));
            /* Set the size of the in-out parameter */
            cliAddrLen = sizeof(echoClntAddr);

            /* Block until receive message from a client */
            if((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX,0,(struct sockaddr *)&echoClntAddr,&cliAddrLen))<0)
            {
                perror("recvfrom() failed.\n");
                exit(1);
            }

            printf("From %s\t",inet_ntoa((struct in_addr)echoClntAddr.sin_addr));
            printf("Message:%s\n",echoBuffer);

            scanf("%s",echoBuffer);

            if((sendto(sock,echoBuffer,strlen(echoBuffer),0,(struct sockaddr *)&echoClntAddr,sizeof(echoClntAddr)))== -1)
            {
                close(sock);
                perror("sendto() sent a different number of bytes than expected.\n");
                exit(1);
            }
        }
    }
}
