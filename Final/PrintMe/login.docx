#include "ucode.c"
/* ALGORITH FOR login


  upon entry, the first argument, argv[0] = login, argc[1] = /dev/ttyX

  1. close the fie descriptors 0,1,2 inherited by INIT
  2. open argv[1] 3 times as in(0), out(1), err(2)
  3. settty(argv[1]) // sets tty name string in PROC.tty
  4. Open /etc/passwd file for READ
  5.while(1) print login info: username, password, get username nad upass.
    For each line in passwd file do:
      tokenize account line;
  6. if(user hasvalid account):
  7.  change uid,gid, to users uid, gid; chuid
      change cwd to user's home dir;  chdir
      close opened passwd file;     close
      
  8. exec to program in user account;  exec




*/

char buf[1024], username[64], upass[64];
char pline[64], mytty[64], *tokenInfo[8];
char *cp, *delim, *cpp, *delimq;
int gid, uid, i, n;

int in, out, err;
int fd;

char whattty[64];

int main(int argc, char *argv[])
{
  //printf("proc %d in LOGIN: argv[1]=%s\n", getpid(), argv[1]);

  //1. closing file descriptors 0 and 1 2 inherited by INIT

  close(0);
  close(1);
  close(2);
  strcpy(mytty, argv[1]);

  //2. open the argv[1] which is mytty 3 times for in out and err

  in = open(mytty, 0);
  out = open(mytty, 1);
  err = open(mytty, 1);

  //set tty in name string PROC.tty
  settty(mytty);

  // open passwd file for read
  /** open /etc/passwd file to get username's uid, gid, HOME, program **/
  fd = open("/etc/passwd", 0);
  if (fd < 0)
  {
    print2f("Error reading passwd file\n");
    exit(1);
  }

  print2f("Stacy's Login. Welcome!\n");
  printf("Stacy's Login: open %s as stdin=%d, stdout=%d, stderr=%d\n", mytty, in, out, err);

  while (1)
  {
    //prompt the user for username and password
    print2f("Username:");
    gets(username);
    print2f("password:");
    gets(upass);


    //Next we tokenize the password file. This way we can get the uname, passwd, uid, guid, home, and shell program out of it.
    //for each line
    n = read(fd, buf, 2048);//read one line at a time
    buf[n] = 0;

    cp = delim = buf; //set the char pointer to the begining of the line

    //tokenize line
    while (cp < &buf[n])
    {
      while (*delim != '\n') //while we do not see a new line char
      { 
        if (*delim == ' ') //if we find a space, we set delim to a -
          *delim = '-'; // check if it is a space, : or - . if it is we advance, and set that location to null, like normal strtok
        if (*delim == ':')
          *delim = ' ';
        delim++;
      }
      *delim = 0;
      strcpy(pline, cp); //copy the oringinal line into pline
      cpp = delimq = pline; //set a new pointer and new delim
      i = 0;
      while (*delimq)
      {
        if (*delimq == ' ') //look for a space. From the previous section we made a space wherever there was a ':'
        {
          *delimq = 0; //set that spot as null
          tokenInfo[i] = cpp; //for each spot that is a space, that is, was delimited, we place the token into our array,
                              // that array holds the uid, guid, home, shell program
          i++;
          delimq++;
          cpp = delimq;
          continue;
        }
        delimq++;
      }

      //check if the user has a valid acount
      if (strcmp(username, tokenInfo[0]) == 0 && strcmp(upass, tokenInfo[1]) == 0)
      {
        printf("Stacys_Login : Welcome user: %s\n", username);
        printf("Stacys_login : cd to HOME=%s  ", tokenInfo[5]);
        chdir(tokenInfo[5]); // cd to users home dir

        gid = atoi(tokenInfo[2]);
        uid = atoi(tokenInfo[3]);
        //printf("change uid to %d\n", uid);
        chuid(uid, 0); // change gid, uid

        print2f("exec to /bin/sh .....\n");
        close(fd);  //close passwd file
        exec("sh"); //exec to my sh
      }
      delim++;
      cp = delim;
    }
    print2f("login failed, try again\n");
    close(fd);
  }
}
