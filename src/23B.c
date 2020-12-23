#import <stdio.h>

int main()
{
    char input[] = "962713854";
    const int len = sizeof input - 1;

    // convert all input chars to int
    for (int i = 0; i < len; i++) input[i] -= '0';

    // initialise linked list (ll)
    const int length = 1000000;
    int ll[length + 1];

    ll[0] = -1;
    for (int i = 0; i < len; i++) ll[input[i]] = input[i+1];
    ll[input[len - 1]] = len + 1;
    for (int i = len + 1; i < length; i++) ll[i] = i + 1;
    ll[length] = input[0];

    int current = input[0];

    for (int i = 0; i < 10000000; i++)
    {
        int dest = current - 1;
        if (!dest) dest = length;

        int t1 = ll[current],
            t2 = ll[ll[current]],
            t3 = ll[ll[ll[current]]];

        // check if target is in picked up cups
        int next[] = {t1, t2, t3};
        for (int j = 0; j < 3; j++) {
            if (next[j] == dest) {
                dest--;
                if (!dest) dest = length;
                j = -1;
            }
        }

        // point start to 4th cup
        ll[current] = ll[t3];

        // insert cups after destination
        int end = ll[dest];
        ll[dest] = t1;
        ll[t3] = end;

        current = ll[current];
    }

    printf("%ld\n", (long) ll[1] * ll[ll[1]]);
}
