#include <stdio.h>
#include <math.h>

const int prime = 20201227;
int table[prime] = {};

int loop_from(long s, int l)
{
    long v = 1;

    for (int n = l; n != 0; n >>= 1) {
        if (n & 1)
        v = v * s % prime;
        s = s * s % prime;
    }

    return v;
}

int loop_size(int target)
{
    int a = 7, b = target, n = sqrt(prime) + 1;

    for (int p = 1; p <= n; p++) {
        int index = loop_from(a,p*n);
        table[index] = p;
    } 

    for (int q = 0; q <= n; q++) {
        int t = (long) loop_from(a,q) * b % prime;
        if (table[t]) {
            return table[t] * n - q;
        }
    }

    return -1;
}

int main()
{
    int keys[2] = {2959251, 4542595};
    int loop = loop_size(keys[0]);
    printf("%d\n", loop_from(keys[1], loop));
}
