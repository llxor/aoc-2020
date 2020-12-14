import Stdio;

void combinations(int floating, int reg, int val, mapping mem) {
  if (floating == 0) {
    mem[reg] = val;
    return;
  }

  int next = floating & (floating - 1);
  int bit = floating ^ next;

  combinations(next, reg, val, mem);
  combinations(next, reg ^ bit, val, mem);
}

int main() {
  string line;
  int ormask, floating;
  mapping mem = ([]);

  while ((line = stdin->gets())) {
    if (line[0..2] == "mem") {
      sscanf(line, "mem[%d] = %d", int reg, int val);
      reg |= ormask;
      combinations(floating, reg, val, mem);
    }

    else {
      ormask = 0, floating = 0;
      sscanf(line, "mask = %s", string mask);

      for (int i = 0; i < 36; i++) {
        int bit = 1 << (35 - i);
        if (mask[i] == 'X') floating ^= bit;
        if (mask[i] == '1')   ormask ^= bit;
      }
    }
  }

  write("%d\n", Array.sum(values(mem)));
}