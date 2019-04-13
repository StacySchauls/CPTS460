/********** test.c file *************/
#include "ucode.c"

int main(int argc, char *argv[ ])
{
  int src, dest, i;
  char buf[256];
  prints("\nTHIS STACY's COPY\n");
  if(argc < 3)
  {
      printf("Error Usage: cp src dest\n");
      return -1;
  }

  //get the files and open them
  src = open(argv[1], O_RDONLY);
  dest = open(argv[2], O_WRONLY | O_CREAT);

  while((i = read(src, buf, 256)) > 0)
  {
      write(dest, buf, i);
  }

  //close the files
close(src);
close(dest);
return 0;
}