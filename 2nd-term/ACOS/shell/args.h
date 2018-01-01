struct args {
    char **argv;
    int argc;

    int capacity;
};
typedef struct args args_t;

void run_cd (char** argv);
void args_new(args_t *args);
void args_add(args_t *args, const char *arg);
void args_exterminate(args_t *args);
void get_directory (char* directory_main);
int try_open_directory(char* str);
void update_directory (char* directory_main);