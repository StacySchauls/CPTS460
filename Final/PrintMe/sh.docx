#include "ucode.c"

/*
ALGORITHM TO USE

get a command
get command token
if command == "built in" command, do it directly 

for binary excutable commad:
fork child, look for '&' if there is none, we wait. 
if there is, we do a pipe for the command

FOR PIPE:
pipe function takes cmdine and and int pd
if (pd) //if has a pie passed in, as WRITER, on pipe pd, close pd[0]; duo2(pd[1],1); close pd[1];

divide the command line into head, tail, by the rightmost pipe symbol
chek if haspipe, if it does, create pipe, fork a child, make parent pid as reader on the new pipe, close new pipe 1, dupe 0, close 0
then do the tail command.

else, do the command


do_command (cmdline)
scan cmdline for i/o redirection symbols
do i/o redirection
make head = cmdline BEFORE doig redirections
exec(head)


scan(cmdline, head, tail)
divide cmdline into head tail by rightmost | symbol
cmdline =cmd1 | cmd2 | cmd.... |


*/
#define BLK 1024

char *name[16], components[64];
int num;
int nowait;
char buf[1024];
int color = 0x00C;

int main(int argc, char *argv[])
{
  int pid, status, i;
  char buf[256], tbuf[256], *cp, *cq;

  signal(2, 1); /* ignore signal#2: Control-C interrupts */

  color = getpid() + 0x000A;
  printf("Stacy's Shell %d\n", getpid());
  //printf("sh %d running\n", getpid());

  while (1)
  {
    printf("Stacys_Sh #%d ", getpid());

    gets(buf); //get command

    if (buf[0] == 0)
      continue;

    cp = buf;
    while (*cp == ' ') // skip leading blanums
      cp++;

    cq = cp;
    while (*cq) // zero our trailing blanums
      cq++;
    cq--;
    while (*cq == ' ')
    {
      *cq = 0;
      cq--;
    }

    //printf("input=%s\n", buf);

    if (strcmp(cp, "") == 0) // if nothing or a bunch of spaces
      continue;

    strcpy(tbuf, cp);
    strcpy(buf, tbuf);
    //printf("input=%s\n", buf);

    strcpy(tbuf, buf);

    num = eatpath(tbuf, name);

    nowait = 0;

    if (num > 1)
    {
      if (strcmp(name[num - 1], "&") == 0)
      {
        // must delete & from buf[ ]
        cp = buf;
        while (*cp)
          cp++; // cp to end to buf
        while (*cp != ' ')
          cp--;  // cp back to space
        *cp = 0; // delete & from buf[ ] end

        num--;
        nowait = 1;
      }
    }

    //build in commands

    if (strcmp(name[0], "cd") == 0)
    {
      if (name[1] == 0)
        chdir("/");
      else
        chdir(name[1]);
      continue;
    }

    if (strcmp(name[0], "pwd") == 0)
    {
      pwd();
      continue;
    }

    /* chname must be done by sh itself */
    if (strcmp(name[0], "chname") == 0)
    {
      //printf("sh chname to %s\n", cp);
      chname(name[1]);
      continue;
    }

    if (strcmp(name[0], "logout") == 0)
    {
      printf("Logging out.. Goodbye\n");
      exit(0);
    }

    if (strcmp(name[0], "exit") == 0)
    {
      exit(0);
      continue;
    }

    //if not a trivial command like the one one above, sh forks a child to do the command

    printf("parent sh %d: forks a child\n", getpid());

    pid = fork(); /* sh forks child */

    if (pid)
    { /* parent sh */

      if (nowait)
      {
        nowait = 0;
        tswitch();
        continue;
      }
      else
      {
        printf("parent sh %d: wait for child %d to die\n", getpid(), pid);
        pid = wait(&status);
        printf("sh %d: child %d exit status = %x\n", getpid(), pid, status);
        continue;
      }
    }
    else
    {

      printf("child sh %d running : cmd=%s\n", getpid(), buf);
      do_pipe(buf, 0);
    }
  }
}

