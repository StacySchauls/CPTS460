#include "ucode.c"

char *tty;
int stdin, stdout, stderr;
int checkCreds(char user[], char pass[]);
char uname[64], home[64], program[64];
int uid, gid;

int main(int argc, char *argv[])
{
    char user[64], pass[64];
    tty = argv[1];

    //close stdin stdout, stderr
    close(0); close(1); close(2);
    //set new ones
    stdin = open(tty, O_RDONLY);
    stdout = open(tty, O_WRONLY);
    stderr = open(tty, 2);

    settty(tty);

    printf("Welcome to Stacy's login. Opened %s as stdin stdout stderror.\n", tty);

    signal(2,1);

    while(1)
    {
        printf("Username: ");
        gets(user);
        printf("Password: ");
        gets(pass);

        if(checkCreds(user, pass) == 1)
        {
            printf("Welcome, %s\n", user);
            chuid(uid, gid);
            chdir(home);
            exec(program);
        }

        printf("Login failed.\n");
    }
    exit(1);
}   


int checkCreds(char *user, char* pass)
{
    int file =  open("/etc/psswd", O_RDONLY);
    char *token, *dl = ":\n", tmp[64], buffer[1024];

    if(file == null)
    {
        printf("Errorr opening password file\n");
        return 0;
    }

    if(read(file, buffer, 1024) < 0)
    {
        printf("Error: cant read password file\n");
        return 0;
    }

    token = strtok(buffer, dl);
    while(token != null)
    {
        if(!strcmp(token, user))
        {
            token = strtok(null, dl);

            if(!strcmp(token, pass))
            {
                uid = atoi(strtok(null, dl));       // grab uid
                gid = atoi(strtok(null, dl));       // grab gid
                strcpy(uname, strtok(null, dl));     // grab username
                strcpy(name, user);
                strcpy(home, strtok(null, dl));     // grab home directory
                strcpy(program, strtok(null, dl));  // grab usershell

                close(file);
                return 1;
            }
        }
        token = strtok(null, dl);
    }
    close(file);
    return 0;
}