#include <stdio.h>
#include <stdlib.h>

long parse_expr(char *expr, char **end)
{
  long ans = 0;
  char op = '+';

  while (*expr != ')' && *expr != '\n' && *expr != '\0')
  {
    switch (*expr)
    {
      case '+': { op = '+'; expr++; break; }
      case '*': { op = '*'; expr++; break; }
      default:  {
        int val;

        switch (*expr) {
          case '(': { val = parse_expr(expr + 1, &expr); break; }
          default:  { val = strtol(expr, &expr, 10); break; }
        } 
      
        switch (op) {
           case '+': { ans += val; break; } 
           case '*': { ans *= val; break; } 
        }
      }
    }
    while (*expr == ' ') expr++;
  }

  if (end != NULL) *end = expr + 1;
  return ans;
}


int main()
{
  char buffer[1000] = {};
  long ans = 0;

  while (fgets(buffer, sizeof buffer, stdin) != NULL) {
    ans += parse_expr(buffer, NULL);
  }

  printf("%ld\n", ans);
}