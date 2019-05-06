#include "ucode.c"

#define BLK 1024
#define OWNER 000700
#define GROUP 000070
#define OTHER 000007

STAT utat, *sp;
int fd, n;
DIR *dp;
char f[32], cwdname[64], file[64];
char buf[1024];

DIR *dp;
char *cp;

void ls_file(STAT *sp, char *name, char *path)
{
    u16 mode;
    int k, len;
    char fullname[32], linkname[60];


    //get the mode of whatever we are stat-ing
    mode = sp->st_mode;

    //check the mode
    if ((mode & 0xF000) == 0x4000) //print file type as d
        mputc('d');

    if ((mode & 0xF000) == 0xA000) //print file type as s
        mputc('s');
    else if ((mode & 0xF000) == 0x8000) //print file type as -
        mputc('-');


    // uses bitwise and to check each byte in the mode.

    if ((mode & (1 << 8)))
        mputc('r');
    else
        mputc('-');
    if ((mode & (1 << 7)))
        mputc('w');
    else
        mputc('-');
    if ((mode & (1 << 6)))
        mputc('x');
    else
        mputc('-');

    if ((mode & (1 << 5)))
        mputc('r');
    else
        mputc('-');
    if ((mode & (1 << 4)))
        mputc('w');
    else
        mputc('-');
    if ((mode & (1 << 3)))
        mputc('x');
    else
        mputc('-');
    if ((mode & (1 << 2)))
        mputc('r');
    else
        mputc('-');
    if ((mode & (1 << 1)))
        mputc('w');
    else
        mputc('-');
    if (mode & 1)
        mputc('x');
    else
        mputc('-');

    if (sp->st_nlink < 10)
        printf("  %d ", sp->st_nlink);
    else
        printf(" %d ", sp->st_nlink);

    //print uid and gid
    printf(" %d  %d", sp->st_uid, sp->st_gid);

    //print size
    printf("%d ", sp->st_size);

    //print name
    printf("%s", name);

    // symlink file
    if ((mode & 0xF000) == 0xA000)
    {
        strcpy(fullname, path);
        strcat(fullname, "/");
        strcat(fullname, name);

        len = readlink(fullname, linkname);
        printf(" -> %s", linkname);
    }

    printf("\n\r");
}

//function to ls a directory
void ls_dir(STAT *sp, char *path)
{
    STAT dstat, *dsp;
    long size;
    char temp[255]; //etx2 filename os 1  255 chars
    int r;

    //get the size
    size = sp->st_size;





    //open dir file for read
    fd = open(file, O_RDONLY);

    /*read from the directory until there is nothing left*/


    while ((n = read(fd, buf, 1024)))
    {
        cp = buf;
        dp = (DIR *)buf;

        while (cp < buf + 1024)
        {
            //print the contents of the directory that we are looking at
            dsp = &dstat;
            //copy nam
            strncpy(temp, dp->name, dp->name_len);
            temp[dp->name_len] = 0;
            f[0] = 0;

            strcpy(f, file);
            strcat(f, "/");
            strcat(f, temp);

            //check if the current item is a file or not
            if (stat(f, dsp) >= 0) //if its a file, then stat the file
                ls_file(dsp, temp, path);

            /*if its not, we update the current pointer wby the recrod length of what 
            we just ls-ed*/
            cp += dp->rec_len;
            dp = (DIR *)cp;
        }
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    int r, i;
    sp = &utat;

    print2f("THIS IS STACY'S ls PROGRAM\n");
    print2f("\n");

    //if no file given, ls the current dir
    if (argc == 1)
    {
        strcpy(file, "./");
    }
    else //else ls whatever was provided
    {
        strcpy(file, argv[1]);
    }

    //check if the stat is valid
    if (stat(file, sp) < 0)
    {
        printf("cannot stat %s\n", argv[1]);
        exit(2);
    }

    //if it  s a file
    if ((sp->st_mode & 0xF000) == 0x8000)
    {
        ls_file(sp, file, file);
    }
    else
    {
        //if its a dir
        if ((sp->st_mode & 0xF000) == 0x4000)
        {
            ls_dir(sp, file);
        }
    }

    exit(0);
}
