#import <stdio.h>
#import <string.h>

int main()
{
  const int depth = 323;
  char grid[depth][100];

  for (int i = 0; i < depth; i++) {
    fgets(grid[i], sizeof grid[i], stdin);
  }

  int width = strlen(grid[0]) - 1;
  long product = 1;

  int dir[5][2] = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

  for (int i = 0; i < 5; i++) {
    int count = 0, x = 0, y = 0;
    do {
      if (grid[y][x] == '#') {
        count++;
      }

      x = (x + dir[i][0]) % width;
      y += dir[i][1];
    } while (y < depth);

    product *= count;
  }

  printf("%ld\n", product);
}
