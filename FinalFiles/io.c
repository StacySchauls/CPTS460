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

/***********************************************************************
                      io.c file of MTX
***********************************************************************/
#include "include.h"
/*********
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;
***********/
char *ctable = "0123456789ABCDEF";

void align(), printi(), prints();


int putc();

/*
#define LINES	25
#define COLUMNS	80
#define TAB_WIDTH	8	
*/
void align(u32 x)
{
  int count;
  count = 10;
  if (x==0) 
     count = 9;
  while (x){
    count--;
    x = (u32)(x/10);
  }

  while(count){
    putc(' ');
    count--;
  }
}

void rpi(int x)
{
   char c;
   if (x==0) return;
   c = ctable[x%10];
   rpi((int)x/10);
   putc(c);
}
  
void printi(int x)
{
    if (x==0){
       prints("0 ");
       return;
    }
    if (x < 0){
       putc('-');
       x = -x;
    }
    rpi((int)x);
    putc(' ');
}

void rpu(u32 x)
{
   char c;
   if (x==0) return;
   c = ctable[x%10];
   rpi((u32)x/10);
   putc(c);
}

void printu(u32 x)
{
    if (x==0){
       prints("0 ");
       return;
    }
    rpu((u32)x);
    putc(' ');
}

void rpx(u32 x)
{
   char c;
   if (x==0) return;
   c = ctable[x%16];
   rpx((u32)x/16);
   putc(c);
}

void printx(u32 x)
{  
  prints("0x");
   if (x==0){
      prints("0 ");
      return;
   }
   rpx((u32)x);
  putc(' ');
}

void prints(char *s)
{
   while (*s){
      putc(*s);
      s++;
   }
}

int printk(char *fmt,...)
{
  char *cp;
  int  *ip;
 
  cp = (char *)fmt;
  ip = (int *)&fmt + 1;

  while (*cp){
    if (*cp != '%'){
      putc(*cp);
      if (*cp=='\n')
	putc('\r');
      cp++;
      continue;
    }
    cp++;
    switch(*cp){
      case 'd' : printi(*ip); break;
      case 'u' : printu(*ip); break;
      case 'x' : printx(*ip); break;
      case 's' : prints((char *)*ip); break;
      case 'c' : putc(*ip);   break;
    }
    cp++; ip++;
  }
  return 1;
}
