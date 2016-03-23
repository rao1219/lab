#include<stdio.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/types.h>
int main()
{
    struct hostent *host;
    /**
    char * 字符串
    char ** 字符串数组
    */
    char **alias;
    char *hostname = "www.126.com";
    if((host=gethostbyname(hostname)) == NULL)
    {
        printf("\tNo information found!\n");
        exit(1);
    }

    for(alias = host->h_aliases;*alias != NULL;alias++)
        printf("\tHost aliases:%s\n",*alias);
    exit(0);
}
