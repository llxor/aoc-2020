#import <stdio.h>

typedef struct {char cards[10000]; int start, len;} stack_t;

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

int find_winner(stack_t player1, stack_t player2, int p1, int p2, stack_t *root)
{
    if (p1 != -1) player1.len = p1;
    if (p2 != -1) player2.len = p2;

    unsigned char loop[1 << 12] = {};

    while (player1.len && player2.len)
    {
        int card1 = player1.cards[player1.start++],
            card2 = player2.cards[player2.start++],
              key = (card1 << 6) | card2, p1;

        // if same two cards are drawn 3 times we are in an infinite loop
        if (loop[key] == 3) return 1;
        loop[key]++;

        player1.len--;
        player2.len--;

        if (player1.len >= card1 && player2.len >= card2) {
            p1 = find_winner(player1, player2, card1, card2, NULL);
        }

        else {
            p1 = card1 > card2;
        }

        stack_t *winner = p1 ? &player1 : &player2;
        winner->cards[winner->start + winner->len++] = p1 ? card1 : card2;
        winner->cards[winner->start + winner->len++] = p1 ? card2 : card1;
    }

    if (root != NULL) *root = (player2.len == 0) ? player1 : player2;
    return (player2.len == 0);
}


int main()
{
    stack_t player1 = parse_stack(),
            player2 = parse_stack(),
            winner = {};

    int ans = 0;
    find_winner(player1, player2, -1, -1, &winner);

    for (int i = 0; i < winner.len; i++)
        ans += (winner.len - i) * winner.cards[winner.start + i];

    printf("%d\n", ans);
}
