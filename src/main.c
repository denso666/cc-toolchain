#include "chown/chown.h"
#include "cp/cp.h"
#include "ls/ls.h"
#include "utils/utils.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

int menu(void);

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
    if (ls(path) == EXIT_FAILURE) {
      perror("ls error");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }

  if (opt == 2) {
    char source[PATH_MAX];
    printf("Dirección a copiar > ");
    char *read_source = fgets(source, PATH_MAX, stdin);
    char dest[PATH_MAX];
    printf("Dirección de destino > ");
    char *read_dest = fgets(dest, PATH_MAX, stdin);
    printf("Recusivo (Y/n) > ");
    char in = getchar();
    clean_buffer();
    int r_flag = 0;
    if (in == 'Y' || in == 'y') {
      r_flag = 1;
    }
    if (cp(read_source, read_dest, r_flag) == EXIT_FAILURE) {
      perror("cp error");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }

  if (opt == 3) {
    char source[PATH_MAX];
    printf("Dirección del archivo > ");
    char *read_source = fgets(source, PATH_MAX, stdin);
    char owners[PATH_MAX];
    printf("Nuevo dueño (usuario:grupo) > ");
    char *read_owners = fgets(owners, PATH_MAX, stdin);
    if (custom_chown(read_source, read_owners) == EXIT_FAILURE) {
      perror("cp error");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
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
