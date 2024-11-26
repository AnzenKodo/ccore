#include <stdio.h>
#include <unistd.h>  // For access() on Unix-like systems
#include <fcntl.h>   // For constants like O_RDONLY
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool file_exist(char *path) {
    if (access(path, F_OK) == 0) {
        return true;
    } else {
        return false;
    }
}

char *get_cache_dir() {
    char cache_dir[100];
    const char *cache_env = getenv("XDG_CACHE_HOME");

    if (cache_env == NULL) {
        const char *home = getenv("HOME");

        if (home != NULL) {
            strcpy(cache_dir, home);
            strcat(cache_dir, "/.cache");
        } else {
            perror("Error: could not find home directory.\n");
            exit(0);
        }
    } else {
        strcpy(cache_dir, cache_env);
    }

    if (file_exist(cache_dir)) {
        fprintf(stdout, "Error: '%s' does not exist.\n", cache_dir);
    }

    return cache_dir;
}
