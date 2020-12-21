import Stdio;

int main()
{
    string input = stdin->read();
    array lines = input / "\n";
    lines = lines[0..sizeof(lines)-2]; // remove last trailing \n

    mapping table = ([]);
    mapping count = ([]);
    array all = ({});

    foreach (lines, string line) {
        sscanf(line, "%s (contains %s)", string ingr, string alle);
        array ingredients = ingr / " ",
              allergens = alle / ", ";

        foreach (allergens, string alle) {
            if (table[alle] == 0) {
                table[alle] = ingredients;
            } else {
                table[alle] &= ingredients;
            }
        }

        all |= ingredients;

        foreach (ingredients, string ingr) {
            count[ingr]++;
        }
    }

    foreach (indices(table), string allergen) {
        all -= table[allergen];
    }

    int ans = 0;

    foreach (all, string ingr) {
        ans += count[ingr];
    }

    write("%d\n", ans);
}
