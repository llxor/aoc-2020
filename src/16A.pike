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

  int invalid = 0;

  foreach ((chunks[2] / "\n")[1..], string ticket) {
    array nums = ticket / ","; 

    foreach (nums, mixed num) {
      sscanf(num, "%d", num);
      function check = lambda(range r) {return r.contains(num);};

      if (Array.all(map(values(fields), check), `==, false)) {
        invalid += num;
        break;
      }
    }
  }

  write("%d\n", invalid);
}