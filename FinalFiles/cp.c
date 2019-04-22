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

/********* cp.c file ***************/

#include "ucode.c"

//void putchar(const char c){ }

int fd, gd, n, count;
char buf[1024], dummy=0;

int main(int argc, char *argv[ ])
{  
  if (argc < 3){
    printf("Usage: cp src dest\n");
    exit(1);
  }
  fd = open(argv[1], O_RDONLY);
  if (fd < 0){
    printf("open src %s error\n", argv[1]);
    exit(2);
  }

  gd = open(argv[2], O_WRONLY|O_CREAT);
  if (gd < 0){
    printf("open dest %s error\n", argv[2]);
    exit(2);
  }
  dummy=0;
  count = 0;
  while( (n=read(fd, buf, 1024))){
    printf("n=%d ", n);
    write(gd, buf, n);
    count += n;
  }
  printf("%d bytes copied\n", count);
}

