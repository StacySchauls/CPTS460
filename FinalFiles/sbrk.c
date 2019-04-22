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

int sbrk();
char ans[16];
char *s = "this is a test string\n";
char *cp, c;
int main()
{
  int r; 
  printf("demonstrates sbrk() to expand Umode HEAP by page size\n");

  r = sbrk();
  printf("r = %x\n", r);
  cp = (char *)r;
  strcpy(cp, s);
  printf("wrote s to %x\n", cp);

  printf("s=%s", cp);
  cp += 4000;
  strcpy(cp, s);
  printf("wrote s to %x\n", cp);
  printf("s=%s", cp);

  printf("expand heap one more page? [y|n]: ");
  if ( (c = getc()) == 'y')
    sbrk();

  printf("try to access address beyond expanded page at VA=%x\n", r+4096);
  cp = (char *)r + 4096;
  strcpy(cp, s);
  printf("wrote s to %x\n", cp);
  printf("s=%s", cp);
}
