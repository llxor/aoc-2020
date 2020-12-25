#include <stdio.h>

int main()
{
    int val, array[2020] = {};

    while (1) {
        scanf("%d", &val);
        if (array[val]) break;
        array[2020 - val] = 1;
    }

    printf("%d\n", val * (2020 - val));
}
