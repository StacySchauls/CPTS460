/********************************************************************
Copyright 2010-2017 K.C. Wang, <kwang@eecs.wsu.edu>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
********************************************************************/

#include "ucode.c"

char *cp, mytty[32];
char uline[2048], buf[1024],zero;

int str(char *src, char *target)
{
  int i;
  for (i=0; i<strlen(src)-strlen(target); i++){
    if (strncmp(&src[i], target, strlen(target))==0){
      // printf("line=%s\n", src);
        return 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[ ])
{
    int fd, n, count, cr, i,j,  newline, backspace;
    int nn;

    STAT st0,st1, sttty;
    int red0, red1;

    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\r");
    printf("             KC's %s in action\n", argv[0]); 
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\r");   

    cr = '\r'; 
    newline='\n';
    backspace='\b';
    gettty(mytty);

    /*****
    printf("mytty=%s\n", mytty);
    getc();
    *******/
    fstat(0, &st0);
    fstat(1, &st1); 
    stat(mytty, &sttty);
    red0 = 1;
    if (st0.st_dev == sttty.st_dev && st0.st_ino == sttty.st_ino)
        red0 = 0; 

    red1 = 1;
    if (st1.st_dev == sttty.st_dev && st1.st_ino == sttty.st_ino)
       red1 = 0; 
 
    if (argc < 2){ // grep from stdin
      printf("usage : grep pattern filename\n");
      exit(1);
    }
    /*
    printf("argc=%d argv[1]=%s red0=%d red1=%d\n", argc, argv[1], red0, red1);
    getc();
    */
    if (argc == 2){
      // if 0 has bee redirected ==> do NOT show the lines read==>getline()
      // otherwise, must show each char typed ==> call gets()
     if (red0){
        nn = 1;
        while(nn){
          nn = getline(uline);
          //printf("nn=%x\n", nn);
       
          if (str(uline, argv[1]))
	     printf("%s", uline);
        }
      }
      else{
    printf("G6 ");
         while( gets(uline)){
        	if (str(uline, argv[1]))
	        printf("%s", uline);
         }
      }
    }
    else{
       printf("open %s for read\n", argv[1]);
       fd = open(argv[1], O_RDONLY);   /* open input file for READ */
       if (fd < 0){
	 printf("open %s failed\n", argv[1]);
         exit(2);
       }

       count = 0;
       while( (n = read(fd, buf, 1024)) ){
             buf[n] = 0;
             uline[0] = 0;

             //printf("buf=%s", buf);
             j = 0;

             for (i=0; i<n; i++){
                 if (buf[i]=='\n' || buf[i]=='\r')
	             break;
	         uline[j++] = buf[i];
                 count++;
             }
             uline[j] = 0;
             count++;

             //printf("uline=%s\n", uline);

             if (str(uline, argv[2]))
                 printf("%s", uline);

             lseek(fd, (long)count, 0);
       }
    }
}

