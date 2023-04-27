#ifndef COMMANDS_H
#define COMMANDS_H

#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

/**
 * Concatenate files and print on the standard output
 * @param path target file path
 * @return int status of read file
 */
int __cat__(const char*);

#endif
