
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
int main()
{
    char quit='.';
    char *buf1 = "start of file\n";
    char *buf2 = "lseek test\n";
    int fd;
    if((fd = open("out.out",O_RDWR | O_CREAT |O_APPEND,S_IWUSR|S_IRUSR))==-1)
        printf("Error in opening\n");

//    while(buf[0]!=quit)
//    {
//        read(0,buf,1);
//        write(fd,buf,1);
//        write(1,buf,1);
//    }
    //strcpy(buf,"start of file\n");
    //printf("%s\n,%d",buf,sizeof(buf)*4);
    write(fd,buf1,sizeof(buf1)*2);
    lseek(fd,0,SEEK_SET);

    write(fd,buf2,sizeof(buf2)*2);

    close(fd);

    return 0;
}
