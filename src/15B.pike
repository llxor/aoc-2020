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

  while (turn < 30000000) {
    next = (turn - history[current]) % turn;
    history[current] = turn++;
    current = next;
  }

  write("%d\n", current);
}