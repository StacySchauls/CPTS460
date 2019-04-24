#include "ucode.c"
#include "strings.h"
void mutilpip(char* line)
{
	if (!line || (line[0] == 0) || (strcmp(line, "") == 0))
		exit(0);

	int pd[2];
	int pid, status;
	int length = strlen(line);
	char* head = strtok(line, "|");
	char* tail = null;

	if (strlen(head) < length)
		tail = line + strlen(head) + 1;
	else
		tail = line + length;


	if (!tail || (strcmp(tail, "") == 0))
		exec(head);




	if (pipe(pd) != 0) 
		if ((pid = fork()) < 0)
		
			if (!pid) {
				close(pd[0]);
				close(1);
				dup(pd[1]);
				exec(head);
			}
			else {
				pid = wait(&status);
				close(pd[1]);
				close(0);
				dup(pd[0]);

				mutilpip(tail);
			}
}

int main()
{
	while (1)
	{
		int pid, status;

		char line[128];
		printf("mysh %d # :", getpid());
		gets(line);
		if (line == 0) return;
		token(line);

		if (argc == 0)
		{
			printf("argc=%d\n", argc);
		}
		else if (argc == 1)
		{
			printf("argc=%d\n", argc);
			printf("argv[0]=%s\n", argv[0]);

			if (strcmp("logout", argv[0]))
			{
				exit(0);
			}


			if ((pid = fork()) < 0)
				printf("forking child process%s", ".");

			if (pid)
			{
				printf("%d waiting...\n", pid);
				pid = wait(&status);
				printf("%d died of %04x\n", pid, status);
			}
			else
			{
				mutilpip(line);
			}
		}
	}
	return 0;
}

