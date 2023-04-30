#ifndef UPTIME_H
#define UPTIME_H

#include <stdio.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <stdlib.h>


#define SEC2MIN(x) (x)/60
#define SEC2HOUR(x) SEC2MIN(x)/60
#define SEC2DAYS(x) SEC2HOUR(x)/24

/**
 * Ask the system the current uptime
 * @return int On success, 0 is returned. On error, -1 is returned.
 */
int Uptime_Function(void);


#endif
