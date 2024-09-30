#include "stack.h"

#include <stdio.h>

double stack[STACK_CAPACITY];
int stack_size;

bool stack_push(double item) {
    if (stack_size == STACK_CAPACITY) {
        return false;
    }

    stack[stack_size] = item;
    stack_size += 1;

    return true;
}

bool stack_peek(double *item) {
    if (stack_size == 0) {
        return false;
    }

    *item = stack[stack_size - 1];
    return true;
}

bool stack_pop(double *item) {
    if (stack_size == 0) {
        return false;
    }

    stack_size -= 1;
    *item = stack[stack_size];

    return true;
}

void stack_clear(void) {
    stack_size = 0;
}

void stack_print(void) {
    if (stack_size == 0) {
        return;
    }

    printf("%0.10f", stack[0]);

    for (int i = 1; i < stack_size; i++) {
        printf(" %0.10f", stack[i]);
    }

    printf("\n");
}
