/*
 发啥返回啥
*/

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define ECHOMAX 255 // longest string to echo

int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr;// echo server address
    struct sockaddr_in fromAddr;//source address of echo
    unsigned short echoServPort;
    unsigned int fromSize;// in-out of address size from recvfrom()

    char *servIP;
    char *echoString;
    char echoBuffer[ECHOMAX+1];

    int echoStringLen;
    int resStringLen;

    if((argc < 3)|| (argc > 4))
    {
        printf("Useage: %s <Server IP> <Echo Word> [<Echo Port>]\n",argv[0]);
        exit(1);
    }

    servIP = argv[1];
    echoString = argv[2];
    if((echoStringLen = strlen(echoString)) > ECHOMAX)
    {
        printf("Echo word too long!\n");
        exit(1);
    }

    if(argc == 4)
        echoServPort = atoi(argv[3]);
    else
        echoServPort = 7; // 7 is the well-known port for echo service

    /* Create a datagram/UDP socket */
    if( (sock = socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP)) <0 )
    {
        printf("socket() failed.\n");
        exit(1);
    }

    /* Construct the server address structure */
    memset(&echoServAddr,0,sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_port = htons(echoServPort);

    /* Send the string to the server */
    if((sendto(sock,echoString,echoStringLen,0,(struct sockaddr *)&echoServAddr,sizeof(echoServAddr))) != echoStringLen)
    {
        printf("sendto() sent a different number of bytes than expected");
        exit(1);
    }

    /* Recv a response */
    fromSize = sizeof(fromAddr);
    if((resStringLen = recvfrom(sock,echoBuffer,ECHOMAX,0,(struct sockaddr *)&fromAddr,&fromSize)) !=echoStringLen)
    {
        printf("recvfrom() failed\n");
    }

    if(echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    {
        printf("%d\n%d\n",echoServAddr.sin_addr.s_addr,fromAddr.sin_addr.s_addr);
        printf("Error: received a packet from unknown source.\n");
        //exit(1);
    }

    /* null-terminate the received data */
    echoBuffer[resStringLen] = '\0';
    printf("Received :%s\n",echoBuffer);
    close(sock);
    exit(0);
}
