#include <stdio.h>
#include <string.h>

int main()
{
  int timestamp, numbers[100], len = 0;
  char buffer[1000], *tok, *src = buffer;

  scanf("%d\n", &timestamp);
  fgets(buffer, sizeof buffer, stdin);

  while ((tok = strtok(src, ","))) {
    if (*tok != 'x') {
      sscanf(tok, "%d", &numbers[len++]);
    }
    src = NULL;
  }

  for (int t = timestamp;; t++) {
    for (int i = 0; i < len; i++) {
      if (t % numbers[i] == 0) {
        printf("%d\n", (t - timestamp) * numbers[i]);
        return 0;
      }
    }
  }
}