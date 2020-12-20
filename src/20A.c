#import <stdio.h>
#import <string.h>

const int size = 10;

typedef struct {char grid[size][size]; int id;} tile_t;
typedef struct {unsigned int masks[4], matches;} edges_t;

unsigned int reverse(unsigned int mask) {
  return __builtin_bitreverse32(mask) >> (32 - size);
}


tile_t parse_tile()
{
  tile_t tile = {};

  char buffer[100] = {};
  fgets(buffer, sizeof buffer, stdin);

  sscanf(buffer, "Tile %d:", &tile.id);
  for (int i = 0; i < size; i++) {
    fgets(buffer, sizeof buffer, stdin);
    strncpy(tile.grid[i], buffer, size);
  }

  // clean up trailing line
  fgets(buffer, sizeof buffer, stdin);

  return tile;
}


edges_t get_edges(tile_t *tile)
{
  edges_t edges = {};

  for (int i = 0; i < size; i++) {
    unsigned int mask = 1 << i; 
    if (tile->grid[i][0] == '#') edges.masks[0] |= mask;
    if (tile->grid[i][9] == '#') edges.masks[1] |= mask;
  } 

  for (int j = 0; j < size; j++) {
    unsigned int mask = 1 << j; 
    if (tile->grid[0][j] == '#') edges.masks[2] |= mask;
    if (tile->grid[9][j] == '#') edges.masks[3] |= mask;
  }

  return edges;
}


int main()
{
  const int len = 144;
  tile_t tiles[len];
  edges_t edges[len];

  // get all tiles and pre-compute edges 
  for (int i = 0; i < len; i++)
  {
    tiles[i] = parse_tile();
    edges[i] = get_edges(&tiles[i]);
  }

  for (int i = 0; i < len; i++) {
    for (int j = 0; j < i; j++) {
      if (i != j) {
        for (int k = 0; k < 4; k++) {
          for (int l = 0; l < 4; l++) {
            unsigned int our = edges[i].masks[k],
                       their = edges[j].masks[l];

            if (our == their || our == reverse(their)) {
              edges[i].matches++;
              edges[j].matches++;
            }
          }
        }
      }
    }
  }

  unsigned long ans = 1;

  for (int i = 0; i < len; i++) {
    if (edges[i].matches == 2) {
      ans *= tiles[i].id;
    }
  }

  printf("%lu\n", ans);
}