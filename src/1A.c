#include "stdio.h"

int main() {
  const int N = 200;
  int array[N] = {};

  for (int i = 0; i < N; i++) {
    scanf("%d", &array[i]);
  }

  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (array[i] + array[j] == 2020) {
        printf("%d\n", array[i] * array[j]);
        return 0;
      }
    }
  }

  return 0;
}