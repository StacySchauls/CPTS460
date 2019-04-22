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
#define printk printf

int console, s0, s1;

void login()
{
  exec("login /dev/tty0");
}
void s0login()
{
  exec("login /dev/ttyS0");
}
void s1login()
{
  exec("login /dev/ttyS1");
}

void another(int pid)
{
   printf("-----------------------------------------------------\n");
   printf("KCINIT: Oh my God! My beloved login child %d has died\n", pid);
   printf("KCINIT: Oh well, I'll just fork another one!\n");
   printf("-----------------------------------------------------\n");
}
        
void parent()
{
  int pid, status;
  printf("KCINIT : waiting .....\n");
  while(1){
    pid = wait(&status);

    if (pid==console){
      //another(pid);
       console = fork();
       if (console)
	 continue;
       else
	 login();
    }
    if (pid==s0){
       s0 = fork();
       if (s0)
          continue;
       else
          s0login();
    }
    /*************
    if (pid==s1){
       s1 = fork();
       if (s1)
          continue;
       else
          s1login();
    }
    **************/
    printf("KCINIT: I just buried an orphan child task %d\n", pid);
  }
}

void cdserver()
{
  exec("cdserver");
  exit(1);
}

int main(int argc, char *argv[ ])
{
  int in, out;
  int pid;
  in  = open("/dev/tty0", O_RDONLY);
  out = open("/dev/tty0", O_WRONLY);

  printf("proc %d in Umode ", getpid());
  printf("argc=%d %s %s\n", argc, argv[0], argv[1]);

  printf("%s\n", "KCINIT: fork a login task on console");
  console = fork();
  if (console){ // parent

    printf("fork login on ttyS0\n");
    s0 = fork();
    if (s0){
      /****************
      s1 = fork();
      if (s1)
         parent();
      else
	s1login();
      **************/
      parent();
    }
    else{
      s0login();
    }
  }
  else{
    login();
  }
}


