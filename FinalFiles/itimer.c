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

/*************************************************************************
             timerq demo the timer queue in Kernel
 tasks may request timer intervals t, which are maintained in a timerQ
 ordered by tiem to expire relative to the sum of those in fornt.
 Task goes to TIMER mode (effectively SLEEP). When t expires, clock handler
 makes it ready again
 To test: login several users; run timerq in each sh ==> see timerQ
************************************************************************/
#include "ucode.c"

int t,i,j,k;
void catcher(int sig)
{
  printf("catcher in Umode sig=%d\n", sig);
  signal(14, catcher);
  itimer(2);
}

int main(int argc, char *argv[])
{
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\r");
    printf("        This is KC's %s in action\n", argv[0]);
    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\r");

    if (argc < 2){
      printf("Usage: itimer seconds\n"); exit(1);
    }
    printf("install itimer catcher? [y|n] ");

    if (getc()=='y')
       signal(14, catcher);
    printf("\n");
    t = atoi(argv[1]);

    printf("itimer %d ", t); 
    itimer(t);          // call kitimer() in Kernel

    printf("looping until SIGALRM ....\n");

    while(1);
}

             
