#include "messages.h"
#include "operators.h"
#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_READ_LENGTH 1024

int main(int argc, char **argv) {
    bool use_trig = false;
    bool print_help = false;

    int opt;

    while ((opt = getopt(argc, argv, "mh")) != -1) {
        switch (opt) {
        case 'h': print_help = 1; break;
        case 'm': use_trig = 1; break;
        }
    }

    if (print_help) {
        fprintf(stdout, USAGE, "./calc");
        return 0;
    } else if (use_trig || argc == 1) {
        while (true) {
            fprintf(stderr, "> ");

            char expr[BUFFER_READ_LENGTH] = { 0 };
            if ((fgets(expr, BUFFER_READ_LENGTH, stdin)) == NULL && feof(stdin)) {
                break;
            }

            for (int i = 0; i < BUFFER_READ_LENGTH; i++) {
                if (expr[i] == '\n') {
                    expr[i] = '\0';
                }
            }

            char *saveptr;
            const char *token = strtok_r(expr, " ", &saveptr);
            bool error = false;

            while (token != NULL && !error) {
                double d;
                size_t token_length = strlen(token);

                if (parse_double(token, &d)) {

                    if (!stack_push(d)) {
                        fprintf(stderr, ERROR_NO_SPACE, d);
                        error = true;
                    }
                } else if (token_length == 1 && binary_operators[(int) *token]) {

                    binary_operator_fn op = binary_operators[(int) *token];
                    if (!apply_binary_operator(op)) {
                        fprintf(stderr, ERROR_BINARY_OPERATOR);
                        error = true;
                    }
                } else if (token_length == 1 && my_unary_operators[(int) *token]) {

                    unary_operator_fn op = my_unary_operators[(int) *token];
                    if (!apply_unary_operator(op)) {
                        fprintf(stderr, ERROR_UNARY_OPERATOR);
                        error = true;
                    }
                } else {
                    if (token_length == 1) {
                        fprintf(stderr, ERROR_BAD_CHAR, *token);
                    } else {
                        fprintf(stderr, ERROR_BAD_STRING, token);
                    }
                    error = true;
                }

                token = strtok_r(NULL, " ", &saveptr);
            }

            if (!error) {
                stack_print();
            }

            stack_clear();
        }

        return 0;
    } else {
        fprintf(stdout, USAGE, "./calc");
        return -1;
    }
}
