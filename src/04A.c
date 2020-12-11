#include <stdio.h>
#include <string.h>
#include <lib.h>

int main() {
  char buffer[1000] = "";
  char passport[1000] = "";
  int count = 0, exit = 0;

  while (!exit) {
    passport[0] = '\0';

    // read in passport
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

    // split into tokens
    char *tokens[100] = {};
    int length = split_by_chars(tokens, 100, passport, " :\n") - 1;

    // check tokens
    if (length >= 14) {
      int flag = 1;

      if (length == 14) {
        for (int i = 0; i < length; i += 2) {
          if (streql(tokens[i], "cid")) {
            flag = 0;
            break;
          }
        }
      }

      if (flag) {
        count++;
      }
    }
  }

  printf("%d\n", count);
}