#include <stdio.h>
#include <string.h>

int main()
{
  int timestamp, numbers[100], len = 0, counts[100], count = 0;
  char buffer[1000], *tok, *src = buffer;

  scanf("%d\n", &timestamp); // ingored
  fgets(buffer, sizeof buffer, stdin);

  while ((tok = strtok(src, ","))) {
    if (*tok != 'x') {
      counts[len] = count;
      sscanf(tok, "%d", &numbers[len++]);
    }
    src = NULL;
    count++;
  }

  long t = 0, jump = numbers[0];

  for (int i = 1; i < len; i++) {
    int c = counts[i],
        n = numbers[i];

    while ((t + c) % n != 0) t += jump;
    jump *= n;
  }

  printf("%ld\n", t);
}