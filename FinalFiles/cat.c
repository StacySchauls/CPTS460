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

char *cp, mytty[64];

char realname[64], linkname[64];

int main(int argc, char *argv[ ])
{
    int fd, n;
    char buf[1244], dummy;

    print2f("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\r");
    print2f("      KC's cool cat MEOW!        \n\r"); 
    print2f("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\r");   

    fd = 0;
    if (argc > 1){
      fd = open(argv[1], O_RDONLY);
      if (fd < 0){
	printf("cat %s error\n", argv[1]);
        exit(0);
      }
    }

    while( (n=read(fd, buf, 1024)) ){
	buf[n] = 0;
        printf("%s", buf);
    }
    close(fd);
    exit(0);
}
