#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.141592653589793;

// f(x) = x * cos(x^3)
double f(double x) {
    return x * cos(pow(x, 3));
}

// Метод Сімпсона
double simpson(double a, double b, int n) {
    if (n % 2 != 0)
        throw invalid_argument("Кількість підінтервалів n має бути парною!");

    double h = (b - a) / n;
    double S = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0)
            S += 2 * f(x);
        else
            S += 4 * f(x);
    }

    return S * h / 3.0;
}

int main() {
    double a = 0.0;
    double b = PI / 4.0;
    int n = 10000;  // велике n для точності

    double I = simpson(a, b, n);

    cout << "Result: " << I << endl;

    return 0;
}
