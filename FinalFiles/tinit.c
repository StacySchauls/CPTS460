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

int pid, cdserver, console, s0, s1;

main(int argc, char *argv[ ])
{
  int in, out;

  in  = open("/dev/tty0", O_RDONLY);
  out = open("/dev/tty0", O_WRONLY);

  printf("%s\n", "KCINIT : fork a login task on console");

  console = fork();

  if (console){
       printf("KCINIT : fork login tasks on serial terminals\n");
       s0 = fork();
       if (s0){
           cdserver = fork();
           if (cdserver){
              printf("start CDSERVER %d\n", cdserver);
	      parent();
	   }
           else{
              exec("cdserver"); 
	   }
       }
       else
	 s0login();
  
       /*****************
       if (s0){
	 s1 = fork();
         if (s1)
	    parent();
         else 
            s1login();
       }
       else{
	 s0login();
       }

       parent();
       ******************/
   }
  else{
    login();
  }
}

int login()
{
  exec("login /dev/tty0");
}

int s0login()
{
  exec("login /dev/ttyS0");
}
      
int s1login()
{
  exec("login /dev/ttyS1");
}
      
int parent()
{
  int status;
  printf("KCINIT : waiting .....\n");

  while(1){

    pid = wait(&status);

    if (pid==console){
       printf("\n-----------------------------------------------\n");
       printf("KCINIT: Oh my God! ");
       printf("My beloved login child has died\n");
       printf("Oh Well, I'll just fork another one!\n");
       printf("-----------------------------------------------\n");
       console = fork();
       if (console)
	 continue;
       else
         login();
    }
    if (pid==s0){
       printf("\n-----------------------------------------------\n");
       printf("KCINIT: Oh Dear! ");
       printf("My serial login child has died\n\r");
       printf("Oh well, I'll just fork another one!\n\r");
       printf("-----------------------------------------------\n");
       s0 = fork();
       if (s0)
	 continue;
       else
         s0login();
    }
    if (pid==s1){
       printf("\n-----------------------------------------------\n");
       printf("KCINIT: Oh No! ");
       printf("My serial login child has died\n");
       printf("Oh well, I'll just fork another one!\n");
       printf("-----------------------------------------------\n");
       s1 = fork();
       if (s1)
	 continue;
       else
         s1login();
    }
    /*
    printf("KCINIT : I just buried an orphan child task\n");
    */
  }
}
