import Stdio;

int main() {
  int current = 0, turn = 1;
  mapping history = ([]);
  string input = stdin->gets();

  foreach (input/",", string num) {
    sscanf(num, "%d", int val);
    history[val] = turn++;
  }

  while (turn < 30000000) {
    int next;

    if (history[current] == 0) {
      next = 0;
    } else {
      next = turn - history[current];
    }

    history[current] = turn++;
    current = next;
  }

  write("%d\n", current);
}