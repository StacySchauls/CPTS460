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

void catcher(int signal)
{
  printf("in catcher(): signal=%d\n", signal);
  //  while(1);
}

char *p;
int main()
{
  int a,b,c;
  printf("testing divide_by_zero trap\n");
  printf("catcher address=%x\n", (int)catcher);

  /***** install catcher for sign#8 *****/
  signal(8, (int)catcher);

  a=1; b=0;
  c = a/b;
  printf("after divide\n");
}


