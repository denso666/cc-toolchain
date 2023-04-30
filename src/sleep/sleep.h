#ifndef SLEEP_H
#define SLEEP_H

#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MIN2SEC(x) (x)*60
#define HOUR2SEC(x) MIN2SEC(x)*60

/**
 * Ask the system to sleep the process
 * @return int On success, 0 is returned. On error, -1 is returned.
 */
int Sleep_Function(char *seconds);

#endif
