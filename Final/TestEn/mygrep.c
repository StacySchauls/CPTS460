#include "ucode.c"
#define NUMLINES 128
int main(int argc, char *argv[])
{
    int fd, size, i, reader, count = 0, linenum = 0;
    char tx[64], line[64];
    int searching = 1;

    if (argc == 1)
    {
        prints("Usage: grep pattern file\n");
        return -1;
    }
    else if (argc == 2)
    {
        //stdin
        fd = 0;
    }
    else
    {
        fd = open(argv[2], O_RDONLY);
        if (fd < 0)
        {
            prints("Error opeing file.\n");
            return -1;
        }
    }
    if (fd >= 0)
    {

        prints("\nSTACY'S GREP\n");
        size = strlen(argv[1]);
        printf("looking for %s\n", argv[1]);

        while (searching == 1)
        {
            //clears our line.
            clearLine(&line);
            // need to build our input buffer that we will search throughby using read
            for (i = 0; i < NUMLINES; i++)
            {
                reader = read(fd, &line[i], 1);

                if (reader < 1)
                {
                    searching = 0;
                    break;
                }
                if ((line[i] == '\n') || line[i] == '\r')
                {
                    line[i + 1] = 0;
                    break;
                }
                if (line[i] == 0)
                {
                    searching = 0;
                    break;
                }
            }
            linenum++;
            //check for a match
            //printf("line is: %s\n", line);
            if (searching == 1 && (!CheckLine(line, argv[1], size) == 1))
            {
                count++;
                printf("%d: %s\n", linenum, line);
            }
        }
        printf("Found %d matches. \n", count);
    }

    close(fd);
    return 0;
}

int clearLine(char *str)
{
    int i;
    for (i = 0; i < NUMLINES; i++)
    {
        str[i] = 0;
    }
    return 1;
}

int CheckLine(char *str, char *pattern, int size)
{
    if (!strstr(str, pattern))
    {
        return 1;
    }
    return 0;
}