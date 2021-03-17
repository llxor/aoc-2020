#include <stdio.h>

int main()
{
    const char input[] = "962713854";
    const int length = sizeof input - 1;

    int cups[length];
    for (int i = 0; i < length; i++) cups[i] = input[i] - '0';

    for (int i = 0; i < 100; i++)
    {
        int current = cups[0];
        int t = current - 1, next = -1;
        if (!t) t = 9;

        for (int j = 1; j < length; j++) {
            if (cups[j] == t) {
                if (j < 4) {
                    t -= 1, j = 0;
                    if (!t) t = 9;
                } else {
                    next = j;
                    break;
                }
            }
        }

        int t1 = cups[1], t2 = cups[2], t3 = cups[3];
        for (int i = 4; i <= next; i++) cups[i - 3] = cups[i];

        cups[next - 2] = t1;
        cups[next - 1] = t2;
        cups[next - 0] = t3;

        for (int i = 1; i < length; i++) cups[i - 1] = cups[i];
        cups[length - 1] = current;
    }

    int index;
    for (int i = 0; i < length; i++) {
        if (cups[i] == 1) {
            index = (i + 1) % length;
            break;
        }
    }

    for (int i = index; i != index - 1; i = (i + 1) % length)
        printf("%d", cups[i]);

    printf("\n");
}
