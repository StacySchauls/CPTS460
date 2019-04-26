/********** test.c file *************/
#include "ucode.c"

int main(int argc, char *argv[ ])
{
  int i;
  char buf[1024];
  int pid = getpid();
  
  print2f("+++++++++++++++++++++++++++++\n\r");
  print2f("STACY'S CAT PROGRAM >>MEOW<<\n\r");
  print2f("+++++++++++++++++++++++++++++\n\r");

  char c, lc = 0;
  int fd;
  char mybuf[1024];
  //if there is noinput then we read from stnadard in. Set fd to 0
  if(argc == 1){
    fd = 0;
    while (gets(mybuf))
    {
      
        print2f(mybuf);
      
        print2f("\n\r");
      
    }
    exit(0);
  }else{
    if (argc < 2){
      while(gets(mybuf)){
        print2f(mybuf);
        print2f("\n\r");
      }
      exit(0);
    }
  }




  {
    fd = open(argv[1], O_RDONLY);
    
  }

  //check the fd

  if(fd < 0){
    print2f("Could not fine file to cat.\n");
    exit(0);
  }

  //read the input
  while( read(fd, buf, 1024))
  {
    printf("%s", buf);
  }
  //cat done
  close(fd);
  exit(0);
  
}
