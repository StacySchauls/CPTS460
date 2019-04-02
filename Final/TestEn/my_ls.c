#include "ucode.c"
#include "type.h"
//funciton to ls
int do_ls(char *path)
{

  unsigned long ino;
  MINODE *mip, *pip;
  int device = running->cwd->dev;
  char *child;

  // if there was no additional argument, print the cwd
  if(path[0] == 0)
  {
    mip = iget(device, running->cwd->ino);

    printChild(device, mip);

  }
  // otherwise...
  else
  {
    // if we're to print the root, change device to it
    if(path[0] == '/')
    {
      device = root->dev;
    }
    // get the inode for the current path part

    ino = getino(device, path);

    // pathname doesn't exist
    if( 0 >= ino){	return 1;}

    mip = iget(device, ino);

    // if we're not looking at a directory...
    if(((mip->INODE.i_mode) & 0040000)!= 0040000)
    {
      // find the parent of the path part and get its's basename
      if(findparent(path))
        child = basename(pathname);
      // if it doesn't exist, get the name of the child path
      else
      {
        child = (char *)malloc((strlen(pathname) + 1) * sizeof(char));
        strcpy(child, path);
      }
      // print the child path
      printFile(mip, child);
      return 0;
    }

    // print child part
    printChild(device, mip);
  }

  iput(mip->dev, mip);
  return 0;
}

// print information on a file
void printFile(MINODE *mip, char *namebuf)
{
  char *Time;
  unsigned short mode;
  int type;

  mode = mip->INODE.i_mode;

  // print out info in the file in same format as ls -l in linux
  // print the file type
  if((mode & 0120000) == 0120000)
  {
    printf("l");
    type = LINK;
  }
  else if((mode & 0040000) == 0040000)
  {
    printf("d");
    type = DIRECTORY;
  }
  else if((mode & 0100000) == 0100000)
  {
    printf("-");
    type = FILE;
  }

  // print the permissions
  // uses bitwise and to check each byte in the mode.
  if((mode & (1 << 8)))
    printf("r");
  else
    printf("-");
  if((mode & (1 << 7)) )
    printf("w");
  else
    printf("-");
  if((mode & (1 << 6)) )
    printf("x");
  else
    printf("-");

  if((mode & (1 << 5)) )
    printf("r");
  else
    printf("-");
  if((mode & ( 1 << 4)) )
    printf("w");
  else
    printf("-");
  if((mode & (1 << 3)) )
    printf("x");
  else
    printf("-");
  if((mode & (1 << 2)) )
    printf("r");
  else
    printf("-");
  if((mode & (1 << 1)) )
    printf("w");
  else
    printf("-");
  if(mode & 1)
    printf("x");
  else
    printf("-");

  // print the file info
  printf("\t%d\t%d\t%d\t", mip->INODE.i_links_count, mip->INODE.i_size, mip->ino);
  Time = ctime( (const time_t *) &(mip->INODE.i_mtime));
  Time[strlen(Time) -1 ] = 0;
  printf("%s\t%s\t", Time, namebuf);
  

  // if this is a symlink file, show the file it points to
  if((mode & 0120000) == 0120000)
    printf(" => %s\n",(char *)(mip->INODE.i_block));
  else
    printf("\n");

  iput(mip->dev, mip); // write back to disk
}

// print contents of child directory
void printChild(int devicename, MINODE *mp)
{
  char buf[BLKSIZE], namebuf[256], *cp;
  DIR *dp;
  int i, ino;
  MINODE *temp;

  // cycle through direct blocks and print them
  for(i = 0; i < 12; i++)
  {

    if(mp->INODE.i_block[i])
    {
      get_block(devicename, mp->INODE.i_block[i], buf);
      cp = buf;
      dp = (DIR *)buf;

      while(cp < &buf[BLKSIZE])
      {

        strncpy(namebuf, dp->name, dp->name_len);
        namebuf[dp->name_len] = 0;

        ino = dp->inode;
        temp = iget(devicename, ino);

        printFile(temp, namebuf);

        cp+=dp->rec_len;
        dp = (DIR *)cp;
      }
    }
  }

}

// checks if there is a parent by looking for a '/'
int findparent(char *pathn)
{
  int i = 0;
  while(i < strlen(pathn))
  {
    if(pathn[i] == '/')
      return 1;
    i++;
  }
  return 0;
}
