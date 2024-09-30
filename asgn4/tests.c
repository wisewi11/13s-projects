#include "operators.h"
#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

int main() {
    double num1 = 1.0;
    double num2 = 2.0;

    stack_push(num2);
    stack_push(num1);
    printf("Stack pushed successfully\n");

    apply_binary_operator(operator_sub);

    double result;
    stack_peek(&result);
    printf("Stack peek test successful\n");

    assert(result == num1);
    printf("Subtraction successful\n");

    stack_pop(&result);
    assert(!stack_peek(&result));
    printf("Stack pop test successful\n");

    assert(Sqrt(9.0) == 3.0);
    printf("Square root test successful\n");

    assert(Abs(2.0) == 2.0);
    assert(Abs(-7.0) == 7.0);
    printf("Abs test successful\n");

    printf("Sin(0) is 0: %0.10f\n", Sin(0));
    printf("Sin(pi / 3) is 0.86602540378: %0.10f\n", Sin(M_PI / 3));

    printf("Cos(0) is 1: %0.10f\n", Cos(0));
    printf("Cos(pi / 3) is 0.5: %0.10f\n", Cos(M_PI / 3));

    printf("Tan(0) is 0: %0.10f\n", Tan(0));
    printf("Tan(pi / 3) is 1.73205080757: %0.10f\n", Tan(M_PI / 3));

    return 0;
}
