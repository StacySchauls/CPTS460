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

char tline[128];

main(int argc, char *argv[ ])
{
  int i, r;
  printf("this is a test\n");
  for (i=0; i<argc; i++)
    printf("argv[%d] = %s\n", i, argv[i]);
  if (argc > 1){
    strcpy(tline, argv[1]);
    for (i=2; i<argc; i++){
      strcat(tline, " ");
      strcat(tline, argv[i]);
    }
    r = exec(tline);
    if (r<0)
      printf("exec %s failed\n", tline);
  }
}
