#include <stdio.h>

int menu(void);

int main()
{
    int opt = menu();

    if (opt == 1)
    {
        printf("You select '1'\n");
    }
    else
    {
        printf("Command not found :(\n");
    }

    return 0;
}

int menu(void)
{
    printf("CC-TOOLCHAIN\n");
    printf("1. command_1\n");
    printf("2. command_2\n");
    printf("3. command_3\n");
    printf("n. command_n\n");
    printf("? ");
    
    char in = getchar();
    if (in != EOF)
    {
        in -= '0';
        if (in >= 0 && in <= 9) return (int) in;
    }
    return -1;
}
