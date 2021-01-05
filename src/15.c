#import <stdio.h>
#import <stdlib.h>

// change to 2020 for part 1
const int size = 30000000;
char set[size >> 3] = {};

int contains(int x) { return (set[x >> 3] >> (x & 7)) & 1; }
void insert(int x) { set[x >> 3] |= 1 << (x & 7); }

int main() {
  int input[6] = {1, 12, 0, 20, 8, 16};
  int *hist = calloc(size, sizeof(int));

  for (int i = 0; i < 6; i++) {
    hist[input[i]] = i + 1;
    insert(input[i]);
  }

  int curr = 0;

  for (int t = 7; t < size; t++) {
    int c = curr;
    curr = contains(c) ? t - hist[c] : 0;

    hist[c] = t;
    insert(c);
  }

  printf("%d\n", curr);
  free(hist);
}
