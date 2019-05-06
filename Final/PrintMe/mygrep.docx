#include "ucode.c"
#define NUMLINES 128

int main(int argc, char *argv[])
{
    int fd, size, i, reader, count = 0, linenum = 0;
    char tx[64], line[64];
    int searching = 1;


//check if we are using stdin, a file, or what not
    if (argc == 1)
    {
        print2f("Usage: grep pattern file\n");
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


    //if it is a valid fd go into it
    if (fd >= 0)
    {

        print2f("\nSTACY'S GREP\n");
        size = strlen(argv[1]);

        // while we are searching fo the line
        while (searching == 1)
        {
            //clears our line.
            clearLine(&line);

            // need to build our input buffer that we will search throughby using read

            //read through each line,
            for (i = 0; i < NUMLINES; i++)
            {
                reader = read(fd, &line[i], 1);

                /*if we read less than one, we have reached trhe end and can no
                long read */
                if (reader < 1)
                {
                    searching = 0;
                    break;
                }

                /*check if we have a new line or return char, that becaome null*/
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
            //After reading the line, check if we have match
            if (searching == 1 && (!CheckLine(line, argv[1], size) == 1))
            {
                count++;
                printf("%d: %s\n", linenum, line);
            }
        }

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

//function to check if we have a match or not
int CheckLine(char *str, char *pattern, int size)
{
    /*uses strstr to chek if we have a patttern
    Wher strstr checks for the first occurance of the pattern in a str */
    if (!strstr(str, pattern))
    {
        return 1;
    }
    return 0;
}
