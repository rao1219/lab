#include <fcntl.h>
#include <unistd.h>
#include<string.h>
int main()
{
    /**
    1. how to use lseek() to append a file to another file?
    */
    char buf[300] ;

    /**
    * a. 把file1内容全部读入buffer，
    * b. lseek到file2的末尾，
    * c. 将buffer写入file2
    */
    int fd1,fd2;
    if((fd1 = open("file1",O_RDONLY))==-1)
    {
        printf("Error in opening file one!\n");
        exit(0);
    }
    read(fd1,buf,100);
    if((fd2 = open("file2",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR))==-1)
    {
        printf("Error in opening file two!\n");
        exit(0);
    }
    lseek(fd2,0,SEEK_END);

    write(fd2,buf,strlen(buf));
    close(fd1);
    close(fd2);


    /**
    2.  When using O_APPEND to open a file for reading
        and writing, can we read the file from any location
        using lseek()? Can we update the data in any part of
        the file using lseek()?
    */
    fd1 = open("file1",O_RDWR |O_APPEND);
    lseek(fd1,0,SEEK_SET);
    //write(fd1,"abc",3);
    close(fd1);
    return 0;
}
