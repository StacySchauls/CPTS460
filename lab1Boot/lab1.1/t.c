int prints(char *s)
{
  while(*s) putc(*s++);
}


int gets(char s[])
{

  while((*s = getc()) != '\r') putc(*s++);
  *s = 0;
}

main()
{
  char name[64];
  prints("Welcome to Stacy's Booter!\n");
  while(1)
  {
    prints("What is your name? ");
    gets(name);
    if(name[0] == 0)
    {
      break;
    }
    prints("\n\rWelcome "); prints(name); prints("\n\r");
  }
  prints("Return to assembly and hang\n\r");

}


