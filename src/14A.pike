import Stdio;

int main() {
  string line;
  int ormask, andmask;
  mapping mem = ([]);

  while ((line = stdin->gets())) {
    if (line[0..2] == "mem") {
      sscanf(line, "mem[%d] = %d", int reg, int val);
      val &= andmask;
      val |= ormask;
      mem[reg] = val;
    }

    else {
      ormask = 0, andmask = (1 << 35) - 1;
      sscanf(line, "mask = %s", string mask);

      for (int i = 0; i < 36; i++) {
        int bit = 1 << (35 - i);
        if (mask[i] == '0') andmask ^= bit;
        if (mask[i] == '1')  ormask ^= bit;
      }
    }
  }

  write("%d\n", Array.sum(values(mem)));
}