#include <stdio.h>

int main()
{
    char buffer[1000];
    const int size = 100, mid = size >> 1;

    char table[size][size] = {};
    int ans = 0;

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

        ans += 2*(table[mid + N][mid + E] ^= 1) - 1;
    }

    printf("%d\n", ans);
}
