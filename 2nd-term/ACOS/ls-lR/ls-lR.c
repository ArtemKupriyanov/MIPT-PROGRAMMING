#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <stdarg.h>
#include <pwd.h>
#include <grp.h>

const int RIGHT_FLAGS[9] = { S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH };

const char RIGHT_SYMBOLS[9] = { 'r', 'w', 'x', 'r', 'w', 'x', 'r', 'w', 'x' };

const char NO_RIGHT_SYMBOL = '-';

void make_rights_formatted (int st_mode, char result[11]) {
    result[10] = '\0';
    result[0] = S_ISDIR(st_mode) ? 'd' : '-';
    for (int i = 1; i < 10; i++) {
        if ((st_mode & RIGHT_FLAGS[i - 1]) == RIGHT_FLAGS[i - 1]) {
            result[i] = RIGHT_SYMBOLS[i - 1];
        }
        else {
            result[i] = NO_RIGHT_SYMBOL;
        }
    }
}

int max (int a, int b) {
    return a >= b ? a : b;
}

int visit_directory (char *dirname, char ***entries) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        perror(dirname);
        return -1;
    }

    struct dirent *dir_entry;

    char *entry_name;
    int entry_name_capacity = 20;

    entry_name = malloc(sizeof(char) * (entry_name_capacity + 1));

    int entries_size = 0;
    int entries_capacity = 10;
    *entries = realloc(*entries, sizeof(char *) * entries_capacity);

    while ((dir_entry = readdir(dir)) != NULL) {
        // Ignoring this and parent directories
        if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0) {
            continue;
        }
        int name_size = strlen(dir_entry->d_name);
        if (name_size < entry_name_capacity) {
            entry_name_capacity = max(entry_name_capacity * 2, name_size);
            entry_name=realloc(entry_name, sizeof(char) * (entry_name_capacity + 1));
        }
        sprintf(entry_name, "%s", dir_entry->d_name);

        // Adding entry to the array.
        char *new_entry = malloc(name_size);
        memcpy (new_entry, entry_name, name_size);
        new_entry[name_size] = '\0';

        if (entries_size == entries_capacity) {
            entries_capacity *= 2;
            *entries = realloc(*entries, sizeof(char *) * entries_capacity);
        }
        (*entries)[entries_size] = new_entry;
        ++entries_size;
    }

    closedir(dir);

    if (entries_size < entries_capacity) {
        *entries = realloc(*entries, entries_size * sizeof(char *));
    }

    return entries_size;
}

// Safely prints data to char array pointed by **dest.
int sprintf_to (int dest_cap, char **dest, char *format, ...) {
    if (*dest == NULL || dest_cap == 0) {
        *dest = realloc(*dest, sizeof(char) * 10);
        dest_cap = 10;
    }

    va_list args;
    va_start (args, format);
    int size = vsnprintf(*dest, dest_cap, format, args) + 1;

    //printf("size=%d, dest_cap=%d\n", size, dest_cap);
    if (size > dest_cap) {
        *dest = realloc(*dest, sizeof(char) * size);
        dest_cap = size;

        va_end(args);
        va_start(args, format);
        vsnprintf(*dest, size, format, args);
    }

    va_end(args);
    return dest_cap;
}

static int compare_str_asc (const void *a, const void *b) {
    return strcmp (* (char * const *) a, * (char * const *) b);
}

void ls (char *dirname) {
    char **entries = NULL;
    int entries_count;

    entries_count = visit_directory(dirname, &entries);

    qsort (entries, entries_count, sizeof(char *), compare_str_asc);

    struct stat stat_buf;

    int path_cap = 20;
    char *path = malloc(path_cap * sizeof(char));

    const int columns_count = 7;
    char ***data;

    data = malloc(sizeof(char**) * entries_count);

    for (int i = 0; i < entries_count; i++) {
        path_cap = sprintf_to(path_cap, &path, "%s/%s", dirname, entries[i]);
        //printf("path=%s\n", path);

        if (stat(path, &stat_buf)) {
            perror(path);
            continue;
        }

        char rights[10];
        make_rights_formatted(stat_buf.st_mode, rights);

        char *access_time = ctime(&stat_buf.st_atime);
        access_time[strlen(access_time) - 1] = '\0';

        // Collecting statistics.
        data[i] = malloc(sizeof(char*) * columns_count);

        for (int j = 0; j < columns_count; j++) {
            data[i][j] = NULL;
        }

        struct passwd *owner_usr = getpwuid (stat_buf.st_uid);
        struct group *owner_grp = getgrgid (stat_buf.st_gid);

        int off = 0;
        sprintf_to(0, data[i] + off++, "%s", rights);
        sprintf_to(0, data[i] + off++, "%d", stat_buf.st_nlink);
        sprintf_to(0, data[i] + off++, "%s", owner_usr->pw_name);
        sprintf_to(0, data[i] + off++, "%s", owner_grp->gr_name);
        sprintf_to(0, data[i] + off++, "%lld", (long long)stat_buf.st_size);
        sprintf_to(0, data[i] + off++, "%s", access_time);
        sprintf_to(0, data[i] + off++, "%s", entries[i]);
    }
    // Counting column sizes.
    int col_max_len[columns_count];

    for (int i = 0; i < columns_count; i++) {
        col_max_len[i] = 0;
    }

    for (int j = 0; j < columns_count; j++) {
        for (int i= 0; i < entries_count; i++) {
            col_max_len[j] = max(col_max_len[j], strlen(data[i][j]));
        }
    }

    // Printing data.
    printf("%s:\n", dirname);
    for (int i = 0; i < entries_count; i++) {
        for (int j = 0; j < columns_count - 1; j++) {
            printf("%*s ", col_max_len[j], data[i][j]);
        }
        printf("%s\n", data[i][columns_count - 1]);
    }

    // Cleaning memory obtained by ***data.
    for (int i = 0; i < entries_count; i++) {
        for (int j = 0; j < columns_count; j++) {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);

    // Visiting entries.
    for (int i = 0; i < entries_count; i++) {
        sprintf(path, "%s/%s", dirname, entries[i]);
        if (stat(path, &stat_buf)) {
            perror(path);
            continue;
        }
        if (S_ISDIR(stat_buf.st_mode)) {
            printf("\n");
            ls (path);
        }
    }

    // Cleaning memory.
    free(path);
    for (int i = 0; i < entries_count; i++) {
        free(entries[i]);
    }
    free (entries);
}

int main (int argc, char **argv) {
    char **dir_lim = argv + argc;
    for (char **dir = argv + 1; dir < dir_lim; dir++) {
        if (dir > argv + 1) {
            printf("\n");
        }
        ls(*dir);
    }
}
