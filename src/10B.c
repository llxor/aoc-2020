#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
  return *(int*)a - *(int*)b;
}

char saved[1000] = {};
size_t table[1000] = {};

size_t combinations(int array[], int len)
{
  if (len == 1) {
    return 1;
  }

  int v = array[0];
  size_t total = 0;

  if (saved[v]) {
    return table[v];
  }

  for (int i = 1; i < len; i++) {
    if (array[i] - v <= 3) {
      total += combinations(&array[i], len - i);
    } else {
      break;
    }
  }

  saved[v] = 1;
  return (table[v] = total);
}

int main()
{
  char buffer[1000] = {};
  int numbers[1000] = {};
  int len = 1;

  while (fgets(buffer, sizeof buffer, stdin) != NULL) {
    sscanf(buffer, "%d", &numbers[len++]);
  }

  qsort(numbers, len, sizeof *numbers, cmp);
  printf("%zu\n", combinations(numbers, len)); 
}