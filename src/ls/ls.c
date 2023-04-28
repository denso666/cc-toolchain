#include "ls.h"
#include "../utils/utils.h"


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
