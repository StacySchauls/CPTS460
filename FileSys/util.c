

int cp_file(){
    char buf[1024];
    int n;
    int fd = open(path, O_RDONLY);
    creat(parameter[0], 0);

    int gd = open(parameter[0], O_WRONLY);
    while(n = read(fd, buf, BLKSIZE)){
        write(gd, buf, n);
    }
    close(fd);
    close(gd);
}