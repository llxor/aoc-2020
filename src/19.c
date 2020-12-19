#import <stdio.h>
#import <stdlib.h>

typedef struct {unsigned char value, ptrs[2][3], options, len;} rule_t;
typedef struct {const char *end[8]; char len;} array_t;

rule_t parse_rule(char *src)
{
  rule_t rule = {};
  char opt_len = 0, len = 0;

  if (*src == '"')
  {
    rule.value = *(src + 1);
    return rule;
  }

  while (*src != '\0' && *src != '\n')
  {
    switch (*src)
    {
      case '|': { len = 0; opt_len++; src++; break; }
      default:  { rule.ptrs[opt_len][len++] = strtol(src, &src, 10); break; }
    }

    while (*src == ' ') src++;
  }

  rule.options = opt_len + 1, rule.len = len;
  return rule;
}


array_t check(const rule_t *rules, const rule_t *rule, const char *src)
{
  array_t res = {.len = 0, .end = {}};

  // base case: rule is a matching character
  if (rule->value)
  {
    if (*src == rule->value) res.end[res.len++] = src + 1;
    return res;
  }

  for (int i = 0; i < rule->options; i++)
  {
    const char *copies[8] = {src};
    int len = 1;

    for (int j = 0; j < rule->len; j++)
    {
      // optimise: skip on empty array
      if (len == 0) goto end;

      if (rule->ptrs[i][j] != 0xff)
      {
        // filter not pre-finished
        int nlen = 0;
        for (int k = 0; k < len; k++)
          if (*copies[k] != '\n')
            copies[nlen++] = copies[k]; 

        // optimise: check we still have some copies
        if (nlen == 0) goto end;

        const char *new_copies[8] = {};
        len = 0;

        // find if copy can be continued
        for (int k = 0; k < nlen; k++)
        {
          array_t sub = check(rules, &rules[rule->ptrs[i][j]], copies[k]);
          for (int l = 0; l < sub.len; l++)
            new_copies[len++] = sub.end[l];
        }

        for (int k = 0; k < len; k++)
          copies[k] = new_copies[k];
      }
    }

    for (int k = 0; k < len; k++) {
      res.end[res.len++] = copies[k];
    }

    end: continue;
  }

  return res;
}


int main()
{
  char buffer[1000] = {};
  rule_t rules[1 << 8];
  int parsing = 1, ans = 0;

  while (fgets(buffer, sizeof buffer, stdin) != NULL)
  {
    if (buffer[0] == '\n') {
      parsing = 0;
      continue;
    }

    if (parsing) {
      int ptr, n;
      sscanf(buffer, "%d: %n", &ptr, &n);
      rules[ptr] = parse_rule(buffer + n);
    }

    else {
      array_t res = check(rules, &rules[0], buffer);
      ans += res.len > 0 && *res.end[0] == '\n';
    }
  }

  printf("%d\n", ans);
}