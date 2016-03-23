#include<unistd.h>
#include<stdio.h>

int mai_n()
{
    char *arg[] = {"/bin/ls",0};
    /* fork ,and exec within child process*/
    if(fork() == 0)
    {
        printf("In child process:\n");
        execv(arg[0],arg);
        printf("I will never be called");
    }
    printf("Execution continues in parent process\n");
}
