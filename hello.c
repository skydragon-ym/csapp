#include "apue.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

int main(){

    /*
    //这种方式的可移植性不好,如果MAXPATH是indeterminate，就会有问题
    char buffer[MAXPATH];
    getcwd(buffer,MAXPATH);
    printf("The current directoryis:%s\n",buffer);
    */

    size_t size = 0;
    char *path = path_alloc(&size);
    char *cwd = getcwd(path, size);
    printf("current working directory is %s\n", cwd);
}

char * path_alloc(size_t *sizep){
    char *ptr;
    size_t size;

    pathmax = pathconf("/", _PC_PATH_MAX);

    size = pathmax + 1;

    if((ptr = malloc(size)) == NULL){
        //err_sys("malloc error for pathname");
    }

    *sizep = size;

    return ptr;
}