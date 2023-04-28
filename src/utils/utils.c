#include "utils.h"

void clean_buffer() {
  while (getchar() != '\n')
    ;
}

/**
 * Checks it a path is a directory
 * Return 1 if it is a file, 0 if it is not and -1 in case of error
 */
int is_dir(char *path) {
  struct stat file_stat;
  if (lstat(path, &file_stat) == -1) {
    return -1;
  }
  if (S_ISDIR(file_stat.st_mode)) {
    return 1;
  }
  return 0;
}

int remove_lastchar(char *str) {
  if (str != NULL) {
    int len = strlen(str);
    str[len - 1] = '\0';
    return 0;
  }
  return -1;
}
