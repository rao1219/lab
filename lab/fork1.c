#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main_te()
{
    pid_t pid;
    pid = fork();
    printf("fork returned %d\n",pid);
    exit(0);
}
