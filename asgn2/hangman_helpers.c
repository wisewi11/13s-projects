#include "hangman_helpers.h"

bool is_lowercase_letter(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    } else {
        return false;
    }
}

bool validate_secret(const char *secret) {
    size_t len = strlen(secret);

    for (size_t i = 0; i < len; i++) {
        if (!is_lowercase_letter(secret[i]) && !string_contains_character(punctuation, secret[i])) {
            fprintf(stdout, "invalid character: '%c'\n", secret[i]);
            fprintf(stdout,
                "the secret phrase must contain only lowercase letters, spaces, hyphens, and "
                "apostrophes\n");
            return false;
        }
    }
    if (len > 256) {
        fprintf(stdout, "the secret phrase is over 256 characters\n");
        return false;
    }

    return true;
}

bool string_contains_character(const char *s, char c) {
    while (*s != '\0') {
        if (*s == c) {
            return true;
        }
        s++;
    }
    return false;
}

char read_letter(void) {
    char l;
    printf("Guess a letter: ");
    scanf("%c", &l);

    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    return l;
}
