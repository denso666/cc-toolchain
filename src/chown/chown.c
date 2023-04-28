#include "chown.h"

/**
 * Allows to change the ownership of a file
 */
int custom_chown(char *path, char *owners) {
  if (path == NULL || owners == NULL) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }

  // Validates the path exists
  struct stat file_stat;
  if (stat(path, &file_stat) == -1) {
    return EXIT_FAILURE;
  }
  // Set the defaults group id
  gid_t group_id = file_stat.st_gid;

  // Gets the user name from the given argument
  char *user_name = strtok(owners, ":");
  if (user_name == NULL) {
    errno = EINVAL;
    return EXIT_FAILURE;
  }

  // Retrieves the user id from /etc/passwd
  struct passwd *user;
  if ((user = getpwnam(user_name)) == NULL) {
    printf("User '%s' does not exists\n", user_name);
    errno = EINVAL;
    return EXIT_FAILURE;
  }
  uid_t user_id = user->pw_uid;

  // If group name was given it retrieves the group id
  char *group_name = strtok(NULL, ":");
  if (group_name != NULL) {
    struct group *grp;
    if ((grp = getgrnam(group_name)) == NULL) {
      printf("Group '%s' does not exists\n", group_name);
      errno = EINVAL;
      return EXIT_FAILURE;
    }
    group_id = grp->gr_gid;
  }

  // Change the ownership of the input file
  return chown(path, user_id, group_id);
}
