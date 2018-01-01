#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <memory.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAXSIZ 4096

void arch(const char* path, int fd_out, int uid, char type)
{
	puts(path);

	char* buf = (char*)malloc(65536 * sizeof(char));
	if (buf == NULL)
	{
		perror("arch: malloc:");
		exit(2);
	}

	int path_size = strlen(path);
	sprintf(buf, "%c%c%s", path_size & 255, (path_size >> 8) & 255, path);

	char s_uid[11];
	int i = 0;
	while (uid)
	{
		s_uid[i++] = uid % 10 + 48;
		uid /= 10;
	}
	s_uid[i] = 0;

	char uid_len = i;
	while (i / 2)
	{
		char t = s_uid[i - 1];
		s_uid[i - 1] = s_uid[uid_len - i];
		s_uid[uid_len - i] = t;
		i--;
	}

	if (type != '-')
	{
		int len = path_size + 2;
		char link = (type == 'l' ? 4 : 0);
		sprintf(buf + len, "%c%c%c%c%s%s", 0, 0, uid_len + link,
				0, s_uid, (type == 'l' ? "link" : ""));
		write(fd_out, buf, len + 4 + uid_len + link);

		free(buf);

		return;
	}

	int fd_in = open(path, O_RDONLY);

	write(fd_out, buf, path_size + 2);

	int read_size = read(fd_in, buf, MAXSIZ);
	char s_size[2];
	s_size[0] = read_size & 255;
	s_size[1] = (read_size >> 8) & 255;

	write(fd_out, s_size, 2);
	write(fd_out, buf, read_size);

	sprintf(buf, "%c%c%s", uid_len, 0, s_uid);
	write(fd_out,  buf, uid_len + 2);

	close(fd_in);

	free(buf);
}

char list(const char* path, int fd_out)
{
	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir(path)) == NULL)
	{
		perror("arch: opendir:");
		return 0;
	}

	char not_empty = 0;
	while ((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.')
			continue;

		char* new_path = malloc((strlen(path) + strlen(entry->d_name) + 2) * sizeof(char));
		if (new_path == NULL)
		{
			perror("arch: malloc:");
			exit(2);
		}
		sprintf(new_path, "%s%s", path, entry->d_name);

		struct stat buf;
		stat(new_path, &buf);

		char type = '-';
		if (S_ISDIR(buf.st_mode))
			type = 'd';
		else if (S_ISLNK(buf.st_mode))
			type = 'l';

		if (type == 'd')
		{
			int len = strlen(new_path);
			new_path[len] = '/';
			new_path[len + 1] = '\0';

			if (!list(new_path, fd_out))
				arch(new_path, fd_out, buf.st_uid, type);
		}
		else if (buf.st_size <= MAXSIZ)
		{
			not_empty = 1;
			arch(new_path, fd_out, buf.st_uid, type);
		}
		else
			fprintf(stderr, "arch: %s: file is too large\n", new_path);

		free(new_path);
	}

	closedir(dir);

	return not_empty;
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "usage: arch PATH ARCH_NAME\n");
		return 1;
	}

	char path[1024];
	strcpy(path, argv[1]);

	int i;
	for (i = strlen(path) - 1; path[i] == '/'; i--);

	path[i + 1] = '/';
	path[i + 2] = '\0';

	int fd_out = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU);

	list(path, fd_out);

	close(fd_out);

	return 0;
}
