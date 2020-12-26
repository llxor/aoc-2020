#import <stdio.h>

const int prime = 20201227;

int loop_size(int target)
{
    int val = 1, loop = 0;

    while (val != target)
    {
        val *= 7;
        val %= prime;
        loop++;
    }

    return loop;
}


int loop_from(long s, int n)
{
    long k, v = 1;

    while (n != 0)
    {
        k = (n & 1) ? s : 1;
        v = v * k % prime;
        s = s * s % prime;
        n >>= 1;
    }

    return v;
}


int main()
{
    int keys[2] = {2959251, 4542595};
    int loop = loop_size(keys[0]);
    printf("%d\n", loop_from(keys[1], loop));
}
