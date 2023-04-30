#include "sleep.h"

int Sleep_Function(char * seconds)
{
    int ret_val = EXIT_SUCCESS;
    long long unsigned int sleepTime = 0;
    if(isdigit(seconds[0]))
    {
        sleepTime = atoll(seconds[0]);
    }
    else
    {
        ret_val = EXIT_FAILURE;
        sleepTime = 0;
        fprintf(stderr, "Error: %s\n", strerror( EINVAL ));
        return ret_val;
    }
    while (0 != sleep(sleepTime));
    return ret_val;

}