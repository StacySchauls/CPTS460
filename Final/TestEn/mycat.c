B/********** mycat.c file *************/
#include "ucode.c"
#define BLKSIZE 1024
extern char cr;

int main(int argc, char *argv[ ])
{
	char ttybuf[128];
	STAT ttystat, fdstat;

	gettty(ttybuf);
	//printf("ttybuf=%s\n", ttybuf);
	stat(ttybuf, &ttystat);
	fstat(1, &fdstat);
	//printf("tty.ino=%d fd.ino=%d\n", ttystat.st_ino,fdstat.st_ino);
	char input[128];
	if (argc == 1)
	{
		printf("argc=%d\n", argc);
		printf("argv[0]=%s\n", argv[0]);
		char *tmp = ".";
		printf("no file%s\n", tmp);
		gets(input);
		printf("input=%s\n", input);
		return;
	}
	else if (argc == 2)
	{
		//printf("argc=%d\n", argc);
		//printf("argv[0]=%s\n", argv[0]);
		//printf("argv[1]=%s\n", argv[1]);
		char mybuf[BLKSIZE];  // a null char at end of mybuf[ ]
		int n = 0;
		int fd = open(argv[1], O_RDONLY);
		int i = 0;
		if (fd < 0) return -1;
		//printf("%s------------
		while ( n = read(fd, mybuf, BLKSIZE)) {
			mybuf[n] = 0;
			//spit out chars from mybuf[ ] but handle \n properly;
			//printf("n=%d mybuf=%s", n, mybuf);
			for (i = 0; i < n; i++)
			{

				if(mybuf[i] == '\n' && ttystat.st_ino == fdstat.st_ino)
				{
					//write(1, &cr, 1);
					//write(1, &mybuf[i], 1);
					mputc(mybuf[i]);
				}
				else if (mybuf[i] == '\n' && ttystat.st_ino != fdstat.st_ino)
				{
					write(1, &mybuf[i], 1);
				}
				else
				{
					mputc(mybuf[i]);
				}
			}
		}

		close(fd);
		return;
	}
	/*
	else //can't reach //cat f1 > f2
	{
		printf("argc=%d\n", argc);
		printf("argv[0]=%s\n", argv[0]);
		printf("argv[1]=%s\n", argv[1]);
		printf("argv[2]=%s\n", argv[2]);
		printf("argv[3]=%s\n", argv[3]);
		return;
		char mybuf[BLKSIZE];  // a null char at end of mybuf[ ]
		int n = 0;
		int fd = open(argv[1], O_RDONLY);
		int i = 0;
		if (fd < 0) return -1;
		//printf("%s----------------------------------\n","-");
		while ( n = read(fd, mybuf, BLKSIZE)) {
			mybuf[n] = 0;
			//spit out chars from mybuf[ ] but handle \n properly;
			//printf("n=%d mybuf=%s", n, mybuf);
			for (i = 0; i < n; i++)
			{
				//mputc(mybuf[i]);
				//mputc(0);mputc(0);
				if (mybuf[i] == '\n')
				{
					// printc \n will auto add \r\n
					// mputc('\n');
					printf("argv[2] = %s", argv[2]);

					if (argv[2] != ">")
					{
						mputc(mybuf[i]);
					}
					else if (strcmp(argv[2], ">") == 0)
					{
						write(1, &mybuf[i], 1);
					}
					else
					{
						mputc(mybuf[i]);
					}
				}
				else
				{
					mputc(mybuf[i]);
				}
			}
		}

		close(fd);
	}
	*/


	//printf("%s----------------------------------\n","-");

}