#import <stdio.h>
#import <stdlib.h>

int main() {
  const int size = 30000000; // change to 2020 for part 1
  int input[6] = {1, 12, 0, 20, 8, 16};
  int *hist = calloc(size, sizeof(int));

  for (int i = 0; i < 6; i++) {
    hist[input[i]] = i + 1;
  }

  int curr = 0;

  for (int t = 7; t < size; t++) {
    int h = hist[curr];
    hist[curr] = t;
    curr = h ? t - h : 0;
  }

  printf("%d\n", curr);
  free(hist);
}
