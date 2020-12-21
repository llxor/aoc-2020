import Stdio;

int main()
{
    string input = stdin->read();
    array lines = input / "\n";
    lines = lines[0..sizeof(lines)-2]; // remove last trailing \n
    mapping table = ([]);

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
    }

    bool filtered = false;
    array keys = indices(table);

    while (!filtered) {
        filtered = true;

        foreach (keys, string key) {
            if (sizeof(table[key]) > 1) {
                filtered = false;
            } else {
                foreach (keys, string key2) {
                    if (key2 != key) {
                        table[key2] -= table[key];
                    }
                }
            }
        }
    }

    string ans = "";
    sort(keys);

    foreach (keys, string key) {
        ans += "," + table[key][0];
    }

    write("%s\n", ans[1..]); // remove first ,
}