//divides command into head and tail based off rightmost |
int scan(buf, tail) char *buf; char **tail;
{
  char *p;

  p = buf;
  *tail = 0;

  while (*p) // scan to buf end line
    p++;

  while (p != buf && *p != '|') // scan backward until |, to get the rightmost |
    p--;

  if (p == buf) // no | was found
    return 0;

  *p = 0;           // change location of | to NULL
  p++;              // move p right by 1
  while (*p == ' ') // skip over any blanums
    p++;

  *tail = p; // change tail pointer to p

  return 1; // head points at buf; return head
}

int do_pipe(char *buf, int *rpd)
{
  int hasPipe, pid;
  char *tail;
  int lpd[2];

  if (rpd)
  { //if there was a pipe passed in
    // as writer on RIGHT side pipe
    close(rpd[0]);
    close(1);
    dup(rpd[1]);
    close(rpd[1]);
  }

  //scan for a pipe
  hasPipe = scan(buf, &tail);

  //if it has a pipe
  if (hasPipe)
  {
    if (pipe(lpd) < 0)
    { // create LEFT side pipe
      printf("proc %d pipe call failed\n", getpid());
      exit(1);
    }
    
    //fork a child to execute command
    pid = fork();

    if (pid < 0)
    {
      printf("proc %d fork failed\n", getpid());
      exit(1);
    }


    //make parent the reader on the left side of the pipe
    if (pid)
    { 
      close(lpd[1]);
      close(0);
      dup(lpd[0]);
      close(lpd[0]);
      //printf("proc %d exec %s\n", getpid(), tail);
      command(tail);
    }
    else
    { // child gets LEFT pipe as its RIGHT pipe
      do_pipe(buf, lpd);
    }
  }
  else
  { // no pipe symbol in string must be the leftmost cmd
    command(buf);
  }
  return 1;
}

//exec the command. look for io redirect and such
int command(char *s)
{
  char *name[16], tbuf[64];
  int i, j, num, val;
  char cmdline[64];

  strcpy(tbuf, s);
  num = eatpath(tbuf, name);

  val = num;

  //scan command line for io redirect sumbols, < > << >>
  for (i = 0; i < num; i++)
  {
    if (strcmp(name[i], "<") == 0)
    {
      printf("proc %d redirect input from %s\n", getpid(), name[i + 1]);
      if (val > i)
        val = i; // val = index of first < or > or >>
      if (name[i + 1] == 0)
      {
        printf("Error in < input\n\r");
        exit(1);
      }
      close(0);
      if (open(name[i + 1], 0) < 0)
      {
        printf("Error opening input file\n");
        exit(2);
      }
      break;
    }
  }
  for (i = 0; i < num; i++)
  {
    if (strcmp(name[i], ">") == 0)
    {
      printf("proc %d redirect outout to %s\n", getpid(), name[i + 1]);
      if (val > i)
        val = i; // val = index of first > or < or >>
      if (name[i + 1] == 0)
      {
        printf("invalid > in command line\n\r");
        exit(3);
      }
      close(1);
      open(name[i + 1], O_WRONLY | O_CREAT);
      break;
    }
  }
  for (i = 0; i < num; i++)
  {
    if (strcmp(name[i], ">>") == 0)
    {
      printf("proc %d append output to %s\n", getpid(), name[i + 1]);
      if (val > i)
        val = i;
      if (name[i + 1] == 0)
      {
        printf("invalid >> in command line\n\r");
        exit(4);
      }
      close(1);
      open(name[i + 1], O_WRONLY | O_CREAT | O_APPEND);
      break;
    }
  }
  //printf("after val/O redirection ");

  strcpy(cmdline, name[0]);
  //printf("cmdline=%s val=%d ", cmdline, val);

  for (j = 1; j < val; j++)
  {
    strcat(cmdline, " ");
    strcat(cmdline, name[j]);
  }

  if (exec(cmdline) < 0)
    exit(1);
  return 1;
}
