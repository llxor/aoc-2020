#import <stdio.h>
#import <stdlib.h>
#import <string.h>

typedef enum {JMP, ACC, NOP} op_t;
typedef struct {op_t op; int value;} instr_t;

int main()
{
  char buffer[1000];
  size_t len = 0;
  instr_t instructions[1000];

  while (fgets(buffer, sizeof buffer, stdin) != NULL)
  {
    char op[100];
    instr_t code = {};

    sscanf(buffer, "%s %d", op, &code.value);

         if (strcmp(op, "acc") == 0) code.op = ACC;
    else if (strcmp(op, "jmp") == 0) code.op = JMP;
    else if (strcmp(op, "nop") == 0) code.op = NOP;

    instructions[len++] = code;
  }

  int acc, ptr;
  char visited[len];

  for (size_t i = 0; i < len; i++)
  {
    acc = 0, ptr = 0;
    memset(visited, 0, len);

    instructions[i].op = 2 - instructions[i].op;

    while (!visited[ptr] && ptr < len)
    {
      instr_t instr = instructions[ptr];
      visited[ptr] = 1;

      switch (instr.op)
      {
        case ACC:
          acc += instr.value;
          ptr++;
          break;

        case JMP:
          ptr += instr.value;
          break;

        case NOP:
          ptr++;
          break;
      }
    }

    if (ptr == len) {
      printf("%d\n", acc);
      return 0;
    }

    instructions[i].op = 2 - instructions[i].op;
  }
}
