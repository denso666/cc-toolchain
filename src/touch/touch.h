#ifndef TOUCH_H
#define TOUCH_H

#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <utime.h>
#include <time.h>


/**
 * @brief Change file timestamps
 * @param target_file target file
 * @return int status of creation or status change
 */
int __touch__(const char*);

#endif
