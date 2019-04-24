
#include "ucode.c"

#define printk printf

int console, s0, s1;

//login to 0
void login()
{
  exec("login /dev/tty0");
}
//login to s0
void login1()
{
  exec("login /dev/ttyS0");
}

//login to s1
void login2()
{
  exec("login /dev/ttyS1");
}

//modify book code from singlular tty0 to be able to log into s0 and s1 as well, for each terminal
void parent() //this is P1's code
{
  int pid, status;
  prints("Stacy's_INIT is waiting for ZOMMMBIE!!\n");
  while (1)
  {
    pid = wait(&status);

    if (pid == console) //if console login process died
    {
      prints("Stacy's_INIT forks a new console login\n");
      console = fork();
      if (console)
        continue;
      else
        login();
    }
    if (pid == s0)
    {
      s0 = fork();
      if (s0)
        continue;
      else
        login1();
    }

    printf("Stacy's_INIT: I just buried an orphan child proc %d\n", pid);
  }
}

int main(int argc, char *argv[])
{
  int in, out;
  int pid;
  in = open("/dev/tty0", O_RDONLY);
  out = open("/dev/tty0", O_WRONLY);

  prints("Stacy's_INIT forks a login proc on console\n");
  console = fork();
  if (console) //this is the parent
  {

    prints("Stacy_INIT forks login on ttyS0\n");
    s0 = fork();
    if (s0) //s0 the parent
    {
      parent();
    }
    else
    {
      login1(); //child login on s0
    }
  }
  else //chil ecec to login on tty0
  {
    login();
  }
}
