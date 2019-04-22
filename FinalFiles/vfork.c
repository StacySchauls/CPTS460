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

int vfork();

int main()
{
  int  pid, status, r;
  char cmd[64];

  printf("\nthis program demonstrates vfork()\n");
  pid = vfork();

  if (pid){
      printf("parent %d waits\n", getpid()); 
      pid = wait(&status);
      printf("parent %d after wait child exit status=%x\n", getpid(), status); 
  }
  else{
      printf("this is the vforked child %d\n", getpid());
      printf("input a command to execute: ");
      gets(cmd);
      r = exec(cmd);
      printf("exec failed! vforked %d exit\n", getpid());
      exit(1);
  }
}         
