#include "stdio.h"
#include "string.h"

int binary_search(const char *code, size_t len, const char *key) {
  char lower = key[0], upper = key[1];
  int min = 0, max = (1 << len) - 1;

  for (int i = 0; i < len; i++) {
    if (code[i] == lower) max = (min + max) >> 1;
    else if (code[i] == upper) min = (min + max + 1) >> 1;
    else return -1;
  }

  return min;
}

int main() {
  char buffer[100] = {};
  int table[1024] = {};
  int N = 859, len = sizeof table / sizeof table[0];

  for (int i = 0; i < N; i++) {
    fgets(buffer, sizeof buffer, stdin);
    int row = binary_search(buffer, 7, "FB"),
        col = binary_search(buffer + 7, 3, "LR");

    int id = 8 * row + col;
    table[id] = 1;
  }

  for (int i = 1; i < len - 1; i++) {
    if (!table[i] && table[i - 1] && table[i + 1]) {
      printf("%d\n", i);
      return 0;
    }
  }
}