#import <stdio.h>
#import <string.h>

int binary_search(const char *code, size_t len, const char *key)
{
  char lower = key[0], upper = key[1];
  int min = 0, max = (1 << len) - 1;

  for (int i = 0; i < len; i++) {
    if (code[i] == lower) max = (min + max) >> 1;
    else if (code[i] == upper) min = (min + max + 1) >> 1;
    else return -1;
  }

  return min;
}


int main()
{
  char buffer[100] = {};
  int max = 0, N = 859;

  for (int i = 0; i < N; i++) {
    fgets(buffer, sizeof buffer, stdin);
    int row = binary_search(buffer, 7, "FB"),
        col = binary_search(buffer + 7, 3, "LR");

    int id = 8 * row + col;
    if (id > max) max = id;
  }

  printf("%d\n", max);
}
