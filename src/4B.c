#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int valid_height(int v, char *suffix) {
  if (strcmp(suffix, "cm") == 0) { return 150 <= v && v <= 193; }
  if (strcmp(suffix, "in") == 0) { return  59 <= v && v <=  76; }
  return 0;
}

int valid_hair_color(char *str) {
  if (strlen(str) != 7) return 0;
  if (str[0] != '#') return 0;
  
  for (int i = 1; i < 7; i++) {
    if (!('0' <= str[i] && str[i] <= '9') && 
        !('a' <= str[i] && str[i] <= 'f'))
        return 0;
  }

  return 1;
}

int valid_eye_color(char *str) {
  return strcmp(str, "amb") == 0 ||
         strcmp(str, "blu") == 0 ||
         strcmp(str, "brn") == 0 ||
         strcmp(str, "gry") == 0 ||
         strcmp(str, "grn") == 0 ||
         strcmp(str, "hzl") == 0 ||
         strcmp(str, "oth") == 0;
}

int main() {
  char buffer[1000] = "";
  char passport[1000] = "";
  int count = 0, exit = 0;

  while (!exit) {
    passport[0] = '\0';

    while (1) {
      if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        exit = 1;
        break;
      }
      if (buffer[0] == '\n') {
        break;
      }
      strcat(passport, buffer);
    }

    int length = 0;
    char *tokens[100] = {}, *ptr = &passport[0];

    for (int i = 0; i < sizeof passport; i++) {
      if (passport[i] == '\0') {
        break;
      }

      if ((passport[i] == ' ') || (passport[i] == '\n') || (passport[i] == ':')) {
        tokens[length++] = ptr;
        passport[i] = '\0';
        ptr = &passport[i + 1];
      }
    }

    if (length >= 14) {
      int flag = 1, fail;

      #define tok_equals(str) strcmp(tokens[i], str) == 0
      #define clear_flag { flag = 0; fail = __LINE__; break; }

      for (int i = 0; i < length; i += 2) {
        char *rest, *str = &tokens[i][0];
        int v = strtol(tokens[i + 1], &rest, 10);

             if (tok_equals("cid") && length == 14) clear_flag
        else if (tok_equals("byr") && !(1920 <= v && v <= 2002) && *rest == '\0') clear_flag
        else if (tok_equals("iyr") && !(2010 <= v && v <= 2020) && *rest == '\0') clear_flag
        else if (tok_equals("eyr") && !(2020 <= v && v <= 2030) && *rest == '\0') clear_flag
        else if (tok_equals("hgt") && !valid_height(v, rest)) clear_flag
        else if (tok_equals("hcl") && !valid_hair_color(rest)) clear_flag
        else if (tok_equals("ecl") && !valid_eye_color(rest)) clear_flag
        else if (tok_equals("pid") && !(strlen(tokens[i+1]) == 9 && *rest == '\0')) clear_flag
      }

      if (flag) {
        count++;
      }
    }
  }

  printf("%d\n", count);
}