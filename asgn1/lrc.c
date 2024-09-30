#include "names.h"

#include <stdio.h>
#include <stdlib.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } Position;

const Position die[6] = { DOT, DOT, DOT, LEFT, CENTER, RIGHT };

int main() {
    int num_players = 3;
    printf("Number of players (3 to 10)? ");

    int scanf_result = scanf("%d", &num_players);
    if (scanf_result < 1 || num_players < 3 || num_players > 10) {
        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    unsigned seed = 4823;
    printf("Random-number seed? ");

    scanf_result = scanf("%u", &seed);
    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
        seed = 4823;
    }

    srandom(seed);

    int player_chips[MAX_PLAYERS];

    for (int i = 0; i < num_players; i++) {
        player_chips[i] = 3;
    }

    while (1) {
        for (int i = 0; i < num_players; i++) {
            if (player_chips[i] > 0) {
                int rolls = 3;
                if (player_chips[i] < 3) {
                    rolls = player_chips[i];
                }

                for (int j = 0; j < rolls; j++) {
                    int dice_roll = random() % 6;
                    Position roll = die[dice_roll];

                    if (roll == DOT) {
                        //printf("rolled a dot\n");
                    } else if (roll == LEFT) {
                        //printf("rolled a left\n");
                        int left_player = (i + 1) % num_players;

                        player_chips[i] -= 1;
                        player_chips[left_player] += 1;
                    } else if (roll == RIGHT) {
                        ///printf("rolled a right\n");
                        int right_player = (i - 1 + num_players) % num_players;

                        player_chips[i] -= 1;
                        player_chips[right_player] += 1;
                    } else if (roll == CENTER) {
                        //printf("rolled a center\n");
                        player_chips[i] -= 1;
                    }
                }

                printf("%s: ends her turn with %d\n", player_name[i], player_chips[i]);
            }
            int players_having_chips = 0;
            int player_have_chip = -1;

            for (int p = 0; p < num_players; p++) {
                if (player_chips[p] > 0) {
                    players_having_chips += 1;
                    player_have_chip = p;
                }
            }

            if (players_having_chips == 1) {
                printf("%s won!\n", player_name[player_have_chip]);
                return 0;
            }
        }
    }

    return 0;
}
