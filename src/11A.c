#include <stdio.h>
#include <string.h>

int main()
{
  char grid[1000][1000] = {};
  int height = 0, width = 0, change;

  while (fgets(grid[height], sizeof grid[0], stdin) != NULL) {
    height++;
  }

  width = strlen(grid[0]) - 1;
  char flip[height][width];

  do {
    change = 0;
    memset(flip, 0, height * width);

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (grid[i][j] != '.') {
          int is_occupied = grid[i][j] == '#',
              adjacent = 0;

          for (int x = i - 1; x <= i + 1; x++) {
            for (int y = j - 1; y <= j + 1; y++) {
              if ((0 <= x && x < height) && (0 <= y && y < width)) {
                adjacent += (grid[x][y] == '#');
              }
            }
          }

          if (adjacent == 0) {
            flip[i][j] = (change = 1);
          }

          // greater than 4 to include the occupied seat itself 
          else if (adjacent > 4 && is_occupied) {
            flip[i][j] = (change = 1);
          }
        }
      }
    }
    
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (flip[i][j]) {
          if (grid[i][j] == '#') {
             grid[i][j] = 'L';
          } else {
             grid[i][j] = '#';
          }
        }
      }
    }
  } while (change);

  int count = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (grid[i][j] == '#') count++;
    }
  }

  printf("%d\n", count);
}