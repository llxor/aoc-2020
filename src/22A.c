#import <stdio.h>

typedef struct {char cards[1000]; int start, len;} stack_t;

stack_t parse_stack()
{
    stack_t res = {};
    char buffer[1000] ={};
    int tmp;

    fgets(buffer, sizeof buffer, stdin); // skip player line

    while (1)
    {
        if (fgets(buffer, sizeof buffer, stdin) == NULL || buffer[0] == '\n') break;
        sscanf(buffer, "%d", &tmp);
        res.cards[res.len++] = tmp;
    }

    return res;
}

int main()
{
    stack_t player1 = parse_stack(),
            player2 = parse_stack();

    while (player1.len && player2.len)
    {
        int card1 = player1.cards[player1.start++],
            card2 = player2.cards[player2.start++];

        player1.len--;
        player2.len--;

        if (card1 > card2) {
            player1.cards[player1.start + player1.len++] = card1;
            player1.cards[player1.start + player1.len++] = card2;
        } else {
            player2.cards[player2.start + player2.len++] = card2;
            player2.cards[player2.start + player2.len++] = card1;
        }
    }

    stack_t *winner = (player2.len == 0) ? &player1 : &player2;
    int ans = 0;

    for (int i = 0; i < winner->len; i++)
        ans += (winner->len - i) * winner->cards[winner->start + i];

    printf("%d\n", ans);
}
