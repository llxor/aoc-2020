#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char buffer[1000] = {};
  int numbers[1000] = {};
  int len = 1;

  while (fgets(buffer, sizeof buffer, stdin) != NULL) {
    sscanf(buffer, "%d", &numbers[len++]);
  }

  qsort(numbers, len, sizeof *numbers, strcmp);
  int diff_one = 0, diff_three = 1;

  for (int i = 1; i < len; i++) {
    switch(numbers[i] - numbers[i - 1]) {
      case 1:
        diff_one++;
        break;
      case 3:
        diff_three++;
        break;
    }
  }

  printf("%d\n", diff_one * diff_three);
}
