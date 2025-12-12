#include <iostream>
#include <Windows.h>
#include <cmath>
#include <iomanip>

using namespace std;

// Диференціальне рівняння:
// y' = y^2 * e^x - 2y
double f(double x, double y) {
    return y * y * exp(x) - 2 * y;
}

// Один крок методу Рунге–Кутти 4 порядку
double rungeKuttaStep(double x, double y, double h) {
    double k1 = f(x, y);
    double k2 = f(x + h / 2, y + h * k1 / 2);
    double k3 = f(x + h / 2, y + h * k2 / 2);
    double k4 = f(x + h, y + h * k3);
    return y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    double x0 = 0.0;
    double y0 = 1.0;       // y(0) = 1
    double X = 1.0;        // шукаємо y(1)
    double eps = 0.00001;  // точність

    double h = 0.1;        // початковий крок
    double y_big, y_small;
    double error = 0.0;

    while (true) {
        double x = x0;
        double y = y0;

        // Розв'язок з кроком h (грубий)
        while (x < X) {
            double step = min(h, X - x);
            y = rungeKuttaStep(x, y, step);
            x += step;
        }
        y_big = y;

        // Розв'язок з кроком h/2 (точніший)
        x = x0;
        y = y0;
        while (x < X) {
            double step = min(h / 2, X - x);
            y = rungeKuttaStep(x, y, step);
            x += step;
        }
        y_small = y;

        // Оцінка похибки
        error = fabs(y_small - y_big);

        if (error < eps)
            break;
        else
            h /= 2.0; // зменшуємо крок
    }

    cout << fixed << setprecision(10);
    cout << "Розв'язок диференціального рівняння в точці x = 1:\n";
    cout << "y(1) = " << y_small << endl;
    cout << "Використаний крок h = " << h << endl;
    cout << "Похибка обчислень = " << error << endl;

    return 0;
}
