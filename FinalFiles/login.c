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

char buf[1024], uname[64], upass[64];
char pline[64], mytty[64], *pname[8];
char *cp, *cq, *cpp, *cqq;
int gid, uid, i, n;

// seems stdin,stdout,stderr are keywords in bcc
// int stdin, stdout, stderr; ==> auto_start symbol
int in, out, err;
int fd;
// login : call by init as "login tty0" | "login ttyS0" | ...
// Upon entry, name[0]=filename, name[1]=mytty string 
char whattty[64];

int main(int argc, char *argv[ ])
{
  //printf("proc %d in LOGIN: argv[1]=%s\n", getpid(), argv[1]);
  close(0); close(1); close(2);
  strcpy(mytty, argv[1]);
  //strcpy(mytty, "/dev/tty0");

  in  = open(mytty, 0);
  out = open(mytty, 1);
  err = open(mytty, 1);

  fixtty(mytty);  // register mytty string in PROC.tty[]
  gettty(whattty);
  printf("KCLOGIN : tty=%s\n", whattty);
  printf("KCLOGIN : open %s as stdin=%d, stdout=%d, stderr=%d\n", 
	 mytty, in, out, err);

  while(1){
    //printf("------------------------------------\n\r");
    print2f("login:"); 
    gets(uname);
    print2f("password:"); 
    gets(upass); 
    //printf("------------------------------------\n\r");


    /** open /etc/passwd file to get uname's uid, gid, HOME, program **/
    fd = open("/etc/passwd", 0); 
    if (fd < 0){ printf("no passwd file\n"); exit(1);}

    n = read(fd, buf, 2048);
    buf[n] = 0;

    cp = cq = buf;
    while(cp < &buf[n]){   
       while (*cq != '\n'){
         if (*cq == ' ') *cq = '-';
         if (*cq == ':') *cq = ' ';
         cq++;
       }
       *cq = 0;
       strcpy(pline, cp);
       cpp = cqq = pline;
       i = 0;
       while (*cqq){
         if (*cqq == ' '){
	   *cqq = 0;
           pname[i] = cpp;
           i++;
           cqq++; cpp = cqq;
           continue;
         }
         cqq++; 
       }

       if (strcmp(uname, pname[0])==0 && strcmp(upass, pname[1])==0){
          printf("KCLOGIN : Welcome! %s\n",uname);
          printf("KCLOGIN : cd to HOME=%s  ",pname[5]);
    	  chdir(pname[5]);  // cd to panme[5]
    
          gid = atoi(pname[2]); uid = atoi(pname[3]);
          printf("change uid to %d\n",uid);
          chuid(uid, 0);        // change gid, uid 
    
          printf("exec to /bin/sh .....\n");
          close(fd); 
          exec("sh kcsh start");
       }
       cq++; cp = cq;
    }
    printf("login failed, try again\n");
    close(fd); 
  }
}
