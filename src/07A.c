#include <stdio.h>
#include <lib.h>

typedef struct {size_t key; size_t n; struct {int n; size_t key;} inner[100];} entry_t;

int main()
{
  char buffer[1000] = {};
  entry_t table[1000] = {};
  size_t size = 0;

  while (fgets(buffer, sizeof buffer, stdin) != NULL)
  {
    const int len = 100;
    char *words[len] = {};

    size_t _ = split_by_str(words, len, buffer, " bags contain ");
    size_t n = split_by_str(words + 1, len - 1, words[1], ", ");

    if (streql(words[1], "no other bags.\n")) n = 0;

    char adj[100] = {};
    char color[100] = {};

    sscanf(words[0], "%s %s", adj, color);
    size_t key = hash(adj) ^ hash(color);
    entry_t outer = {.n = n, .key = key};

    for (size_t i = 1; i <= n; i++)
    {
      int d;
      sscanf(words[i], "%d %s %s", &d, adj, color);
      size_t key = hash(adj) ^ hash(color);
      outer.inner[i-1].n = d;
      outer.inner[i-1].key = key;
    }

    table[size++] = outer;
  }

  char success[size];
  size_t cache[size];
  size_t cache_len = 1, last,
         key = hash("shiny") ^ hash("gold");
  cache[0] = key;

  for (size_t i = 0; i < size; i++) success[i] = 0;

  do {
    last = cache_len;
    for (size_t i = 0; i < size; i++)
    {
      if (!success[i])
      {
        entry_t entry = table[i];
        for (size_t j = 0; j < entry.n; j++)  // for each sub color
          for (size_t k = 0; k < cache_len; k++) // for each target color
            if (entry.inner[j].key == cache[k])
            {
              cache[cache_len++] = entry.key;
              success[i] = 1;
              goto next;
            }
      }
      next: continue;
    }
  } while (last != cache_len);

  printf("%zu\n", cache_len - 1);
}
