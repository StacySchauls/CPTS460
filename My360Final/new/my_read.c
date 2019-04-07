#include "type.h"


int my_read(int argc, char *argv[]){
    int fd = 0;
    int nbytes = 0;
    char fd_str[255] = {0}, nBytesStr[BLKSIZE] = {0}, buf[BLKSIZE] = {0};

    if(argc < 1){
        //No file given
        printf("Read: Enter an opened file to read: ");
        fgets(fd_str, 255, stdin);
       // fd_str[strlen(fd_str)-1] = '\0';
        fd = atoi(fd_str);
        printf("Enter number of bytes to read from file: ");
        fgets(nBytesStr, BLKSIZE, stdin);
        nBytesStr[strlen(nBytesStr) -1] = '\0'; //kill new line
        nbytes = atoi(nBytesStr);
    }
    else if (argc < 2){
        //only provided the file descriptor
        fd = atoi(argv[0]);
        printf("Enter number of bytes to read from file: ");
        fgets(nBytesStr, BLKSIZE, stdin);
        nBytesStr[strlen(nBytesStr) -1] = '\0'; //kill new line
        nbytes = atoi(nBytesStr);
    }
    else{
        //provided everything we needed
        fd = atoi(argv[0]);
        nbytes = atoi(argv[1]);
    }

    printf("FD: %d\nNbytes: %d\n", fd, nbytes);
    //check if fd is good
}