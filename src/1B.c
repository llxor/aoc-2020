#include "stdio.h"

int main() {
  const int N = 200;
  int array[N] = {};

  for (int i = 0; i < N; i++) {
    scanf("%d", &array[i]);
  }

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      for (int k = j + 1; k < N; k++) {
        if (array[i] + array[j] + array[k] == 2020) {
          printf("%d\n", array[i] * array[j] * array[k]);
          return 0;
        }
      }
    }
  }
}