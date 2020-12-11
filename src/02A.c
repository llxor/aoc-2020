#include <stdio.h>

int main() {
  int min, max, count = 0;
  char c, password[100] = {};
  char buffer[1000] = {};

  for (int i = 0; i < 1000; i++) {
    int lettercount = 0;

    fgets(buffer, sizeof buffer, stdin);
    sscanf(buffer, "%d-%d %c: %s", &min, &max, &c, password);

    for (int j = 0; j < sizeof password; j++) {
      if (password[j] == c) lettercount++;
      if (password[j] == 0) break;
    }

    if (min <= lettercount && lettercount <= max) {
      count++;
    }
  }

  printf("%d\n", count);
}