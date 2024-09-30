#include "mathlib.h"

#include <math.h>

double Abs(double x) {
    if (x > 0) {
        return x;
    } else {
        return -x;
    }
}

double Sqrt(double x) {
    if (x < 0) {
        return nan("nan");
    }

    double t1 = 0.0;
    double t2 = 1.0;

    while (Abs(t1 - t2) > EPSILON) {
        t1 = t2;
        t2 = 0.5 * (t1 + (x / t1));
    }

    return t2;
}

double Sin(double x) {
    x = fmod(x, 2 * M_PI);
    if (x < 0) {
        x += 2 * M_PI;
    }

    double num1 = 1;
    double num2 = x;

    double answer = num2;

    while (Abs(num2) > EPSILON) {
        num2 = -num2 * x * x / ((2 * num1) * (2 * num1 + 1));
        answer += num2;
        num1++;
    }

    return answer;
}

double Cos(double x) {
    x = fmod(x, 2 * M_PI);
    if (x < 0) {
        x += 2 * M_PI;
    }

    double num1 = 1;
    double num2 = 1;

    double answer = num2;

    while (Abs(num2) > EPSILON) {
        num2 = -num2 * x * x / ((2 * num1) * (2 * num1 - 1));
        answer += num2;
        num1++;
    }

    return answer;
}

double Tan(double x) {
    return Sin(x) / Cos(x);
}
