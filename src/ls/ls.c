#include "ls.h"

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

// list the contents of the directory path
int ls(char *dir_path) {
  // Default source path
  char *source = ".";
  if (source != NULL) {
    source = dir_path;
  }

  // Validate that the path is a directory
  int is_source_dist = is_dir(source);
  if (is_source_dist == -1) {
    return EXIT_FAILURE;
  }
  if (is_source_dist == 0) {
    errno = ENOTDIR;
    return EXIT_FAILURE;
  }

  // Open the directory file and read its entries
  DIR *dir = opendir(source);
  struct dirent *file;
  while ((file = readdir(dir)) != NULL) {
    // Ignores the self and parent paths
    if (strcmp(".", file->d_name) == 0 || strcmp("..", file->d_name) == 0) {
      continue;
    }
    printf("%s\n", file->d_name);
  }
  closedir(dir);
  return EXIT_SUCCESS;
}
