#include "uptime.h"

int Uptime_Function(void)
{
    int ret_val = 0;
    struct sysinfo SystemInformation;
    int days = 0;
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int val = sysinfo(&SystemInformation);
    if (0 == val)
    {
        seconds = SystemInformation.uptime % 60;
        minutes = (SEC2MIN(SystemInformation.uptime)) % 60;
        hours = (SEC2HOUR(SystemInformation.uptime)) % 24;
        days = (SEC2DAYS(SystemInformation.uptime));


        printf("Uptime: %d days, %d hours, %d minutes, %d seconds\n", days,hours,minutes,seconds);
    }
    else
    {
        ret_val = -1;
        fprintf(stderr, "Error: %s\n", strerror(val));
        return ret_val;
    }
    return ret_val;
}