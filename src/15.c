#import <stdio.h>
#import <stdlib.h>

int main()
{
    const int size = 30000000;
    int input[6] = {1,12,0,20,8,16},
        *hist = calloc(size, sizeof(int));

    int current = 0,
           next = 0,
           turn = 1;

    for (int i = 0; i < 6; i++)
        hist[input[i]] = turn++;

    while (turn < size) {
        if (turn == 2020)
            printf("Part 1: %d\n", current);
        next = (turn - hist[current]) % turn;
        hist[current] = turn++;
        current = next;
    }

    printf("Part 2: %d\n", current);
    free(hist);
}
