#include <stdio.h>
#include <string.h>

int main()
{
  const int depth = 323;
  char grid[depth][100];

  for (int i = 0; i < depth; i++) {
    fgets(grid[i], sizeof grid[i], stdin);
  }

  int width = strlen(grid[0]) - 1;
  int x = 0, y = 0, count = 0;

  do {
    if (grid[y][x] == '#') {
      count++;
    }

    x = (x + 3) % width;
    y++;
  } while (y < depth);

  printf("%d\n", count);
}
