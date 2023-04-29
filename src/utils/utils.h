#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

void clean_buffer();

/**
 * Checks it a path is a directory
 * Return 1 if it is a file, 0 if it is not and -1 in case of error
 */
int is_dir(char *path);

/**
 * Removes the new line character (assuming is the last character)
 */
int remove_lastchar(char *str);

#endif
