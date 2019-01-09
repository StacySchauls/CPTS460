#include "ext2.h"
int prints(char *s)
{
  while(*s) putc(*s++);
}


int gets(char s[])
{

  while((*s = getc()) != '\r') putc(*s++);
  *s = 0;
}

u16 getblk(u16 blk, char buf[ ])
{
  //convert the blk to CHS
  readfd(blk/18, (blk/9)%2, (blk*2)%18, buf);
}


main()
{

}


