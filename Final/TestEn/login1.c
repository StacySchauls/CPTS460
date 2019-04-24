#include "strtok.c"
#include "ucode.c"
//#include "strtok.c"
char *tty;
int stdin, stdout, stderr;
int checkCreds(char user[], char pass[]);
char uname[64], home[64], program[64];
int uid, gid;

int main(int argc, char *argv[])
{
    char user[64], pass[64];
    char *tokens[10];
    tty = argv[1];
    char *token, *dl = ":", tmp[64], buffer[1024];

    //close stdin stdout, stderr
    close(0); close(1); close(2);
    //set new ones
    stdin = open(tty, 0);
    stdout = open(tty, 1);
    stderr = open(tty, 2);

    settty(tty);

    printf("Welcome to Stacy's login. Opened %s as stdin stdout stderror.\n", tty);
    int file =  open("/etc/passwd", O_RDONLY);
    if(file == 0){
        prints("Error opening file\n");
        return 0;
    }
    

    while(1)
    {
        printf("UUU: ");
        gets(user);
        printf("Password: ");
        gets(pass);

        if(read(file, buffer, 1024) < 0)
        {
            prints("Error: cant read password file\n");
            return 0;
        }else{
            prints("reading file\n");
        }

        prints("buffer is\n");
        prints(buffer);
        prints("\n");


        strtok(buffer, tokens, ":");
        printf("user: %s\ttok0: %s\tpass: %s\t tok1: %s\n",user,tokens[0],pass,token[1]);

        if((!strcmp(user, tokens[0]) && !strcmp(pass, tokens[1]) == 0))
        {
            prints("YAY?\n");
            gid = atoi(tokens[2]);
            uid = atoi(tokens[3]);
            strcpy(name, tokens[4]);
            strcpy(home, tokens[5]);
            strcpy(program, tokens[6]);
            chdir(home);
            exec(program);
        }else{
            prints("Error in login\n");
        }

        //token = strtok(buffer, dl);
        //prints("token is\n");
        //prints(token);

        /*
        while(token != null)
        {
            prints("\ntoken is ");
            prints( token);

            if(!strcmp(token, user))
            {
                prints("\ntoken matches username\n");
                token = strtok(null, dl);

                if(!strcmp(token, pass))
                {
                    uid = atoi(strtok(null, dl));       // grab uid
                    gid = atoi(strtok(null, dl));       // grab gid
                    strcpy(uname, strtok(null, dl));     // grab username
                    strcpy(name, user);
                    strcpy(home, strtok(null, dl));     // grab home directory
                    strcpy(program, strtok(null, dl));  // grab usershell

                    printf("Welcome, %s\n", user);
                    chuid(uid, gid);
                    chdir(home);
                    exec(program);
                    close(file);

                }
            }
            token = strtok(null, dl);
        }
        */
        close(file);
        printf("Login failed.\n");
    }
    printf("exiting?\n");
    exit(1);
}   
