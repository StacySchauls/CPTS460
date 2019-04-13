/********** test.c file *************/
#include "ucode.c"

int main(int argc, char *argv[ ])
{
  int i;

  int pid = getpid();
  printf("STACY'S CAT PROGRAM >>MEOW<<\n", pid);

  char c, lc = 0;
  int fd;
  
  //if there is noinput then we read from stnadard in. Set fd to 0
  if(argc == 1){
    fd = 0;
  }
  else{
    fd = open(argv[1], O_RDONLY);
  }

  //check the fd

  if(fd < 0){
    printf("Could not fine file to cat.\n");
    return -1;
  }

  //read the input
  while( read(fd, &c, 1) > 0)
  {
    printc(c);
    //check the new line chars
    if(fd == 0)
    {
      if(c == '\n' && (lc != '\n' && lc != '\r'))
        printc('\r');
    }//else if we're reading from stdin we look for the return chars
    else
    {
      if(c == '\r' && (lc != '\n' && lc != '\r'))
      {
        printc('\n');
        printc('\r');
      }
    }
    lc = c;
  }
  //cat done
  printf("\n");
  close(fd);
  return 1;
  
}
