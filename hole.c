#include "apue.h"
#include <fcntl.h>

/*
The file’s offset can be greater than the file’s current size, in which case the next
write to the file will extend the file.This is referred to as creating a hole in a file and is
allowed. Any bytes in a file that have not been written are read back as 0.
*/

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void){
    int fd;

    if((fd=creat("file.nohole",FILE_MODE)) < 0){
        err_sys("creat error");
    }        

    //offset will be 10 after write system call
    if(write(fd,buf1,10) != 10){
        err_sys("buf1 write error");
    }

    //offset will be 16384 after lseek system call
    if(lseek(fd,16384,SEEK_SET) == -1){
        err_sys("lseek error");
    }
    //offset will be 16394 after write system call
    if(write(fd,buf2,10) != 10){
        err_sys("buf2 write error");
    }

    exit(0);
}
