/*************************************************************************
	> File Name: teststr.c
	> Author:
	> Mail:
	> Created Time: Tue 29 Mar 2016 01:45:07 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main()
{
    char *temp = malloc(sizeof(char));
    scanf("%s",temp);
    printf("%s",temp);

    return 0;
}
