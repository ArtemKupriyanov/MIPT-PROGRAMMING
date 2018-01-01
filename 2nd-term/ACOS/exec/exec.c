#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void son()
{
	execlp("ls", "ls", NULL);
	perror("ls");
	exit(1);
}

int main(int argc, const char* argv[])
{
	int k1 = fork();
	int k2 = fork();
	if (k1 == 0)
	{
		son();
		exit(0);
	}
	else
		wait(&k1);
	if (k2 == 0)
	{
		son();
		exit(0);
	}
	else
		wait(&k2);
	printf("k1 k2 %d %d\n", k1, k2);
	printf("I conched\n");
	return 0;
}
