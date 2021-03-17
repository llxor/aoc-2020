#include <stdio.h>
#include <stdlib.h>

struct range {
  int a1, a2, b1, b2;
};

int in_range(struct range r, int x) {
  return (r.a1 <= x && x <= r.a2) || (r.b1 <= x && x <= r.b2);
}

const int rangesN = 20, ticketsN = 238;

void parse_ints(char *buffer, int array[rangesN]) {
  for (int i = 0; i < rangesN; i++) {
    array[i] = strtol(buffer, &buffer, 10);
    buffer++;
  }
}

void parse_input(struct range ranges[rangesN], int our[rangesN], int tickets[ticketsN][rangesN]) {
  char buffer[1000];
  char name[1000];

  for (int i = 0; i < rangesN; i++) {
    fgets(buffer, sizeof buffer, stdin);

    struct range *r = ranges + i;
    sscanf(buffer, "%[^:]: %d-%d or %d-%d", name, &r->a1, &r->a2, &r->b1, &r->b2);
  }

  // skip lines
  fgets(buffer, sizeof buffer, stdin);
  fgets(buffer, sizeof buffer, stdin);

  fgets(buffer, sizeof buffer, stdin);
  parse_ints(buffer, our);

  // skip lines
  fgets(buffer, sizeof buffer, stdin);
  fgets(buffer, sizeof buffer, stdin);

  for (int i = 0; i < ticketsN; i++) {
    fgets(buffer, sizeof buffer, stdin);
    parse_ints(buffer, tickets[i]);
  }
}

int main() {
  struct range fields[rangesN] = {};
  int our[rangesN] = {};
  int tickets[ticketsN][rangesN] = {};

  int pos[rangesN] = {[0 ... rangesN - 1] = (1 << 20) - 1};
  int valid[ticketsN] = {};
  int validN = 0;

  parse_input(fields, our, tickets);

  // remove invalid tickets
  for (int i = 0; i < ticketsN; i++) {
    int invalid = 0;

    for (int j = 0; j < rangesN; j++) {
      for (int k = 0; k < rangesN; k++) {
        if (in_range(fields[k], tickets[i][j])) {
          goto end;
        }
      }

      invalid = 1;
      break;

    end:
      continue;
    }

    if (!invalid) {
      valid[validN++] = i;
    }
  }

  // match fields with pos
solve:
  for (int i = 0; i < rangesN; i++) {
    if (pos[i] & (pos[i] - 1)) {
      for (int j = 0; j < validN; j++) {
        int *ticket = tickets[valid[j]];
        int mask = 0;

        for (int k = 0; k < rangesN; k++) {
          int solved = 0;

          for (int l = 0; l < rangesN; l++) {
            if (pos[l] == 1 << k) {
              solved = 1;
              break;
            } 
          }

          if (!solved && in_range(fields[i], ticket[k])) {
            mask |= 1 << k;
          }
        }

        pos[i] &= mask;
        if ((pos[i] & (pos[i] - 1)) == 0) {
          goto solve;
        }
      }
    }
  }

  long ans = 1;

  for (int i = 0; i < 6; i++) {
    ans *= our[__builtin_ctz(pos[i])];
  }

  printf("%ld\n", ans);
}
