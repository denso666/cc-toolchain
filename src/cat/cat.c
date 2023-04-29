#include "./cat.h"

int __cat__(const char* path)
{
    struct stat st;
    // exist?
    if (stat(path, &st) != -1)
    {
        // is a directory?
        if ((st.st_mode & S_IFMT) == S_IFDIR)
        {
            fprintf(stderr, "cat: %s: Is a directory\n", path);
            return EXIT_FAILURE;
        }
        else
        {
            int fd = open(path, O_RDONLY);
            if (fd)
            {
                char* buf = (char*)malloc(1);
                while (read(fd, buf, 1))
                {
                    fprintf(stdout, "%s", buf);
                }
                close(fd);
                free(buf);
                return EXIT_SUCCESS;
            }
            else
            {
                perror("cat");
                return EXIT_FAILURE;
            }
        }
    }
    else
    {
        perror("cat");
        return EXIT_FAILURE;
    }
}
