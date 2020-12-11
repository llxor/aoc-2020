#include <stdio.h>
#include <lib.h>

typedef struct {size_t key; size_t n; struct {int n; size_t key;} inner[100];} entry_t;

int solve(size_t key, entry_t *table, size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    entry_t entry = table[i];
    if (entry.key == key)
    {
      int ans = 1;
      for (size_t j = 0; j < entry.n; j++)
        ans += entry.inner[j].n * solve(entry.inner[j].key, table, len);

      return ans;
    }
  }

  return -1;
}

int main() 
{
  char buffer[1000] = {};
  entry_t table[1000] = {};
  size_t size = 0;

  while (fgets(buffer, sizeof buffer, stdin) != NULL)
  {
    char *words[100] = {};
    size_t len = sizeof words / sizeof words[0];

    size_t _ = split_by_str(words, len, buffer, " bags contain ");
    size_t n = split_by_str(words + 1, len - 1, words[1], ", ");

    if (streql(words[1], "no other bags.\n")) {
      n = 0;
    }

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

  size_t key = hash("shiny") ^ hash("gold");
  printf("%d\n", solve(key, table, size) - 1);
}