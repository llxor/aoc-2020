#include <stdio.h>
#include <stdlib.h>

int main()
{
  char buffer[100] = {};
  char instr;
  int X = 0, Y = 0, N;

  typedef enum { NORTH, EAST, SOUTH, WEST } direction;
  direction D = EAST;

  while (fgets(buffer, sizeof buffer, stdin) != NULL)
  {
    sscanf(buffer, "%c%d", &instr, &N);

    switch(instr) {
      case 'N': { N: Y += N; break; }
      case 'E': { E: X += N; break; }
      case 'S': { S: Y -= N; break; }
      case 'W': { W: X -= N; break; }
      case 'L': { D = (4 + (D - N / 90)) % 4; break; }
      case 'R': { D = (4 + (D + N / 90)) % 4; break; }
      case 'F': { 
        switch (D) {
          case NORTH: { goto N; }
          case  EAST: { goto E; }
          case SOUTH: { goto S; }
          case  WEST: { goto W; }
        }
      }
    }
  }

  printf("%d\n", abs(X) + abs(Y));
}