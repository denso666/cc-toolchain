#ifndef CP_H
#define CP_H

#include <dirent.h>
#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

/**
 * Copy function, if r_flag is set to 1, it will copy directories recursive
 */
int cp(char *source, char *destination, int r_flag);

#endif
