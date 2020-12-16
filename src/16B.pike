import Stdio;

class range { int min1, max1, min2, max2; }

int main() {
  string data = stdin->read();
  array chunks = data / "\n\n";

  mapping fields = ([]);
  foreach (chunks[0] / "\n", string line) {
    range r = range();
    sscanf(line, "%s: %d-%d or %d-%d", string key, r->min1, r->max1, r->min2, r->max2);
    fields[key] = r;
  }

  array(array | string) position = allocate(sizeof(values(fields)));
  for (int i = 0; i < sizeof(position); i++) {
    position[i] = ({});
  }

  function to_int = lambda(string s) { sscanf(s, "%d\n", int n); return n; };

  foreach ((chunks[2] / "\n")[1..], string ticket) {
    array nums = map(ticket / ",", to_int); 
    bool invalid = false;

    foreach (nums, string|int num) {
      bool ok = false;

      foreach (values(fields), range r) {
        if ((r->min1 <= num && num <= r->max1) || (r->min2 <= num && num <= r->max2)) {
          ok = true;
          break;
        }
      }

      if (!ok) {
        invalid = true;
        break;
      }
    }

    if (!invalid) {
      int i = 0;
      foreach (nums, int num) {
        position[i] = Array.push(position[i], num);
        i++;
      }
    }
  }

  foreach (indices(position), int key) {
    array(string) possible = ({});
    foreach (indices(fields), string field) {
      range r = fields[field];
      function in_range = lambda(int i) { return (r->min1 <= i && i <= r->max1) || (r->min2 <= i && i <= r->max2); };
      if (Array.all(map(position[key], in_range), `==, true)) {
        possible = Array.push(possible, field);
      }
    }
    position[key] = possible;
  }

  bool cont = true;
  while (cont) {
    cont = false;

    foreach (indices(position), int key) {
      if (stringp(position[key]) == 0) {
        cont = true;

        if (sizeof(position[key]) == 1) {
          position[key] = position[key][0];

          foreach(indices(position), int key2) {
            if (stringp(position[key2]) == 0) {
              array new = ({});

              foreach (position[key2], string opt) {
                if (opt != position[key]) {
                  new = Array.push(new, opt);
                }
              }

              position[key2] = new;
            }
          }
        }
      }
    }
  }

  int ans = 1;
  array my_vals = map((chunks[1] / "\n")[1] / ",", to_int); 

  foreach (indices(position), int key) {
    if ((position[key] / " ")[0] == "departure") {
      ans *= my_vals[key];
    }
  }

  write("%d\n", ans);
}