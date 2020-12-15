import Stdio;

int main()
{
  int current = 0, next, turn = 1;
  string input = stdin->gets();
  mapping history = ([]);

  foreach (input / ",", string num) {
    sscanf(num, "%d", int val);
    history[val] = turn++;
  }

  while (turn < 2020) {
    if (history[current] == 0)
      next = 0;
    else
      next = turn - history[current];

    history[current] = turn++;
    current = next;
  }

  write("%d\n", current);
}