/*************************************************************************
	> File Name: calDate.c
	> Author:Rao Qi
	> Mail:2013213278@bupt.edu.cn
	> Created Time: Sun 24 Jan 2016 10:39:11 AM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int n;
int month_num[13];
int total_num[13];
int day,month;

void input()
{
    printf("please input an integer(between 1 and 365):\n");
    scanf("%d",&n);
    int valid = check_input(n);
    if(valid == 0)
    {
        printf("Invalid input,please try again\n");
        input();
    }
}

int check_input(int n)
{
    if(n>0&&n<366)
    {
        return 1;
    }
    else
        return 0;
}

void process()
{
    int i,j;
    for(i = 0;i<=12;i++)
    {
        total_num[i] = 0;
        switch(i)
        {
            case 0:month_num[0]=0;break;
            case 1:case 3:case 5:case 7:case 8:case 10:case 12:
                month_num[i] = 31;
            break;
            case 4:case 6:case 9:case 11:
                month_num[i] = 30;
            break;
            case 2:month_num[i] = 28;
            break;
        }
        for(j=0;j<=i;j++)
        {
            total_num[i] += month_num[j];
        }

    }
    for(i = 1;i<=12;i++)
    {
        //printf("month:%d\t%d\n",i,total_num[i]);
        if(n>total_num[i-1]&&n<=total_num[i])
        {
            day = n - total_num[i-1];
            month = i;
            break;
        }
    }
}
void output()
{
    char end[5],mon[20];
    if(day%10 == 1){
        strcpy(end,"st");
    }
    else if(day%10 == 2){
        strcpy(end,"nd");
    }
    else if(day%10 ==3){
        strcpy(end,"rd");
    }
    else
        strcpy(end,"th");

    switch(month)
    {
        case 1:
            strcpy(mon,"January");break;
        case 2:
            strcpy(mon,"February");break;
        case 3:
            strcpy(mon,"March");break;
        case 4:
            strcpy(mon,"April");break;
        case 5:
            strcpy(mon,"May");break;
        case 6:
            strcpy(mon,"June");break;
        case 7:
            strcpy(mon,"July");break;
        case 8:
            strcpy(mon,"August");break;
        case 9:
            strcpy(mon,"September");break;
        case 10:
            strcpy(mon,"October");break;
        case 11:
            strcpy(mon,"November");break;
        case 12:
            strcpy(mon,"December");break;
    }
    printf("%s\t%d%s\n",mon,day,end);
}

int _main_()
{
    while(1){
        input();
        process();
        output();
    }
    return 0;
}
