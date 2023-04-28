#ifndef LS_H
#define LS_H

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// list the contents of the directory path
int ls(char *dir_path);

#endif
