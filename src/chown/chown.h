#ifndef CHWON_H
#define CHWON_H 

#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Allows to change the ownership of a file
 */
int custom_chown(char *path, char *owners);

#endif
