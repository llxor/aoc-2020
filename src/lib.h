#import "stddef.h"

// checks strings a and b for equality
int streql(const char *a, const char *b)
{
  while (1) {
    if (*a != *b) {
      return 0;
    }

    if (*a == '\0') {
      return 1;
    }

    a++;
    b++;
  }
}

//checks first n chars of a and b for equality
int strneql(const char *a, const char *b, size_t n)
{
  for (size_t i = 0; i < n; i++) {
    if (*a != *b) {
      return 0;
    }

    a++;
    b++;
  }

  return 1;
}

// own implementation of strlen
size_t __hidden_strlen(const char *src) {
  const char *end = src;
  while (*end) end++;
  return end - src;
}

// splits src by delimiter into an array with max n elems
size_t split_by_str(char **array, size_t n_elems, char *src, const char *delim)
{
  size_t delim_len = __hidden_strlen(delim);
  size_t array_len = 0;
  char *ptr = src;

  while (1) {
    if (strneql(src, delim, delim_len) || *src == '\0') {
      array[array_len++] = ptr;

      if (*src == '\0') {
        break;
      }

      else {
        *src = '\0';
        src += delim_len;
        ptr = src;
      }
    }

    else {
      src++;
    }

    if (array_len == n_elems) {
      break;
    }
  }

  return array_len;
}

// splits src by any char in delimiter into an array on max n elems
size_t split_by_chars(char **array, size_t n_elems, char *src, const char *delim)
{
  size_t delim_len = __hidden_strlen(delim) + 1;
  size_t array_len = 0;
  char *ptr = src;
  char exit = 0;
  
  while (!exit) {
    for (size_t i = 0; i < delim_len; i++) {
      if (*src == delim[i]) {
        array[array_len++] = ptr;

        if (*src == '\0') {
          exit = 1;
          break;
        }

        *src = '\0';
        ptr = src + 1;
        break;
      }
    }

    src++;

    if (array_len == n_elems) {
      break;
    }
  }

  return array_len;
}

size_t hash(const char *src)
{
  size_t prime = 0x100000001B3;
  size_t hash = 0xcbf29ce484222325;

  while (*src != '\0')
  {
    hash ^= *src;
    hash *= prime;
    src++;
  }

  return hash;
}
