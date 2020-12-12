#include <stdio.h>
#include <stdlib.h>

int main()
{
  char buffer[100] = {};
  char instr;
  int X = 0, Y = 0, WX = 10, WY = 1, N, angle;

  int sin[4] = {0, 1, 0, -1};
  int cos[4] = {1, 0, -1, 0};

  while (fgets(buffer, sizeof buffer, stdin) != NULL)
  {
    sscanf(buffer, "%c%d", &instr, &N);
    angle = 0;

    switch(instr) {
      case 'N': { WY += N; break; }
      case 'E': { WX += N; break; }
      case 'S': { WY -= N; break; }
      case 'W': { WX -= N; break; }
      case 'L': { angle = (4 + N/90) % 4; break; }
      case 'R': { angle = (4 - N/90) % 4; break; }
      case 'F': { X += N * WX; Y += N * WY; break; }
    }

    int NX = WX * cos[angle] - WY * sin[angle],
        NY = WX * sin[angle] + WY * cos[angle]; 

    WX = NX, WY = NY;
  }

  printf("%d\n", abs(X) + abs(Y));
}