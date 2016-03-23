/*************************************************************************
	> File Name: byteorder.c
	> Author:
	> Mail:
	> Created Time: Thu 17 Mar 2016 11:55:22 AM CST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
    union{
        short s;
        char c[sizeof(short)];
    }un;

    un.s=0x0102;

    if (sizeof(short)==2){
        if (un.c[0]==1 &&un.c[1]==2)
            printf("big-endian\n");
        else if(un.c[0]==2 && un.c[1]==1)
            printf("little-endian\n");
        else
            printf("Unknown\n");
    }
    else
        printf("sizeof(short)=%d\n",sizeof(short));

    exit(0);
}
