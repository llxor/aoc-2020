#include <stdio.h>
#include <lib.h>

const int N = 37;

struct array {
  char *words[100], len;
};

int indexOf(struct array arr, char *item) {
  if (item == NULL) {
    return -1;
  }

  for (int i = 0; i < arr.len; i++) {
    if (streql(arr.words[i], item)) {
      return i;
    }
  }

  return -1;
}

void flatten(int len, struct array alle[len], struct array *all) {
   for (int i = 0; i < len; i++) {
    for (int j = 0; j < alle[i].len; j++) {
      char *word = alle[i].words[j], found = 0;

      if (word == NULL) {
        continue;
      }

      for (int k = 0; k < all->len; k++) {
        if (streql(word, all->words[k])) {
          found = 1;
          break;
        }
      }

      if (!found) all->words[all->len++] = word;
    }
  }
}

void solve(struct array ingr[N], struct array alle[N], struct array all, struct array table[]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < alle[i].len; j++) {
      int index = indexOf(all, alle[i].words[j]);

      if (table[index].len == 0) {
        for (int k = 0; k < ingr[i].len; k++) {
          table[index].words[table[index].len++] = ingr[i].words[k];
        }
      }

      else {
        for (int k = 0; k < table[index].len; k++) {
          int ind = indexOf(ingr[i], table[index].words[k]);

          if (ind == -1) {
            table[index].words[k] = NULL;
          }
        }
      }
    }
  }
}

int main() {
  char ingredients[N][1000] = {}, allergens[N][1000];
  struct array ingr[N] = {}, alle[N] = {};
  struct array all = {};

  for (int i = 0; i < N; i++) {
    char buffer[1000];
    fgets(buffer, sizeof buffer, stdin);

    sscanf(buffer, "%[^(](contains %[^)])", ingredients[i], allergens[i]);
    ingr[i].len = split_by_str(ingr[i].words, 100, ingredients[i], " ") - 1;
    alle[i].len = split_by_str(alle[i].words, 100, allergens[i], ", ");
  }

  flatten(N, alle, &all);
  struct array table[8] = {};
  solve(ingr, alle, all, table);

  struct array must = {};
  flatten(8, table, &must);

  int count = 0;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < ingr[i].len; j++) {
      int index = indexOf(must, ingr[i].words[j]);

      if (index == -1) {
        count++;
      }
    }
  }

  printf("%d\n", count);
}
