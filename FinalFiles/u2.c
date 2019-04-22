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

main(int argc, char *argv[ ])
{
  int a,b,c, pid, ppid, mode, r, cmd, usp;
  char name[64];
  int i;

  mode = getcsr();
  mode = mode & (0x0000001F);
  printf("CPU mode=%x argc=%d\n", mode, argc);
  for (i=0; i<argc; i++){
    printf("argv[%d] = %s\n", i, argv[i]);
  }
  a = 123; b = 234; c = 345;
  /*
  mode = getcsr();
  mode = mode & (0x0000001F);
  printf("CPU MODE=%x\n", mode);
  */
  pid = getpid();
  ppid = getppid();
  usp = ugetusp();
  //printf("AFTER getpid() SYSCALL PID =%d PPID =%d usp = %x\n", pid,ppid,usp);
  //printf("proc %d in Umode, mysp=%x usp=%x\n", pid, getmysp(), ugetusp());
  
  while(1){
     pid = getpid();
     ppid = getppid();

     printf("DAS IST PROZESS %d IN USER-MODUS, MEIN VATER=%d\n", pid, ppid);
     show_menu();
  
     printf("BEFEHL? : ");
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
