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

#include "uinclude.h"

char ans[16], any[16];
int pc, bp;
int mainpc;

int setjmp()
{
  int *p;
  p = (int *)&p;
  bp = *(p+1);
  pc = *(p+2);
  return 0;
}

int longjmp()
{
  int *p;
  p = (int *)&p;

  *(p+1) = bp;
  *(p+2) = pc;

  return 1;
}

void catcher(sig) int sig;
{
  printf("in catcher : signal# = %d OLYMPIC long jump!\n",sig);
  longjmp();
}  

int main()
{
  int r;

  printf("testing segmentation error\n");
  printf("install catcher ? (y|n) : ");
  gets(ans);

  if (strcmp(ans, "y")==0){
     signal(11, catcher);  // in protected mode, segmenatation signal = 11
     printf("catcher installed\n");
  }

  r = setjmp();
  if (r==0)
     seg_fault();
  else{
     printf("Amazing! YOU survived segmentation fault!\n");     
     exit(0);  // KCW: must exit() directly rather than return to u.c
  }
}

    
int seg_fault()
{
    int *p;
    printf("try to access invalid address\n");
    p = (int *)0x10000000;
    *p = 100;
    return 0;
}

