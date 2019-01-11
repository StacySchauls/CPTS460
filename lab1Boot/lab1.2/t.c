#include <string.h>
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

#define TRK 18
#define CYL 36
#define BLK 1024

#include "ext2.h"
typedef struct ext2_group_desc  GD;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;
GD    *gp;
INODE *ip;
DIR   *dp;
char *cp;
char buf1[BLK], buf2[BLK];
//int color = 0x0A;
u8 ino;
/*prototypes*/
int prints(char *s);
int gets(char s[]);

main()
{ 
  u16    i, iblk;
  char   c, temp[64];

  prints("read block# 2 (GD)\n\r");
  getblk(2, buf1);

// 1. WRITE YOUR CODE to get iblk = bg_inode_table block number
  gp = (GD *)buf1;
  iblk = (u16)gp->bg_inode_table;
  prints("inode_block="); putc(iblk+'0'); prints("\n\r"); 
  getc();

  //change color for funsies

// 2. WRITE YOUR CODE to get root inode
  ip = (INODE *)buf1 + 1;
  prints("read inodes begin block to get root inode\n\r");
  getblk(iblk, buf1);
  prints("read data block of root DIR\n\r");
 // 3. WRITE YOUR CODE to step through the data block of root inode
   for(i = 0; i<12; i++)
   {
     if((u16)ip->i_block[i])
     {
        //prints("getting directory for block:"); putc(i); prints("\n");
        getblk((u16)ip->i_block[i],buf2);
        dp = (DIR *)buf2;
        while((char *)dp<&buf2[1024])
        {
            memset(temp,0,64);
            //prints(dp->name); putc(' ');
            strncpy(temp, dp->name, dp->name_len);
            prints(temp); prints("\n\r"); getc(); 
            dp = (DIR *)((char *)dp + dp->rec_len);
        }
     }
   }

  prints("All done. \n\r");
}
int prints(char *s)
{
  while(*s) putc(*s++);
}


int gets(char s[])
{

  while((*s = getc()) != '\r') putc(*s++);
  *s = 0;
}


int getblk(u16 blk, char *buf)
{
  // readfd( (2*blk)/CYL, ( (2*blk)%CYL)/TRK, ((2*blk)%CYL)%TRK, buf);
  readfd( blk/18, ((blk)%18)/9, ( ((blk)%18)%9)<<1, buf);
}
