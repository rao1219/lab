/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Sun 20 Mar 2016 07:48:20 PM CST
 ************************************************************************/

#include<stdio.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/types.h>

int main()
{
    struct hostent *host;
    char **alias;
    char *hostname = "www.126.com";
    if((host=gethostbyname(hostname)) == NULL)
    {
        printf("\tNo information found!\n");
        exit(1);
    }

    for(alias = host->h_aliases;*alias !=NULL;alias++)
    {
        printf("\tHost aliases:%s\n",*alias);
        exit(0);
    }
}
