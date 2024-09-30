#include "hangman_helpers.h"

int main(int argc, char *argv[]) {
    if (argc == 2) {
        char *secret_word = argv[1];
        if (!validate_secret(secret_word)) {
            return 0;
        }

        size_t slen = strlen(secret_word);

        char guesses[MAX_LENGTH] = { 0 };
        char wrong_guess[MAX_LENGTH] = { 0 };

        int num_wrong = 0;

        while (1) {
            // clear screen
            printf(CLEAR_SCREEN);

            // print gallow
            printf("%s\n", arts[num_wrong]);

            // print guess  progress
            printf("\n");
            printf("    Phrase: ");

            int has_missing_letter = 0;

            for (int i = 0; (size_t) i < slen; i++) {
                char letter = secret_word[i];
                if (!is_lowercase_letter(letter)) {
                    printf("%c", letter);
                } else {
                    if (guesses[(int) letter] > 0) {
                        printf("%c", letter);
                    } else {
                        printf("_");
                        has_missing_letter = 1;
                    }
                }
            }

            printf("\n");

            // print eliminated guesses
            printf("Eliminated: ");

            for (int i = 0; i < MAX_LENGTH; i++) {
                char letter = wrong_guess[i];
                if (letter > 0) {
                    printf("%c", letter);
                }
            }

            printf("\n\n");

            // check if user won or lost
            if (num_wrong == LOSING_MISTAKE) {
                printf("You lose! The secret phrase was: %s\n", secret_word);
                return 0;
            } else if (!has_missing_letter) {
                printf("You win! The secret phrase was: %s\n", secret_word);
                return 0;
            }

            // user guess letter
            while (1) {
                char guess = read_letter();
                int id = (int) guess;

                if (!is_lowercase_letter(guess)) {
                    continue;
                }

                if (string_contains_character(secret_word, guess)) {
                    if (guesses[id] == 0) {
                        guesses[id] = guess;
                        break;
                    }
                } else if (wrong_guess[id] == 0) {
                    wrong_guess[id] = guess;
                    num_wrong += 1;
                    break;
                }
            }
        }

    } else {
        printf("wrong number of arguments \n");
        printf("usage: ./hangman <secret word or phrase> \n");
        printf("if the secret is multiple words, you must quote it \n");
        return 0;
    }

    return 0;
}
