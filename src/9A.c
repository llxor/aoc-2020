#include <stdio.h>

int main()
{
  char buffer[1000];
  int numbers[1000];
  int len = 0;

  while (fgets(buffer, sizeof buffer, stdin) != NULL) {
    sscanf(buffer, "%d", &numbers[len++]);
  }

  int back = 25;

  for (int i = back; i < len; i++) {
    char ok = 0;

    for (int j = i - back; j < i; j++) {
      for (int k = j + 1; k < i; k++) {
        if (numbers[j] + numbers[k] == numbers[i]) {
          ok = 1;
          break;
        }
      }
    }

    if (!ok) {
      printf("%d\n", numbers[i]);
      return 0;
    }
  }
}