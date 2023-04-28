#include "ls/ls.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

int menu(void);

void clean_buffer() {
  while (getchar() != '\n');
}

int main() {
  int opt = menu();

  if (opt == 1) {
    printf("Directorio a listar > ");
    char path[PATH_MAX];
    char *read_path = fgets(path, PATH_MAX, stdin);
    if (read_path != NULL) {
      int len = strlen(read_path);
      read_path[len - 1] = '\0';
    }
    if(ls(path) == EXIT_FAILURE){
        perror("ls error");
        return EXIT_FAILURE;
    }
  }

  if (opt == -1) {
    printf("Command not found :(\n");
    return -1;
  }

  return 0;
}

int menu(void) {
  printf("CC-TOOLCHAIN\n");
  printf("1. ls\n");
  printf("2. cp\n");
  printf("3. chown\n");
  printf("n. command_n\n");
  printf("? ");

  char in = getchar();
  clean_buffer();
  if (in != EOF) {
    in -= '0';
    if (in >= 0 && in <= 9)
      return (int)in;
  }
  return -1;
}
