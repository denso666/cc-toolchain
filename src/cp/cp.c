#include "cp.h"
#include "../utils/utils.h"

/**
 * Gets the mode from the inode entry of a file
 */
int get_mode(char *path) {
  struct stat file_stat;
  if (stat(path, &file_stat) == -1) {
    return -1;
  }
  return file_stat.st_mode;
}

/**
 * Checks it a path is a file
 * Return 1 if it is a file, 0 if it is not and -1 in case of error
 */
int is_file(char *path) {
  struct stat file_stat;
  if (lstat(path, &file_stat) == -1) {
    return -1;
  }
  if (S_ISREG(file_stat.st_mode) || S_ISBLK(file_stat.st_mode) ||
      S_ISCHR(file_stat.st_mode) || S_ISFIFO(file_stat.st_mode) ||
      S_ISLNK(file_stat.st_mode)) {
    return 1;
  }
  return 0;
}

/**
 * Concatenates to paths and return the pointer to the combined
 * As the lenght of the path is variable, a new char* is allocated with malloc
 * So free should be called on the returned pointer
 */
char *concat_path(char *path_a, char *path_b) {
  // Gets the length of both paths
  long dir_len = strlen(path_a);
  long base_len = strlen(path_b);

  // Allocates the memory for the combined path
  // The extra 2 characters are for \0 and /
  char *full_path = malloc((dir_len + base_len + 2) * sizeof(char));
  if (full_path == NULL) {
    return NULL;
  }

  // Initialize the full path with string termination character
  full_path[0] = '\0';

  // Concatenates both pats (could have done this easier with sprintf)
  strcat(full_path, path_a);
  // Concatenates the path separator
  full_path[dir_len] = '/';
  full_path[dir_len + 1] = '\0';
  strcat(full_path, path_b);
  return full_path;
}

// Copy command for sym links (only called when copying directories)
int cp_link(char *source, char *dest) {
  // Creates a buffer for the path
  // (Probably there is a better way of allocating this)
  char buffer[PATH_MAX];
  int bytes_read = 0;
  // Reads the path that the sym link points to
  if ((bytes_read = readlink(source, buffer, sizeof(buffer))) == -1) {
    return EXIT_FAILURE;
  }
  // readlink does not add the end of string character
  // so it needs to be added manually
  buffer[bytes_read] = '\0';

  // Concats the filename to the destination path
  char *source_dup = strdup(source);
  char *file_name = basename(source_dup);
  char *full_dest = concat_path(dest, file_name);
  free(source_dup);

  // Creates the sym link in the destination
  if (symlink(buffer, full_dest) == -1) {
    return EXIT_FAILURE;
  }
  free(full_dest);
  return EXIT_SUCCESS;
}

// Copy the contents of source in dest
int copy_file(char *source, char *dest) {
  // Buffer chunk
  char buffer[4096];

  // Opens the source file in read mode
  FILE *fsource = fopen(source, "r");
  if (fsource == NULL) {
    return EXIT_FAILURE;
  }

  // Opens the destination file in write mode
  // Creates the file if id does not exists
  FILE *fdest = fopen(dest, "w");
  if (fdest == NULL) {
    return EXIT_FAILURE;
  }

  // Reads the size of the buffer until the source EOF is reached
  while (feof(fsource) == 0) {
    size_t written = fread(buffer, sizeof(char), sizeof(buffer), fsource);
    // Need to check for ferror as fread does not set it
    if (ferror(fsource) != 0) {
      errno = EIO;
      return EXIT_FAILURE;
    }
    fwrite(buffer, sizeof(char), written, fdest);
    if (ferror(fdest) != 0) {
      errno = EIO;
      return EXIT_FAILURE;
    }
  }

  // Close the files
  fclose(fsource);
  fclose(fdest);

  // Tries to set the same owner and mode as the original file
  struct stat source_stat;
  stat(source, &source_stat);
  chmod(dest, source_stat.st_mode);
  chown(dest, source_stat.st_uid, source_stat.st_gid);
  return EXIT_SUCCESS;
}

// Checks if the parent directory is a directory
// Same as is_dir but use direname as the path
int parent_is_dir(char *path) {
  char *dir_dup = strdup(path);
  char *dir_name = dirname(dir_dup);
  int dir_name_is_dir = is_dir(dir_name);
  free(dir_dup);
  return dir_name_is_dir;
}

