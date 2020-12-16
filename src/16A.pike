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

  int invalid = 0;

  foreach ((chunks[2] / "\n")[1..], string ticket) {
    array nums = ticket / ","; 

    foreach (nums, string|int num) {
      bool ok = false;
      sscanf(num, "%d", num);

      foreach (values(fields), range r) {
        if ((r->min1 <= num && num <= r->max1) || (r->min2 <= num && num <= r->max2)) {
          ok = true;
          break;
        }
      }

      if (!ok) {
        invalid += num;
        break;
      }
    }
  }

  write("%d\n", invalid);
}