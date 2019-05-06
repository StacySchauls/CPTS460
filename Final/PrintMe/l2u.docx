
#include "ucode.c"

int main(int argc, char *argv[])
{
  int fd, f2d, n, c;
  char buf[1024], *cp;

  print2f("Stacy's l2u program\n");

  //show the arguments
  for (n = 0; n < argc; n++)
    printf("%s ", argv[n]);
  printf("\n");


//if argc is one then we are getting stdin
  if (argc == 1)
  {
    while ((c = getc()) != EOF)
    {
      //
      c &= 0x7F;
      if (c >= 'a' && c <= 'z') //if its a valid char
      {
        mputc(c - 'a' + 'A'); //convert it to it's upper-case corrosponding letter, write it to the stdin
        /*This is basically saying acii value c - 97 + 65 (or something like that. Icant remember the actual values)
        but this gives us the upper case value. */
      }
      else
        mputc(c); //if its not a letter then just write is as usual

      if (c == '\r')//write a new line
        mputc('\n');
    }
    exit(0);
  }


  if (argc < 3) //error u dummy you didnt read the proper way to use it
  {
    print2f("usage : l2u f1 f2\n");
    exit(1);
  }


  //Here we are opening the file for read only
  fd = open(argv[1], O_RDONLY);
  if (fd < 0)
  {
    exit(1);
  }

  //we are opening the second file fo rread only
  f2d = open(argv[2], O_WRONLY | O_CREAT);

  //basically same as aabove. read the lines, convert to upper, write back to file

  while (n = read(fd, buf, 1024))
  {
    cp = buf;
    while (cp < buf + n)
    {
      if (*cp >= 'a' && *cp <= 'z')
      {
        *cp = *cp - 'a' + 'A';
      }
      cp++;
    }
    write(f2d, buf, n);
  }
  print2f("Stacy's l2u complete!\n");
}
