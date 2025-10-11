#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const double EPSILON = 0.0001;
const int MAX_ITERATIONS = 1000;

void printVector(const vector<double>& v, const string& name) {
    cout << name << " = [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << fixed << setprecision(6) << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool seidelMethod(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int n) {
    vector<double> x_old(n);
    int iteration = 0;
    double max_diff;

    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    cout << "\n=== Iteration Process ===" << endl;

    do {
        x_old = x;
        max_diff = 0.0;

        for (int i = 0; i < n; i++) {
            double sum = b[i];

            for (int j = 0; j < i; j++) {
                sum -= A[i][j] * x[j];
            }

            for (int j = i + 1; j < n; j++) {
                sum -= A[i][j] * x_old[j];
            }

            x[i] = sum / A[i][i];

            double diff = fabs(x[i] - x_old[i]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }

        iteration++;

        cout << "Iteration " << iteration << ": ";
        printVector(x, "x");
        cout << "Max error: " << scientific << max_diff << fixed << endl;

        if (iteration >= MAX_ITERATIONS) {
            cout << "\nMax iterations reached!" << endl;
            return false;
        }

    } while (max_diff > EPSILON);

    return true;
}

bool checkDiagonalDominance(vector<vector<double>>& A, int n) {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                sum += fabs(A[i][j]);
            }
        }
        if (fabs(A[i][i]) < sum) {
            return false;
        }
    }
    return true;
}

int main() {
    int n = 4;

    vector<vector<double>> A = {
        {0.83,  0.27, -0.13, -0.11},
        {0.13, -1.12,  0.09, -0.06},
        {0.11,  0.05, -1.02,  0.12},
        {0.13,  0.18,  0.24, -0.57}
    };

    vector<double> b = { 1.42, -0.48, 2.34, -0.72 };

    vector<double> x(n);

    cout << "=== Seidel Method for SLAE ===" << endl;
    cout << "\nMatrix A:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << fixed << setprecision(2) << A[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nVector b:" << endl;
    printVector(b, "b");

    cout << "\nAccuracy: " << EPSILON << endl;

    if (!checkDiagonalDominance(A, n)) {
        cout << "\nWARNING: Matrix has no diagonal dominance!" << endl;
        cout << "Convergence is not guaranteed, but let's try..." << endl;
    }

    if (seidelMethod(A, b, x, n)) {
        cout << "\n=== RESULT ===" << endl;
        printVector(x, "Solution");
    }
    else {
        cout << "\nMethod did not converge!" << endl;
    }

    return 0;
}