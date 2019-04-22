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

int main()
{
   printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
   printf("        This is KC's man pages in action\n");
   printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");

   printf("* ===================    USAGE:  ========================== *\n");
   printf("* MTX can boot from and run on x86-based PCs or VMs         *\n");
   printf("* MTX supports multiple user logins with time-sharing       *\n");
   printf("* ===================  COMMANDS: ========================== *\n");
   printf("* login/logout, ls, cd, pwd, ps, whoami, su, lpr, Crtl-C :  *\n");
   printf("* mkdir (rmdir rm cat more) filename     e.g. mkdir /a/b/c  *\n");
   printf("* link, unlink, symlink, cp                                 *\n");
   printf("* grep pattern filename         e.g.  grep printf /a/b/c    *\n");
   printf("* file protection: owner permission only                    *\n");
   printf("* I/O redirection and pipe : <, >, >>, | : as in Unix       *\n");
   printf("* ===================  SYSCALLS: ========================== *\n");
   printf("* fork, exec, wait, open, close, lseek, read, write, creat, *\n");
   printf("* pipe, dup, dup2, signal, kill, catcher : same as in Unix  *\n");
   printf("* ===================  MISC TESTS: ======================== *\n");
   printf("* itimer (in seconds) : interval timer service              *\n");
   printf("* signal : signal handling by user installed catchers       *\n");
   printf("*************************************************************\n");
   exit(0);  
}
