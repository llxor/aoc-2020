#import <stdio.h>

int main()
{
    char buffer[1000];
    long mem[1 << 16];
    long reg, val, andmask, ormask;

    int len = 0, add[500];

    while (fgets(buffer, sizeof buffer, stdin) != NULL)
    {
        if (buffer[1] == 'a') // mask
        {
            ormask = 0, andmask = (1l << 36) - 1;

            for (int i = 0; i < 36; i++) {
                long bit = 1l << (35 - i);
                if (buffer[i+7] == '0') andmask ^= bit;
                if (buffer[i+7] == '1')  ormask ^= bit;
            }
        }

        else // mem
        {
            sscanf(buffer, "mem[%ld] = %ld", &reg, &val);
            val &= andmask;
            val |= ormask;
            mem[reg] = val;
            add[len++] = reg;
        }
    }

    long sum = 0;

    for (int i = 0; i < len; i++) {
        sum += mem[add[i]];
        mem[add[i]] = 0;
    }

    printf("%ld\n", sum);
}
