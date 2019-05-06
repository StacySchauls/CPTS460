
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

//modify book code from singlular tty0 to be able to log into s0 and s1 as well
void parent() //this is P1's code
{
  int pid, status;
  print2f("Stacy's_INIT is waiting for ZOMMMBIE!!\n");
  while (1)
  {
    pid = wait(&status); // wait current process
                        //pther processes steps through the ifs statements
                        //to find what console was waited

    if (pid == console) //if console login process died, fork a new process
    {
      print2f("Stacy's_INIT forks a new console login\n");

      console = fork();

      if (console) //if that process we forked is  console in use, contunue, else prompt a login to tty0
        continue;
      else
        login();
    }

    if (pid == s0) //if the child forked is s0, ttys0, then fork again.
    {
      s0 = fork();

      if (s0) //if s0 exists, continue, 
        continue;
      else    // else prompt login to ttys0
        login1();
    }

    if(pid == s1){ //if pid is s1, fork, again

      s1 = fork();

      if(s1) //if s1 exitst, continue
        continue;
      else
        login2(); //else, prompt login to ttys1
    }

    print2f("Stacy's_INIT: I just buried an orphan child proc ");
    print2f(pid);
  }
}

int main(int argc, char *argv[])
{
  int in, out;
  int pid;
  in = open("/dev/tty0", O_RDONLY); // open In and Out, as qemu console we are using
  out = open("/dev/tty0", O_WRONLY);

  print2f("Stacy's_INIT forks a login proc on console\n");

  console = fork(); //fork a process to launch consoles from
  if (console) //this is the parent
  {

    print2f("Stacy_INIT forks login on ttyS0\n");

    s0 = fork(); //fork a process,

    //attempt to login to the other two terminals

    if (s0) //if s0 exists, it is the parent, call parent method, to get a child.
    {
      parent();
    }
    else //if it doesnt exist, we prompt login to s0
    {
      login1(); //child login on s0
    }
  } //if console is not defined, that is the tty0, we prompt login to it.
  else 
  {
    login();
  }
}
