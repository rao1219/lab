/*************************************************************************
	> File Name: hostalias.c
	> Author:
	> Mail:
	> Created Time: Sun 13 Mar 2016 12:20:00 PM CST
 ************************************************************************/

#include<stdio.h>
#include<netdb.h>
#include<stdlib.h>
#include<sys/types.h>
int main_fjdlkjf()
{
    struct hostent* host = (struct hostent *)malloc(sizeof(struct hostent));
    if(!host){
        printf("fault!\n");
    }
    char ** alias;
    char *hostname = "www.baidu.com";
    if((host=gethostbyname(hostname)==NULL))
    {
        printf("\t No information found!\n");
        exit(1);
    }
    for(alias = host->h_aliases;*alias!=NULL;alias++)
        printf("\t Host aliases:%s\n",*alias);
    exit(0);
}
