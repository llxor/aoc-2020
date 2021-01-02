#import <stdio.h>

const int prime = 20201227;

int loop_size(int target)
{
    int loop = 0;

    for (int val = 1; val != target; loop++) {
        val = val * 7 % prime;
    }

    return loop;
}


int loop_from(long s, int l)
{
    long k, v = 1;

    for (int n = l; n != 0; n >>= 1) {
        k = (n & 1) ? s : 1;
        v = v * k % prime;
        s = s * s % prime;
    }

    return v;
}


int main()
{
    int keys[2] = {2959251, 4542595};
    int loop = loop_size(keys[0]);
    printf("%d\n", loop_from(keys[1], loop));
}
