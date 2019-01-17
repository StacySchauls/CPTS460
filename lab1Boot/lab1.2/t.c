typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

//#define TRK 18
//#define CYL 36
#define BLK 1024

#include "ext2.h"
typedef struct ext2_group_desc  GD;
typedef struct ext2_inode       INODE;
typedef struct ext2_dir_entry_2 DIR;
GD *gp;
DIR *dp;
INODE *ip;
char buf1[BLK], buf2[BLK];
u8 ino;
int i;

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
  readfd( (2*blk)/36, ( (2*blk)%36)/18, ((2*blk)%36)%18, buf);
}

u16 search(INODE *ip, char *name)
{
  char c;
  for(i=0; i<12; i++)
  {
    if((u16)ip->i_block[i])
    {

      getblk((u16)ip->i_block[i],buf2);
      dp = (DIR *)buf2;

      while((char*)dp < buf2 + 1024)
      {
        //c = dp->name[dp->name_len]; //saves the last byte
        dp->name[dp->name_len] = 0; //makes name into a string
        //prints(dp->name); putc(' '); //show the name
        if(!strcmp(dp->name, name))
        {
          return (u16)dp->inode;
        }
        //dp->name[dp->name_len] = c; //restores the last byte
        dp = (char *)dp + dp->rec_len;
      }
    }
  }
  error(); //error if cant find the file name
}

main()
{
  u16    i, iblk;
  u32 *up;
  char *name[2];
  name[0] = "boot";
  name[1] = "mtx";

  getblk(2, buf1);
  gp = (GD *)buf1;
  iblk = (u16)gp->bg_inode_table;
  //prints("inode_block="); putc(iblk+'0'); prints("\n\r"); 

  ip = (INODE *)buf1 + 1;

  getblk(iblk, buf1);

  //getc();
  for(i = 0; i<2; i++)   //look through the blocks searching for the system name
  {
    ino = search(ip, name[i]) - 1;
    if(ino < 0) error(); //couldnt find
    getblk(iblk+(ino/8), buf1);
    ip = (INODE *)buf1 + (ino % 8);
  }

  if((u16)ip->i_block[12]) //read indirect block into buf2, if there is anything there
  {
    getblk((u16)ip->i_block[12], buf2);
  }

  setes(0x1000);  //set ES to loading segment
  for(i=0; i<12; i++) //load the direct blocks
  {
    getblk((u16)ip->i_block[i], 0);
    inces(); //putc('*');
  }


  if((u16)ip->i_block[12]) //load the indirect blocks if any
  {
    up = (u32 *)buf2;
    while(*up)
    {
      getblk((u16)*up, 0);
      inces(); //putc('*');
      up++;
    }
  }
  //prints("Ready?");
  //getc();
}


