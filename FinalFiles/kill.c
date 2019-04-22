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

int pid, sig;
char *cp;

main(int argc, char *argv[ ])
{
  /****************
  int i;
  for (i=0; i<argc; i++)
       printf("argc[%d]=%s\n",i, argv[i]);
  ******************/
   if (argc<2){
      printf("usage : kill [-s SIGNAL#]  pid\n");
      exit(1);   
   }
   if (argc==2){ // kill pid ==> signal#=9
       pid = atoi(argv[1]);
       kill(9, pid, 0);
   }
   // kill -s signal# pid
  
   if (strcmp(argv[1],"-s")){
      printf("usage : kill -s SIGNAL#  pid\n");
      exit(2);
   }
   if (argc < 4){
      printf("usage : kill -s SIGNAL#  pid\n");
      exit(3);
   }
   sig = atoi(argv[2]);
   pid = atoi(argv[3]);

   // printf("sig=%d pid=%d\n", sig, pid); getc();

   kill(sig, pid);
}

