#include "touch.h"

int __touch__(const char* target_file)
{
    struct stat st;
    // exist
    if (!stat(target_file, &st))
    {
        // is a directory
        if ((st.st_mode & S_IFMT) == S_IFDIR)
        {
            fprintf(stderr, "touch: %s: Is a directory\n", target_file);
            return 1;
        }
        // update last access and modify date
        else
        {
            struct utimbuf new_time;
            time_t t = time(NULL);
            new_time.actime = t;
            new_time.modtime = t;
            if (utime(target_file, &new_time) != 0)
            {
                perror("touch");
                return 1;
            }
            return 0;
        }
    }
    // create file
    else
    {
        if (creat(target_file, S_IRUSR | S_IWUSR | S_IROTH | S_IRGRP) < 0)
        {
            perror("touch");
            return 1;
        }
        return 0;
    }
}
