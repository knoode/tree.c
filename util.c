#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <dirent.h>


/* Unicode symbols for printing files */
const wchar_t BOX_FILE_LINE = 0x251c;
const wchar_t BOX_LAST_FILE_LINE = 0x2514;
const wchar_t BOX_VERT_LINE = 0x2502;
const wchar_t BOX_HOR_LINE = 0x2500;


void print_file(const char *name, bool is_dir, bool is_last, unsigned indent)
{
    if (indent > 0) {
        wprintf(L"%lc", BOX_VERT_LINE);
        for (unsigned i = 0; i < indent; i++) {
            if (i >= 1) {
                wprintf(L"%lc", BOX_VERT_LINE);
            }

            wprintf(L"   ");
        }
    }

    if (is_last) {
        wprintf(L"%lc", BOX_LAST_FILE_LINE);
    } else {
        wprintf(L"%lc", BOX_FILE_LINE);
    }

    wprintf(L"%lc%lc ", BOX_HOR_LINE, BOX_HOR_LINE, name);

    if (is_dir) {
        wprintf(BOLD_CYAN L"%s\n" RESET, name);
    } else {
        wprintf(BOLD_WHITE L"%s\n" RESET, name);
    }
}


struct dirent *get_next_valid_entry(DIR *dir)
{
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;

        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }

        return entry;
    }

    return NULL;
}


int concat_path(const char *pre, const char *post, char *buffer, size_t len)
{
    int n_slashes = 0;

    for (size_t i = strlen(pre) - 1; i >= 0; i--) {
        if (pre[i] == '/') {
            n_slashes++;
        } else {
            break;
        }
    }

    if (n_slashes == 0) {
        snprintf(buffer, len, "%s/%s", pre, post);
    } else {
        int new_len = strlen(pre) - (n_slashes - 1);
        char *no_trailing = (char*)malloc(new_len + 1);

        if (!no_trailing) {
            perror("malloc");
            return 1;
        }

        strncpy(no_trailing, pre, new_len);
        no_trailing[new_len] = '\0';
        
        snprintf(buffer, len, "%s%s", no_trailing, post);
        buffer[len - 1] = '\0';
    }

    return 0;
}