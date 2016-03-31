/*
 发啥返回啥
*/

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>

#include<arpa/inet.h>
#define ECHOMAX 255 // longest string to echo

void *get_in_addr(struct sockaddr *sa)
{
    if(sa->sa_family == AF_INET){
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc,char *argv[])
{
    int sock ,rv;
    struct sockaddr_in echoServAddr;// echo server address
    struct sockaddr_in fromAddr;//source address of echo
    unsigned short echoServPort ;
    unsigned int fromSize;// in-out of address size from recvfrom()

    struct addrinfo hints, *servinfo, *p;
     if(argc != 3) {
        fprintf(stderr,"usage: client hostname port\n");
        exit(1);
    }


    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((rv = getaddrinfo(argv[1], argv[2] , &hints, &servinfo))!=0){
        fprintf(stderr,"getaddrinfo: %s\n",gai_strerror(rv));
        return 1;
    }

    for(p=servinfo; p !=NULL ; p = p->ai_next) {
        if((sock = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        break;
    }

    if(p == NULL) {
        fprintf(stderr,"client: failed to connect\n");
        return 2;
    }
    char s[INET6_ADDRSTRLEN];

    inet_ntop(p->ai_family,get_in_addr((struct sockaddr *)p->ai_addr),s,sizeof(s));
    printf("client: connecting to %s\n",s);


    char *echoString = malloc(ECHOMAX*sizeof(char));
    char echoBuffer[ECHOMAX+1];

    int echoStringLen;
    int resStringLen;

    if(argc>3||argc<2)
    {
        printf("Useage: %s <Server IP> [<Echo Port>]\n",argv[0]);
        exit(1);
    }

    //servIP = argv[1];

    if(argc == 3)
        echoServPort = atoi(argv[2]);
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
    echoServAddr.sin_addr.s_addr = inet_addr(s);
    echoServAddr.sin_port = htons(echoServPort);
    printf("Connecting to service %s...\n",s);
    printf("port number:%d\n\n",echoServPort);
    printf("Message to send:");
    while(scanf("%s",echoString)){
        /* Send the string to the server */
        if((echoStringLen = strlen(echoString)) > ECHOMAX)
        {
            printf("Echo word too long!\n");
            exit(1);
        }
        if((sendto(sock,echoString,echoStringLen,0,(struct sockaddr *)&echoServAddr,sizeof(echoServAddr))) != echoStringLen)
        {
            perror("sendto() sent a different number of bytes than expected");
            //exit(1);
        }

        /* Recv a response */
        fromSize = sizeof(fromAddr);
        if((resStringLen = recvfrom(sock,echoBuffer,ECHOMAX,0,(struct sockaddr *)&fromAddr,&fromSize)) !=echoStringLen)
        {
            printf("recvfrom() failed\n");
        }

        if(echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
        {
            printf("%s\n%s\n",inet_ntoa((struct in_addr)echoServAddr.sin_addr),inet_ntoa((struct in_addr)fromAddr.sin_addr));
            printf("Error: received a packet from unknown source.\n");
            exit(1);
        }

        /* null-terminate the received data */
        echoBuffer[resStringLen] = '\0';
        printf("Received :%s\n",echoBuffer);
        printf("Message to send:");
    }
    close(sock);
    exit(0);
}
