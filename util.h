#ifndef UTIL_H
#define UTIL_H


#include <wchar.h>
#include <dirent.h>


#define BOLD_WHITE  "\x1b[1;37m"  // file
#define BOLD_CYAN   "\x1b[1;36m"  // directory
#define RESET       "\x1b[0m"


extern const wchar_t BOX_FILE_LINE; // = 0x251c;
extern const wchar_t BOX_LAST_FILE_LINE; // = 0x2514;
extern const wchar_t BOX_VERT_LINE; // = 0x2502;
extern const wchar_t BOX_HOR_LINE; // = 0x2500;


void print_file(const char *name, bool is_dir, bool is_last, unsigned indent);
struct dirent *get_next_valid_entry(DIR *dir);
int concat_path(const char *pre, const char *post, char *buffer, size_t len);


#endif // UTIL_H