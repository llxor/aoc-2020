#include "stdio.h"
#include "string.h"

int main() {
  char buffer[30] = {};
  char group[1000] = {};
  int sum = 0, exit = 0;

  while (!exit) {
    if (fgets(buffer, sizeof buffer, stdin) == NULL) exit = 1;

    if (buffer[0] == '\n' || exit) {
      int table = 0;

      for (char *s = group; *s != '\0'; s++) {
        if ('a' <= *s && *s <= 'z') {
          table |= 1 << (*s - 'a');
        }
      }

      sum += __builtin_popcount(table);
      group[0] = '\0';
    }

    else {
      strcat(group, buffer);
    }
  }

  printf("%d\n", sum);
}