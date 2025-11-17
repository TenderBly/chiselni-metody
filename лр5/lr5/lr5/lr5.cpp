#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int n = 9;
    double x[n] = { 0.3,0.7,1.5,1.9,2.2,2.7,3.4,3.9,4.4 };
    double y[n] = { 0.13,0.45,0.86,1.01,1.34,1.98,2.56,3.41,5 };

    // СЕРЕДНІ ВЕЛИЧИНИ
    double sumX = 0, sumY = 0, prodX = 1, prodY = 1, sumInvX = 0, sumInvY = 0;

    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        prodX *= x[i];
        prodY *= y[i];
        sumInvX += 1.0 / x[i];
        sumInvY += 1.0 / y[i];
    }

    double meanX_arith = sumX / n;
    double meanY_arith = sumY / n;

    double meanX_geom = pow(prodX, 1.0 / n);
    double meanY_geom = pow(prodY, 1.0 / n);

    double meanX_harm = n / sumInvX;
    double meanY_harm = n / sumInvY;

    // ПОКАЗНИКОВА РЕГРЕСІЯ
    // ln(y) = b0 + b1 ln(x)

    double sumLX = 0, sumLY = 0, sumLXLX = 0, sumLXLY = 0, sumLY2 = 0;

    double LX[20], LY[20];

    for (int i = 0; i < n; i++) {
        LX[i] = log(x[i]);
        LY[i] = log(y[i]);

        sumLX += LX[i];
        sumLY += LY[i];
        sumLXLX += LX[i] * LX[i];
        sumLXLY += LX[i] * LY[i];
        sumLY2 += LY[i] * LY[i];
    }

    double b1 = (n * sumLXLY - sumLX * sumLY) / (n * sumLXLX - sumLX * sumLX);
    double b0 = (sumLY - b1 * sumLX) / n;

    double a0 = exp(b0);
    double a1 = b1;

    // R² та F

    double R2 = (b1 * (n * sumLXLY - sumLX * sumLY)) / (n * sumLY2 - sumLY * sumLY);

    int m = 1;
    double F = (R2 / (1 - R2)) * ((n - m - 1.0) / m);

    // ВИВЕДЕННЯ РЕЗУЛЬТАТІВ

    cout << "Рівняння апроксимації: y = " << a0 << " * x^" << a1 << endl << endl;

    cout << "Середнє арифметичне для X = " << meanX_arith << endl;
    cout << "Середнє геометричне для X = " << meanX_geom << endl;
    cout << "Середнє гармонійне для X = " << meanX_harm << endl;

    cout << "Середнє арифметичне для Y = " << meanY_arith << endl;
    cout << "Середнє геометричне для Y = " << meanY_geom << endl;
    cout << "Середнє гармонійне для Y = " << meanY_harm << endl << endl;

    cout << "Коефіцієнт детермінації (R^2) = " << R2 << endl;
    cout << "F-статистика = " << F << endl;

    cout << "a1=" << a1 << endl;
    cout << "a0=" << a0 << endl;

    return 0;
}
