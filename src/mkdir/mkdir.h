#ifndef MKDIR_H
#define MKDIR_H

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

/**
 * Ask the system to create a directory
 * @return int On success, 0 is returned. On error, -1 is returned.
 */
int MakeDir_Function(char * directory);

#endif
