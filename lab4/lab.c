#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>

int main(int argc,char *argv[])
{
    struct in_addr addr;
    struct hostent *host;
    char **alias;
    struct in_addr **iplist;
    char *in = argv[1];

    if (argc != 2) {
        fprintf(stderr,"usage: ./lab hostname (or ip address)\n");
        return 1;
    }

    printf("--------------------------- ---------\n\n");
    int is_addr = inet_aton(in,&addr);
    if(is_addr == 1)
    {
    //ip
        host = gethostbyaddr(&addr,4,AF_INET);
        if(host == NULL)
        {
            printf("No information found!\n");
            return 0;
        }
    }
    else if(is_addr ==0)
    {
    //name
        host = gethostbyname(in);
        if(host == NULL)
        {
            printf("No information found!\n");
            return 0;
        }
    }
    else
    {
        printf("Unknown input\n");
        return 2;
    }

    printf("Hostname:\n\t%s\n",host->h_name);
    printf("Host alias:\n");
    for(alias =host->h_aliases;*alias!=NULL;alias++)
    {
        printf("\t%s\n",*alias);
    }
    printf("type:\n");
    char *type_str;

    switch(host->h_addrtype)
    {
        case AF_INET:
            type_str = "AF_INET\n";
            printf("\t%s",type_str);
        break;
        case AF_INET6:
            type_str="AF_INET6\n";
            printf("\t%s",type_str);
        break;
        default:
            printf("\tUnknown address type\n");
            return 2;
        break;
    }
    iplist=(struct in_addr **)host->h_addr_list;
    printf("Addreses:\n");
    for(;*iplist!=NULL;iplist++)
    {
        char ip[INET_ADDRSTRLEN];
        inet_ntop(host->h_addrtype,*iplist,ip,INET_ADDRSTRLEN);
        //ip = inet_ntoa(*iplist);
        printf("\t%s\n",ip);
    }
    printf("\n------------------------------------\n");

    return 0;
}
