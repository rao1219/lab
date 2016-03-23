/*************************************************************************
	> File Name: lssk1.c
	> Author:
	> Mail:
	> Created Time: Thu 10 Mar 2016 10:52:30 PM CST
 ************************************************************************/

#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

#define FILE_MODE 0644

int main_fjdkl()
{
    int fd;

    if((fd = creat("file.hole",FILE_MODE))<0)
    {
        printf("create error\n");
        exit(1);
    }
    if(write(fd,buf1,10)!=10)
    {
        printf("buf1 write error\n");
        exit(1);
    }
    /*offset now = 10*/
    if(lseek(fd,40,SEEK_SET)==-1)
    {
        printf("lseek error\n");
        exit(1);
    }
    /*offset now = 40*/
    if(write(fd,buf2,10)!=10)
    {
        printf("buf2 write error\n");
        exit(1);
    }
    /*offset now = 50*/
    exit(0);
}
