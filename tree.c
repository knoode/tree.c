#include "util.h"

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>

// TODO: build.sh
// TODO: More detailed errors
// TODO: Support for Windows
// TODO: Print starting directory as first line


int walk(const char *path, unsigned indent);


int main(int argc, char *argv[])
{
    setlocale(LC_CTYPE, "");

    const char *path = ".";  // default path is current

    if (argc == 2) {
        path = argv[1];
    } else if (argc > 2) {
        puts("usage: ./tree [DIRECTORY]");
        return 1;
    }

    int err = walk(path, 0);

    return err;
}


int walk(const char *path, unsigned indent)
{
    /* Open directory instance */
    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return 1;
    }
    
    struct dirent *current = get_next_valid_entry(dir);
    struct dirent *next = NULL;
    
    /* Iterate through all files */
    while (current != NULL) {
        next = get_next_valid_entry(dir);
        
        const char *filename = current->d_name;

        /* Directory */
        if (current->d_type == DT_DIR) {
            print_file(filename, true, false, indent);

            size_t len = strlen(path) + strlen(filename) + 2;
            char new_path[len];

            char *err = concat_path(path, filename, new_path, len);
            
            if (!err) {
                perror("malloc");
                return 1;
            }

            walk(new_path, indent + 1);
        }
        /* File or other */
        else {
            print_file(filename, false, next == NULL, indent);
        }

        current = next;
    }

    closedir(dir);
    return 0;
}