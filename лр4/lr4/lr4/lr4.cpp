#include <iostream>
#include <vector>
using namespace std;

double lagrangeInterpolation(const vector<double>& x, const vector<double>& y, double x_star) {
    double result = 0.0;
    int n = x.size();

    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i)
                term *= (x_star - x[j]) / (x[i] - x[j]);
        }
        result += term;
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "");
    vector<double> x = { 0, 1, 2, 3, 4 };
    vector<double> y = { 4, 2, 8, 46, 140 };
    double x_star = 1.7;

    double y_star = lagrangeInterpolation(x, y, x_star);

    cout << "Iнтерполяцiйний полiном Лагранжа:\n";
    cout << "x* = " << x_star << endl;
    cout << "y* = " << y_star << endl;

    return 0;
}
