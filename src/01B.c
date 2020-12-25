#import <stdio.h>

int main()
{
    int val, len = 0, nums[200], array[2020] = {};

    while (1) {
        scanf("%d", &val);

        for (int i = 0; i < len; i++)
        {
            int target = 2020 - val - nums[i];

            if (target > 0 && array[target]) {
                printf("%d\n", val * nums[i] * target);
                return 0;
            }
        }

        array[val] = 1;
        nums[len++] = val;
    }
}
