#import <stdio.h>
#import <string.h>

const int size = 10;
typedef enum {LEFT, RIGHT, TOP, BOTTOM} dir_t; 

typedef struct {char grid[size][size]; int id;} tile_t;
typedef struct {unsigned int masks[4], matches, nbors[4];} edges_t;

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
  edges_t edges = {.nbors = {[0 ... 3] = -1}};

  for (int i = 0; i < size; i++) {
    unsigned int mask = 1 << i;
    if (tile->grid[i][0] == '#') edges.masks[LEFT] |= mask;
    if (tile->grid[i][9] == '#') edges.masks[RIGHT] |= mask;
  } 

  for (int j = 0; j < size; j++) {
    unsigned int mask = 1 << j; 
    if (tile->grid[0][j] == '#') edges.masks[TOP] |= mask;
    if (tile->grid[9][j] == '#') edges.masks[BOTTOM] |= mask;
  }

  return edges;
}


void match_edges(tile_t tiles[], edges_t edges[], int len)
{
  for (int i = 0; i < len; i++)
    for (int j = 0; j < i; j++)
      if (i != j)
        for (int k = 0; k < 4; k++)
          for (int l = 0; l < 4; l++) {
            unsigned int our = edges[i].masks[k],
                       their = edges[j].masks[l];

            if (our == their || our == reverse(their)) {
              edges[i].matches++;
              edges[i].nbors[k] = j;
              edges[j].matches++;
              edges[j].nbors[l] = i;
            }
          }
}

// rotates tile clockwise
tile_t rotate_tile(tile_t *tile)
{
  tile_t res = {.id = tile->id};

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int ni = j, nj = size - 1 - i;
      res.grid[ni][nj] = tile->grid[i][j];
    }
  }

  return res;
}

// flip tile along i = j
tile_t flip_tile(tile_t *tile)
{
  tile_t res = {.id = tile->id};

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      res.grid[j][i] = tile->grid[i][j];
    }
  }

  return res;
}

// rotate edges clockwise with tile
edges_t rotate_edges(edges_t *edges)
{
  edges_t res = {.matches = edges->matches};

  int swap[4] = {3,2,0,1};

  for (int i = 0; i < 4; i++) {
    res.masks[i] = edges->masks[swap[i]];
    res.nbors[i] = edges->nbors[swap[i]];
  }

  return res;
}

// flip edges of tile in i = j
edges_t flip_edges(edges_t *edges)
{
  edges_t res = {.matches = edges->matches};

  int swap[4] = {2,3,0,1};

  for (int i = 0; i < 4; i++) {
    res.masks[i] = edges->masks[swap[i]];
    res.nbors[i] = edges->nbors[swap[i]];
  }

  return res;
}

// solve jigsaw piece with (i,j) coord and kth tile
void solve(int side, int grid[side][side], tile_t tiles[], edges_t edges[], int i, int j, int k)
{
  // put piece in grid
  grid[i][j] = k;

  // matching pieces
  int above = (i == 0) ? -1 : grid[i - 1][j],
       left = (j == 0) ? -1 : grid[i][j - 1];

  // orientate tile to loosely match these conditions
  while (!((edges[k].nbors[LEFT] == left && edges[k].nbors[TOP] == above) || 
           (edges[k].nbors[LEFT] == above && edges[k].nbors[TOP] == left)))
  {
    tiles[k] = rotate_tile(&tiles[k]);
    edges[k] = rotate_edges(&edges[k]);
  }

  // flip tile if edges are wrong way around
  if (i + j == 0 || edges[k].nbors[LEFT] != left)
  {
    tiles[k] = flip_tile(&tiles[k]);
    edges[k] = flip_edges(&edges[k]);
  }

  if (j != side - 1) {
    solve(side, grid, tiles, edges, i, j + 1, edges[k].nbors[RIGHT]);
  }

  else if (i != side - 1) {
    solve(side, grid, tiles, edges, i + 1, 0, edges[grid[i][0]].nbors[BOTTOM]);
  }
}

// density = number of '#'s in sea monster
const int width = 20, height = 3, density = 15;
const char sea_monster[height][width] = {
  "                  # ",
  "#    ##    ##    ###",
  " #  #  #  #  #  #   ",
};

// count number of monsters in puzzle
int find(int side, char puzzle[side][side], int final)
{
  int found = 0;

  // iterate over all possible starting points
  for (int i = 0; i < side - height; i++) {
    for (int j = 0; j < side - width; j++) {
      // check if it is monster
      for (int k = 0; k < height; k++) {
        for (int l = 0; l < width; l++) {
          if (sea_monster[k][l] == '#' && puzzle[i+k][j+l] != '#') {
            goto end; // continue to next starting point
          }
        }
      }

      // if monster found
      found++;

      end: continue;
    }
  }

  if (found || final) return found;

  // rotate or flip puzzle and solve new puzzle
  char flipped[side][side], rotated[side][side];

  for (int i = 0; i < side; i++) {
    for (int j = 0; j < side; j++) {
      int ni = j, nj = i;
      flipped[ni][nj] = puzzle[i][j];
      rotated[ni][side - 1 - nj] = puzzle[i][j];
    }
  }

  int try = find(side, flipped, 1);
  return try ? try : find(side, rotated, 0);
}


int main()
{
  const int side = 12;
  const int len = side * side;
  tile_t tiles[len];
  edges_t edges[len];

  // get all tiles and pre-compute edges 
  for (int i = 0; i < len; i++)
  {
    tiles[i] = parse_tile();
    edges[i] = get_edges(&tiles[i]);
  }

  match_edges(tiles, edges, len);
  int grid[side][side] = {};

  // solve puzzle starting from a corner
  for (int i = 0; i < len; i++) {
    if (edges[i].matches == 2) {
      solve(side, grid, tiles, edges, 0, 0, i);
      break;
    }
  }

  // flatten puzzle pieces in grid
  const int puzzle_size = side * (size - 2);
  char puzzle[puzzle_size][puzzle_size] = {}; 

  for (int i = 0; i < side; i++) {
    for (int j = 0; j < side; j++) {
      tile_t *tile = &tiles[grid[i][j]];
      int koffset = i * (size - 2), loffset = j * (size - 2);

      for (int k = 1; k < size - 1; k++) {
        for (int l = 1; l < size - 1; l++) {
          puzzle[k + koffset - 1][l + loffset - 1] = tile->grid[k][l];
        }
      }
    }
  }

  // count '#'s in puzzle
  int count = 0;
  for (int i = 0; i < puzzle_size; i++) {
    for (int j = 0; j < puzzle_size; j++) {
      count += puzzle[i][j] == '#';
    }
  }

  int monsters = find(puzzle_size, puzzle, 0);
  printf("%d\n", count - monsters * density);
}