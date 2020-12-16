import Stdio;

class range {
  int min1, max1, min2, max2;
  bool contains(int x) {
    return (min1 <= x && x <= max1) || (min2 <= x && x <= max2);
  }
}

int main()
{
  string data = stdin->read();
  array chunks = data / "\n\n";

  mapping fields = ([]);
  foreach (chunks[0] / "\n", string line) {
    range r = range();
    sscanf(line, "%s: %d-%d or %d-%d", string key, r->min1, r->max1, r->min2, r->max2);
    fields[key] = r;
  }

  array position = allocate(sizeof(values(fields)), ({}));
  function to_int = lambda(string s) { sscanf(s, "%d\n", int n); return n; };

  foreach ((chunks[2] / "\n")[1..], string ticket) {
    array nums = map(ticket / ",", to_int); 
    bool invalid = false;

    foreach (nums, mixed num) {
      function check = lambda(range r) {return r.contains(num);};

      if (Array.all(map(values(fields), check), `==, false)) {
        invalid = true;
        break;
      }
    }

    if (!invalid) {
      foreach (indices(nums), int i) {
        position[i] = Array.push(position[i], nums[i]);
      }
    }
  }

  foreach (indices(position), int key) {
    array(string) possible = ({});
    foreach (indices(fields), string field) {
      range r = fields[field];
      function check = lambda(int i) {return r.contains(i);};

      if (Array.all(map(position[key], check), `==, true)) {
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