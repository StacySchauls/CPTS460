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

main(int argc, char *argv[])
{
  int i, a,b,c, pid, ppid, mode, r, cmd, status;
  u32 usp, usp1;
  char line[64]; char uc;
  int sh, chpid;

  a = 123; b = 234; c = 345;
  mode = getcsr();
  mode = mode & (0x0000001F);
  printf("CPU mode=%x argc=%d\n", mode, argc);

  for (i=0; i<argc; i++){
    printf("argv[%d] = %s\n", i, argv[i]);
  }

  printf("In Umode: syscall getpid() to get my pid\n");
  pid  = getpid();
  ppid = getppid();

  printf("after getpid() syscall pid=%d ppid=%d usp=%x\n", pid,ppid,usp);

  //  printf("proc %d in Umode, mysp=%x usp=%x\n", pid, getmysp(), ugetusp());
  
  pid  = getpid();
  ppid = getppid();
  printf("This is process #%d in Umode at %x my father=%d\n", 
	   pid, getmyaddress(), ppid);
  ugetc();

  printf("fork a child process as sh\n");
  sh = fork();
  if (sh){ // P1
    while(1){
      printf("P1 waits for ZOMBIE child\n");
      ugetc();
      chpid = wait(&status);
      printf("chpid=%d sh=%d\n", chpid, sh);
  
      if (chpid==sh){
         printf("P1 forks another sh\n");
         sh = fork();
         if (sh)
	    continue;
         else
            do_sh();
      }
      else{
	printf("P1: buried an orphan %d\n", chpid);
      }
    }
  }
  else{ 
    do_sh();
  }
}

int do_sh()
{  // child as sh
   int pid, status;
   pid = fork();
   if (pid){ // sh    
      printf("parent sh %d waits\n", getpid());
      pid = wait(&status);
      printf("parent %d : ZOMBIE child=%d status=%x\n", getpid(), pid, status);
      myexit(0);
   }
   else{ // child of sh
       printf("child sh %d running, exec to /bin/u2\n", getpid());
       exec("u2 see xiahua again");
       // should not see this
       myexit(123);
   }
}


