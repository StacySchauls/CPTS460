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

#define BLK 1024


/*********************************************
   Use a single sh.c to replace u1.c u2.c
   keep ucode.c as a syscall interface
   Re-write u1.c u2.c as one sh.c, which
      show menu() ==> /bin dir contents
      then ask for a command line, and then for(), exec()
**********************************************/
char buf[1024];
int color = 0x00C;

int main(int argc, char *argv[])
{
  char *name="noname";
  if (argc>1)
    name = argv[1];
  uchname(name);
}

