#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


void wc_for_one_file(int fd, int* strings, int* words, int* bytes)
{
	char c;
	bool inword = 0;
	(*strings) = 0; (*words) = 0; (*bytes) = 0;
	while(read(fd, &c, 1) > 0)
	{
		(*bytes)++;
		if (c == '\n') (*strings)++;
		if (isspace(c) && inword)
		{
				(*words)++;
				inword = 0;
		}
		else
		{
			if (!isspace(c))
				inword = 1;
		}
	}
	if (inword) (*words)++;
	printf("%d %d %d ", *strings, *words, *bytes);
}


int main(int argc, char* argv[])
{
	int strings, words, bytes, fd;
	int strings_total = 0, words_total = 0, bytes_total = 0;
	if (argc == 1)
	{
		wc_for_one_file(0, &strings, &words, &bytes);
		return 0;
	}
	for (int i = 1; i < argc; i++)
		if ((fd = open(argv[i], O_RDONLY)) == -1)
			printf("wc: can't open file \"%s\"\n", argv[i]);
		else{
			wc_for_one_file(fd, &strings, &words, &bytes);
			printf("%s\n", argv[i]);
			strings_total += strings;
			words_total += words;
			bytes_total += bytes;
		}
	if (argc > 2)
		printf("%d %d %d total\n", strings_total, words_total, bytes_total);
	return 0;
}
