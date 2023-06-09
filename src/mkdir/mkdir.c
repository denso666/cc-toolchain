#include "mkdir.h"

int MakeDir_Function(char * directory)
{
    int ret_val = EXIT_SUCCESS;
    int val = mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (val ==  0)
    {
        printf("Directory created\n");
    }
    else
    {
        ret_val = EXIT_FAILURE;
        perror("mkdir");
        return ret_val;
    }
    return ret_val;
}
