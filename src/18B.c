#include <stdio.h>
#include <stdlib.h>

long parse_expr(char *expr, char **end)
{
  long ans = 0, len = 0, subs[100] = {};

  while (*expr != ')' && *expr != '\n' && *expr != '\0')
  {
    switch (*expr)
    {
      case '+': { expr++; break; }
      case '*': { expr++; subs[len++] = ans; ans = 0; break; }
      default:  {
        int val;

        switch (*expr) {
          case '(': { val = parse_expr(expr + 1, &expr); break; }
          default:  { val = strtol(expr, &expr, 10); break; }
        } 
      
        ans += val;
      }
    }
    while (*expr == ' ') expr++;
  }

  if (end != NULL) *end = expr + 1;
  for (int i = 0; i < len; i++) ans *= subs[i];
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