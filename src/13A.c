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

  int ans, t = numbers[0];

  for (int i = 0; i < len; i++) {
    int p = numbers[i] - (timestamp % numbers[i]);
    if (p < t) {
      t = p, ans = p * numbers[i];
    }
  }

  printf("%d\n", ans);
}