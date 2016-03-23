/*************************************************************************
	> File Name: signal1.c
	> Author:
	> Mail:
	> Created Time: Sun 13 Mar 2016 11:19:38 AM CST
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
void signalRoutine(int);

int main_fjdlfd()
{
    printf("Signal processing demo program\n");
    while(1)
    {
        signal(SIGINT,signalRoutine);
    }
}
void signalRoutine(int dummy)
{
    printf("Signal routine called[%d]\n",dummy);
    exit(0);
}
