#import <stdio.h>
#import <assert.h>

int loop_size(int target)
{
    int val = 1, loop = 0;

    while (val != target)
    {
        val *= 7;
        val %= 20201227;
        loop++;
    }

    return loop;
}


int loop_from(int s, int n)
{
    unsigned long val = 1;

    for (int i = 0; i < n; i++)
    {
        val *= s;
        val %= 20201227;
    }

    return val;
}


int main()
{
    int keys[2] = {};

    for (int i = 0; i < 2; i++)
        scanf("%d", &keys[i]);

    int card_loop = loop_size(keys[0]),
        door_loop = loop_size(keys[1]);

    int key1 = loop_from(keys[1], card_loop),
        key2 = loop_from(keys[0], door_loop);

    assert(key1 == key2 && "keys do not match");
    printf("%d\n", key1);
}
