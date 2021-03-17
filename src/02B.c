#include <stdio.h>

int main()
{
  int min, max, count = 0;
  char c, password[100] = {};
  char buffer[1000] = {};

  for (int i = 0; i < 1000; i++) {
    int lettercount = 0;

    fgets(buffer, sizeof buffer, stdin);
    sscanf(buffer, "%d-%d %c: %s", &min, &max, &c, password);

    if ((password[min-1] == c) ^ (password[max-1] == c)) {
      count++;
    }
  }

  printf("%d\n", count);
}
