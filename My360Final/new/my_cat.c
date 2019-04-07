#include "util.c"
#include "type.h"

int my_cat(int argc, char *argv){
    if(argc < 1){
        printf("Error: Provide a file to cat. \n");
        return -1;
    }
    return do_cat(argv[0]);
}

int do_cat(char *pathname){
    int n, i;
    char mybuf[BLKSIZE];
    int fd = 0;
    char dummy = 0;

    fd = ()
}