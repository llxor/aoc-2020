#import <stdio.h>

int main()
{
    char buffer[1000];
    const int size = 500, mid = size >> 1;

    char table[size][size] = {};
    int minN = size, maxN = -1, minE = size, maxE = -1;

    while (fgets(buffer, sizeof buffer, stdin) != NULL)
    {
        int N = 0, E = 0;

        for (int i = 0; buffer[i] != '\n'; i++)
        {
                 if (buffer[i] == 'e') E += 2;
            else if (buffer[i] == 'w') E -= 2;
            else if (buffer[i] == 'n') { N++; if (buffer[++i] == 'e') E++; else E--; }
            else if (buffer[i] == 's') { N--; if (buffer[++i] == 'e') E++; else E--; }
        }

        N += mid;
        E += mid;

             if (N < minN) minN = N;
        else if (N > maxN) maxN = N;

             if (E < minE) minE = E;
        else if (E > maxE) maxE = E;

        table[N][E] ^= 1;
    }

    char dirs[6][2] = {{0,2}, {0,-2}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    unsigned int black;

    for (int iter = 0; iter < 100; iter++)
    {
        char tmp[size][size] = {};

        minN -= 1;
        maxN += 1;
        minE -= 2;
        maxE += 2;

        for (int N = minN; N <= maxN; N++) {
            for (int E = minE; E <= maxE; E++) {
                if ((N & 1) == (E & 1))
                {
                    int nbors = 0;

                    for (int i = 0; i < 6; i++) {
                        int dN = dirs[i][0], dE = dirs[i][1];
                        nbors += table[N + dN][E + dE];
                    }

                    if (table[N][E]) {
                        tmp[N][E] = nbors == 0 || nbors > 2;
                    } else {
                        tmp[N][E] = nbors == 2;
                    }
                }
            }
        }

        black = 0;

        for (int N = minN; N <= maxN; N++) {
            for (int E = minE; E <= maxE; E++) {
                if ((N & 1) == (E & 1)) {
                    if (tmp[N][E]) table[N][E] ^= 1;
                    black += table[N][E];
                }
            }
        }
    }

    printf("%d\n", black);
}
