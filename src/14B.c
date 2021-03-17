#include <stdio.h>
#include <assert.h>

typedef struct {long keys[100], values[100], len;} entry_t;
const long size = (1 << 12);

void combinations(long floating, long reg, long val, entry_t mem[])
{
    if (floating == 0) {
        long add = reg % size,
             len = mem[add].len;

        search:
        for (int i = 0; i < len; i++) {
            if (mem[add].keys[i] == reg) {
                mem[add].values[i] = val;
                return;
            }
        }

        if (len == 100) {
            add += 1;
            add %= size;
            len = mem[add].len;
            goto search;
        }

        mem[add].keys[len] = reg;
        mem[add].values[len] = val;
        mem[add].len++;
        return;
    }

    long next = floating & (floating - 1);
    long bit = floating ^ next;

    combinations(next, reg, val, mem);
    combinations(next, reg ^ bit, val, mem);
}


int main()
{
    char buffer[1000];
    entry_t mem[size] = {};
    long reg, val, floating, ormask;

    while (fgets(buffer, sizeof buffer, stdin) != NULL)
    {
        if (buffer[1] == 'a') // mask
        {
            ormask = 0, floating = 0;

            for (int i = 0; i < 36; i++) {
                long bit = 1l << (35 - i);
                if (buffer[i+7] == 'X') floating ^= bit;
                if (buffer[i+7] == '1')   ormask ^= bit;
            }
        }

        else // mem
        {
            sscanf(buffer, "mem[%lu] = %lu", &reg, &val);
            reg |= ormask;
            combinations(floating, reg, val, mem);
        }
    }

    long sum = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < mem[i].len; j++) {
            sum += mem[i].values[j];
        }
    }

    printf("%ld\n", sum);
}
