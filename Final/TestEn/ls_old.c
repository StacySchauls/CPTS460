
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
    int mask, k, len;
    char fullname[32], linkname[60];

    mode = sp->st_mode;

    if ((mode & 0xF000) == 0x4000) //print file type as d
        mputc('d');

    if ((mode & 0xF000) == 0xA000) //print file type as s
        mputc('s');
    else if ((mode & 0xF000) == 0x8000) //print file type as -
        mputc('-');

    mask = 000400;
    // uses bitwise and to check each byte in the mode.
    /*
    for (k = 0; k < 3; k++)
    {
        if (mode & mask)
            mputc('r');
        else
            mputc('-');
        mask = mask >> 1;
        if (mode & mask)
            mputc('w');
        else
            mputc('-');
        mask = mask >> 1;
        if (mode & mask)
            mputc('x');
        else
            mputc('-');
        mask = mask >> 1;
    }
    */
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

    printf(" %d  %d", sp->st_uid, sp->st_gid);

    printf("%d ", sp->st_size);

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

void ls_dir(STAT *sp, char *path)
{
    STAT dstat, *dsp;
    long size;
    char temp[32];
    int r;

    size = sp->st_size;

    //open dir file for read
    fd = open(file, O_RDONLY);
    while ((n = read(fd, buf, 1024)))
    {
        cp = buf;
        dp = (DIR *)buf;

        while (cp < buf + 1024)
        {
            dsp = &dstat;
            strncpy(temp, dp->name, dp->name_len);
            temp[dp->name_len] = 0;
            f[0] = 0;
            strcpy(f, file);
            strcat(f, "/");
            strcat(f, temp);
            if (stat(f, dsp) >= 0)
                ls_file(dsp, temp, path);

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

    printf("Stacy's_ls\n");

    if (argc == 1)
    {
        strcpy(file, "./");
    }
    else
    {
        strcpy(file, argv[1]);
    }

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
