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
int page_out();
int geti()
{
  char s[16];
  gets(s);
  return atoi(s);
}

char *p;
char *s = "testing demand paging";
char buf[1024];

int main()
{
  int n;
  printf("testing DEMAN-PAGING\n");
  printf("input a page number (16-1023): ");
  n = geti();
  n %= 1024; // for simplicity, the first 1024 pages only
  printf("syscall page_out() to mark page %d NOT present\n", n);
  page_out(n);

  printf("\nTRY to access missing page %d\n", n);    
  p = (char *)(n*4096);
  strcpy(p, s);
  strcpy(buf, p);
  buf[1023] = 0;
  printf("buf = %s\n", buf);
}


