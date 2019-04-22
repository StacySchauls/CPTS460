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
  int i, a,b,c, pid, ppid, mode, r, cmd;
 char name[64];
  u32 usp, usp1;
  char line[64]; char uc;

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
  
  while(1){
    pid  = getpid();
    ppid = getppid();

       printf("==============================================\n");
    printf("This is process #%d in Umode at %x my father=%d\n", 
	   pid, getmyaddress(), ppid);
       show_menu();
       printf("Command ? ");
       gets(name); 
       if (name[0]==0) 
           continue;

       cmd = find_cmd(name);

       switch(cmd){
           case 0 : getpid();   break;
           case 1 : ups();       break;
           case 2 : uchname();   break;
           case 3 : ukfork();    break;
           case 4 : uswitch();  break;
           case 5 : uwait();     break;

           case 6 : uexit();     break;
           case 7 : ufork();     break;
           case 8 : uexec();     break;

         default: invalid(name); break;
       } 
  }
}

/**********************
    printf("This is process #%d in Umode at %x my father=%d\n", 
	   pid, getmyaddress(), ppid);
    //printf("mysp=%x\n", getmysp());

    umenu();
    printf("input a command : ");
    ugetline(line); 
    uprintf("\n"); 
 
    if (strcmp(line, "ps")==0)
      ups();
    if (strcmp(line, "chname")==0)
       uchname();
    if (strcmp(line, "kfork")==0)
       ukfork();
    if (strcmp(line, "switch")==0)
       uswitch();
    if (strcmp(line, "exit")==0)
       uexit();

    if (strcmp(line, "wait")==0)
       uwait();
    if (strcmp(line, "fork")==0)
       ufork();
    if (strcmp(line, "exec")==0)
       uexec();

  case 9:  pipe(); break;
       case 10: pfd();  break;
       case 11: read_pipe(); break;
       case 12: write_pipe(); break;
       case 13: close_pipe(); break;

           default: invalid(name); break;
  }
}
******************/