// Copy function if -f flag is not set
int cp_file(char *source, char *dest) {
  // Validates the source is a file
  int source_is_file = is_file(source);
  if (source_is_file != 1) {
    printf("File '%s' not found\n", source);
    errno = ENOENT;
    return EXIT_FAILURE;
  }

  // Checks if the destination is a directory
  int dest_is_dir = is_dir(dest);
  if (dest_is_dir == -1) {
    // If the destination is dos not exists checks the rest of the path exists
    if (parent_is_dir(dest) != 1) {
      printf("Destination '%s' is invalid\n", dest);
      errno = ENONET;
      return EXIT_FAILURE;
    }
  }
  // If the destination is a directory
  if (dest_is_dir == 1) {
    char *file_dup = strdup(source);
    char *file_name = basename(file_dup);
    // Concats the name of the source file to the destination path
    char *full_path = concat_path(dest, file_name);
    free(file_dup);
    // Copy the contents of the source to the destination path
    int copy_return = copy_file(source, full_path);
    int copy_errno = errno;
    free(full_path);
    errno = copy_errno;
    return copy_return;
  }

  // If destination is a file just copy the contents
  return copy_file(source, dest);
}

int cp_dir(char *source, char *dest) {
  // Validate sthe source is a directory
  int source_is_dir = is_dir(source);
  if (source_is_dir == -1) {
    printf("Source directory '%s' does not exists\n", source);
    return EXIT_FAILURE;
  }
  if (source_is_dir == 0) {
    printf("Source '%s' is not a directory\n", source);
    errno = ENOTDIR;
    return EXIT_FAILURE;
  }

  // Validates the destination is a directory
  int dest_is_dir = is_dir(dest);
  // if (dest_is_dir == 1) {
  //   if (is_dir_empty(dest) == 0) {
  //     printf("Destination '%s' is not a empty\n", dest);
  //     errno = ENOTEMPTY;
  //     return EXIT_FAILURE;
  //   }
  // }

  // If the destination exists but is a file
  // return error
  if (dest_is_dir == 0) {
    printf("'%s' already exists\n", dest);
    errno = EEXIST;
    return EXIT_FAILURE;
  }

  // If the destinatin does not exists makes the directory
  if (dest_is_dir == -1) {
    if (parent_is_dir(dest) != 1) {
      return EXIT_FAILURE;
    }
    if (mkdir(dest, get_mode(source)) == -1) {
      return EXIT_FAILURE;
    }
  }

  // Open the source directory file and read its entries
  struct dirent *dir_entry;
  DIR *dir = opendir(source);
  while ((dir_entry = readdir(dir)) != NULL) {
    // Ignores the self and parent paths
    if (strcmp(".", dir_entry->d_name) == 0 ||
        strcmp("..", dir_entry->d_name) == 0) {
      continue;
    }

    int cp_return = 0;
    int cp_error = 0;
    // Get the full path of the directory entry
    char *full_path = concat_path(source, dir_entry->d_name);
    // If the entry is a directory makes the new destination and call cp_dir
    // recursively
    if (dir_entry->d_type == DT_DIR) {
      char *dest_with_folder = concat_path(dest, dir_entry->d_name);
      cp_return = cp_dir(full_path, dest_with_folder);
      cp_error = errno;
      free(dest_with_folder);
    } else if (dir_entry->d_type == DT_LNK) {
      // If the entry is a link makes sym link to the the same path in the new
      // destination
      cp_return = cp_link(full_path, dest);
      cp_error = errno;
    } else {
      // If is any other type of file copy the contents of the file
      cp_return = cp_file(full_path, dest);
      cp_error = errno;
    }

    free(full_path);

    // Handles any of the cp errors
    if (cp_return == EXIT_FAILURE) {
      closedir(dir);
      errno = cp_error;
      return cp_return;
    }
  }
  closedir(dir);
  return EXIT_SUCCESS;
}

/**
 * Copy function, if r_flag is set to 1, it will copy directories recursive
 */
int cp(char *source, char *destination, int r_flag) {
  if (source == NULL || destination == NULL) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }

  // Depending on if -r is set calls to diferent functions
  if (r_flag) {
    return cp_dir(source, destination);
  }
  return cp_file(source, destination);
}
