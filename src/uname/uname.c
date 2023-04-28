#include "./uname.h"

int __uname__(void)
{
    struct utsname buf;
    if (!uname(&buf))
    {
        fprintf(stdout, "Name\t\t%s\n", buf.sysname);
        fprintf(stdout, "Release\t\t%s\n", buf.release);
        fprintf(stdout, "Version\t\t%s\n", buf.version);
        fprintf(stdout, "Proccesor\t%s\n", buf.machine);
        return 0;
    }
    else
    {
        perror("uname");
        return 1;
    }
}
