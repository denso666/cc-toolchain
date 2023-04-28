#include "sleep.h"

int Sleep_Function(int argc, char ** arg)
{
    int ret_val = 0;
    long long unsigned int sleepTime = 0;
    long long unsigned int tempTime = 0;
    for (int i = 1; i < argc; i++)
    {
        if(isdigit(arg[i][0]))
        {
            for(int j = 0; j < strlen(arg[i]); j++)
            {
                if ((arg[i][j] >= '0' && arg[i][j] <= '9') || arg[i][j] == 'm' || arg[i][j] == 'h')
                {
                    'm'==arg[i][strlen(arg[i])-1]? (tempTime = MIN2SEC(atoll(arg[i])))  :\
                    'h'==arg[i][strlen(arg[i])-1]? (tempTime = HOUR2SEC(atoll(arg[i]))) : (tempTime = atoll(arg[i]));
                    sleepTime = tempTime;
                }
                else
                {
                    ret_val = -1;
                    sleepTime = 0;
                    fprintf(stderr, "Error: %s please set time as integer\n", strerror( EINVAL ));
                    return ret_val;
                }
            }
        }
        else
        {
            ret_val = -1;
            sleepTime = 0;
            fprintf(stderr, "Error: %s\n", strerror( EINVAL ));
            return ret_val;
        }
    }
    while (0 != sleep(sleepTime));
    return ret_val;

}