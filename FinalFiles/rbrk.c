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

int sbrk();
char ans[16];
char *s = "this is a test string\n";
char *cp;
int main()
{
  int r; char c;
  printf("\nthis program demonstrates sbrk() to expand Umode HEAP by page\n");

  r = sbrk();
  printf("r = %x\n", r);
  cp = (char *)r;
  strcpy(cp, s);
  printf("wrote s to %x\n", cp);
  printf("s=%s", cp);

}
