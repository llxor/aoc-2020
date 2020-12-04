#include "stdio.h"
#include "string.h"

int main() {
  char buffer[1000] = "";
  char passport[1000] = "";
  int count = 0, exit = 0;

  while (!exit) {
    while (1) {
      if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        exit = 1;
        break;
      }
      if (buffer[0] == '\n') {
        break;
      }
      strcat(passport, buffer);
    }

    int length = 0;
    char *tokens[100] = {}, *ptr = &passport[0];

    for (int i = 0; i < sizeof passport; i++) {
      if (passport[i] == '\0') {
        break;
      }

      if ((passport[i] == ' ') || (passport[i] == '\n') || (passport[i] == ':')) {
        tokens[length++] = ptr;
        passport[i] = '\0';
        ptr = &passport[i + 1];
      }
    }

    if (length == 16) {
      count++;
    }

    else if (length == 14) {
      int flag = 1;

      for (int i = 0; i < length; i += 2) {
        if (strcmp(tokens[i], "cid") == 0) {
          flag = 0;
          break;
        }
      }

      if (flag) {
        count++;
      } 
    }

    passport[0] = '\0';
  }

  printf("%d\n", count);
}