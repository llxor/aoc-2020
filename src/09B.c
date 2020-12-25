#import <stdio.h>

int main()
{
  char buffer[1000];
  int numbers[1000];
  int len = 0;

  while (fgets(buffer, sizeof buffer, stdin) != NULL) {
    sscanf(buffer, "%d", &numbers[len++]);
  }

  int target = 257342611;

  for (int i = 0; i < len; i++) {
    int sum = 0;

    for (int j = i; j < len; j++) {
      sum += numbers[j];

      if (sum == target) {
        int min = target, max = 0;

        for (int k = i; k <= j; k++) {
          if (numbers[k] > max) max = numbers[k];
          if (numbers[k] < min) min = numbers[k];
        }

        printf("%d\n", min + max);
        return 0;
      }

      if (sum > target) break;
    }
  }
}
