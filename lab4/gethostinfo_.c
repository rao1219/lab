#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

int main()
{
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo,*p;
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC; //don't care ipv4 or v6
    hints.ai_socktype = SOCK_STREAM; //TCP stream sockets
    hints.ai_flags = AI_PASSIVE;    // fill in my IP for me

    char ipstr[INET_ADDRSTRLEN];

    if((status = getaddrinfo("8.8.8.8","3490",&hints,&servinfo))!= 0){
        fprintf(stderr,"getaddrinfo error:%s\n",gai_strerror(status));
        exit(1);
    }
    printf("IP addresses:\n\n");
    for(p = servinfo;p!=NULL;p = p->ai_next)
    {
        void *addr;
        char *ipver;

        //get the pointer to the address itself;
        //different fields in IPv4 and IPv6:
        if(p->ai_family == AF_INET){ //iIPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { //IPV6
            struct sockaddr_in *ipv6 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv6->sin_addr);
            ipver = "IPv6";
        }
        //convert the IP to a string and print it:
        inet_ntop(p->ai_family,addr,ipstr,sizeof(ipstr));
        printf("\t%s:%s",ipver,ipstr);
    }

    freeaddrinfo(servinfo);

    return 0;
}

