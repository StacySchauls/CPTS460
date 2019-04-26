

#include "ucode.c"

char *cp, mytty[64];

char realname[64], linkname[64];
char mybuf[1024];
int i;
char *cp;
char nline='\n';
char r='\r';
int main(int argc, char *argv[ ])
{
    int fd, n;
    char buf[1024], dummy;

    print2f("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\r");
    print2f("      STACYS MEOW PROGRAM        \n\r"); 
    print2f("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\r");   



    /* open file desciptor, if stdin, get input, write it. else, read from the file we opened, and write it to the current terminal */
    fd = 0;
    if (argc > 1){
      fd = open(argv[1], O_RDONLY);
      if (fd < 0){
    	printf("cat %s error\n", argv[1]);
        exit(0);
      }
    }

    if(argc == 1){
      fd = 0;
      while(gets(buf)){
        print2f(buf);
        print2f("\n\r");
      }
      exit(0);
    }

    while (n = read(fd, buf, 1024))
    {
        buf[n] = 0;
        cp = buf;
        if (fd)
        {
           
            for (i = 0; i < n; i++)
            {
                write(1, &buf[i], 1);
                if (buf[i] == '\n')
                {
                    write(2, &r, 1);
                }
            }
        }

        else
        {
            cp = buf;
            if (*cp == '\r')
            {
                write(2, &nline, 1);
            }
            write(1, cp, 1);
        }
}
    close(fd);
    exit(0);
}
