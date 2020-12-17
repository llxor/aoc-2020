#import <stdio.h>

int main()
{
  const int size = 20;
  char grid[size][size][size][size] = {};
  char next[size][size][size][size] = {};

  int min_width = size/2 - 3, max_width = size/2 + 4,
      min_height = min_width, max_height = max_width,
      min_depth = size/2, max_depth = size/2,
      min_forth = min_depth, max_forth = max_depth,
      active = 0;

  char buffer[100] = {};

  for (int i = min_height; i <= max_height; i++) {
    fgets(buffer, sizeof buffer, stdin);
    for (int j = min_width; j <= max_width; j++) {
      grid[min_forth][min_depth][i][j] = buffer[j - min_width];
      next[min_forth][min_depth][i][j] = buffer[j - min_width];
      active += buffer[j - min_width] == '#';
    }
  }

  for (int simul = 0; simul < 6; simul++) {
    for (int f = min_forth - 1; f <= max_forth + 1; f++) {
      for (int i = min_depth - 1; i <= max_depth + 1; i++) {
        for (int j = min_height - 1; j <= max_height + 1; j++) {
          for (int k = min_width - 1; k <= max_width + 1; k++) {
            char value = grid[f][i][j][k];
            int count = 0;

            for (int fi = -1; fi <= 1; fi++)
              for (int di = -1; di <= 1; di++)
                for (int dj = -1; dj <= 1; dj++)
                  for (int dk = -1; dk <= 1; dk++)
                    count += grid[f+fi][i+di][j+dj][k+dk] == '#';

           if (value == '#') {
             count--;
             if (count != 2 && count != 3) {
               next[f][i][j][k] = '.';
               active--;
             }
           }

           else {
             if (count == 3) {
               next[f][i][j][k] = '#';
               active++;
               if (f < min_forth) min_forth = f;
               if (f > max_forth) max_forth = f;
               if (i < min_depth) min_depth = i;
               if (i > max_depth) max_depth = i;
               if (j < min_height) min_height = j;
               if (j > max_height) max_height = j;
               if (k < min_width) min_width = k;
               if (k > max_width) max_width = k;
             }
           }
         }
       }
     }
    }

    for (int f = min_forth; f <= max_forth; f++)
      for (int i = min_depth; i <= max_depth; i++)
        for (int j = min_height; j <= max_height; j++)
          for (int k = min_width; k <= max_width; k++)
            grid[f][i][j][k] = next[f][i][j][k]; 
  }

  printf("%d\n", active);
}