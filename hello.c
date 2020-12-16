#include "apue.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#ifdef PATH_MAX
static long pathmax = PATH_MAX;
#else
static long pathmax = 0;
#endif

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

int main(){

    /*
        为什么不适用PATH_MAX或者_POSIX_PATH_MAX,而使用pathconf("/", _PC_PATH_MAX)
        1. 这种方式的可移植性不好,如果MAXPATH是indeterminate，就会有问题
        char buffer[PATH_MAX];
        getcwd(buffer,PATH_MAX);
        printf("The current directoryis:%s\n",buffer);
        2. _POSIX_PATH_MAX给的默认值太小了，不够用
        说以我们需要用pathconf("/", _PC_PATH_MAX)，运行时动态获取

        _POSIX_PATH_MAX;
        _POSIX_OPEN_MAX;
    */

    size_t size = 0;
    char *path = path_alloc(&size);
    char *cwd = getcwd(path, size);
    printf("current working directory is %s\n", cwd);

    long int value = sysconf(_SC_V7_LP64_OFF64);
    value = _POSIX_V7_LP64_OFF64;


}

char * path_alloc(size_t *sizep){
    char *ptr;
    size_t size;

    if(pathmax == 0)
        pathmax = pathconf("/", _PC_PATH_MAX);

    if(openmax == 0)
        openmax = sysconf(_SC_OPEN_MAX);

    size = pathmax + 1;

    if((ptr = malloc(size)) == NULL){
        //err_sys("malloc error for pathname");
    }

    *sizep = size;

    return ptr;
}