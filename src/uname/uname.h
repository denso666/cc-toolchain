#ifndef UNAME_H
#define UNAME_H

#include <sys/utsname.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Print system information
 * @return int On success, one is returned. On error, one is returned.
 */
int __uname__(void);

#endif
