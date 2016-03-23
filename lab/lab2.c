#include <fcntl.h>
#include <unistd.h>
#include<string.h>
int main()
{
    /**
    2.  When using O_APPEND to open a file for reading
        and writing, can we read the file from any location
        using lseek()? Can we update the data in any part of
        the file using lseek()?
    */
    int fd;

    fd = open("file3",O_RDWR |O_APPEND);
    lseek(fd,0,SEEK_SET);
    write(fd,"abc",3);
    close(fd);
    return 0;
}

