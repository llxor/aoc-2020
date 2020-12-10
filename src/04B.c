#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lib.h"

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

    // read passport
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

    // split into tokens
    char *tokens[100] = {};
    int length = split_by_chars(tokens, 100, passport, " :\n") - 1;

    // check tokens
    if (length >= 14) {
      int flag = 1;

      #define tok_equals(str) strcmp(tokens[i], str) == 0
      #define in_range(a, b) (a <= v && v <= b)
      #define clear_flag { flag = 0; break; }

      for (int i = 0; i < length; i += 2) {
        char *rest, *str = &tokens[i][0];
        int v = strtol(tokens[i + 1], &rest, 10);

             if (tok_equals("cid") && length == 14) clear_flag
        else if (tok_equals("byr") && !in_range(1920, 2002)) clear_flag
        else if (tok_equals("iyr") && !in_range(2010, 2020)) clear_flag
        else if (tok_equals("eyr") && !in_range(2020, 2030)) clear_flag
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