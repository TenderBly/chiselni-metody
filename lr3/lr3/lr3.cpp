#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// System of equations:
// F1: x^2 - 3y^2 + 2z^2 = -0.7
// F2: x - y^2 + 2z = 1.5
// F3: 2x^2 - y - z^2 = -1.5

// Function to calculate system values
void calculateF(double x, double y, double z, double F[3]) {
    F[0] = x * x - 3 * y * y + 2 * z * z + 0.7;
    F[1] = x - y * y + 2 * z - 1.5;
    F[2] = 2 * x * x - y - z * z + 1.5;
}

// Objective function (sum of squared residuals)
double objectiveFunction(double x, double y, double z) {
    double F[3];
    calculateF(x, y, z, F);
    return 0.5 * (F[0] * F[0] + F[1] * F[1] + F[2] * F[2]);
}

// Calculate gradient of objective function
void calculateGradient(double x, double y, double z, double grad[3]) {
    double F[3];
    calculateF(x, y, z, F);

    // Partial derivatives of F1, F2, F3 with respect to x, y, z
    double dF1_dx = 2 * x;
    double dF1_dy = -6 * y;
    double dF1_dz = 4 * z;

    double dF2_dx = 1;
    double dF2_dy = -2 * y;
    double dF2_dz = 2;

    double dF3_dx = 4 * x;
    double dF3_dy = -1;
    double dF3_dz = -2 * z;

    // Gradient of objective function
    grad[0] = F[0] * dF1_dx + F[1] * dF2_dx + F[2] * dF3_dx;
    grad[1] = F[0] * dF1_dy + F[1] * dF2_dy + F[2] * dF3_dy;
    grad[2] = F[0] * dF1_dz + F[1] * dF2_dz + F[2] * dF3_dz;
}

// Vector norm
double vectorNorm(double v[3]) {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

// Gradient descent method
void gradientDescent(double& x, double& y, double& z, double epsilon) {
    const int maxIterations = 10000;
    double alpha = 0.01; // Initial step size
    double grad[3];
    int iteration = 0;

    cout << fixed << setprecision(6);
    cout << "\nIteration process:\n";
    cout << "Iteration\t x\t\t y\t\t z\t\t ||grad||\t f(x,y,z)\n";
    cout << string(90, '-') << endl;

    while (iteration < maxIterations) {
        calculateGradient(x, y, z, grad);
        double gradNorm = vectorNorm(grad);
        double fValue = objectiveFunction(x, y, z);

        if (iteration % 100 == 0) {
            cout << iteration << "\t\t"
                << x << "\t" << y << "\t" << z << "\t"
                << gradNorm << "\t" << fValue << endl;
        }

        // Check stopping criterion
        if (gradNorm < epsilon) {
            cout << "\nConvergence achieved at iteration " << iteration << endl;
            break;
        }

        // Update variables with adaptive step size
        double x_new = x - alpha * grad[0];
        double y_new = y - alpha * grad[1];
        double z_new = z - alpha * grad[2];

        // Check for improvement
        double f_new = objectiveFunction(x_new, y_new, z_new);
        if (f_new < fValue) {
            x = x_new;
            y = y_new;
            z = z_new;
            alpha *= 1.05; // Increase step on success
        }
        else {
            alpha *= 0.5; // Decrease step on failure
        }

        // Step size bounds
        if (alpha > 0.1) alpha = 0.1;
        if (alpha < 1e-10) {
            cout << "\nStep size became too small. Stopping.\n";
            break;
        }

        iteration++;
    }

    if (iteration >= maxIterations) {
        cout << "\nReached maximum number of iterations\n";
    }
}

int main() {
    // Initial approximation
    double x = 1.0, y = 1.0, z = 1.0;
    double epsilon = 0.0001;

    cout << "Solving system of nonlinear equations using gradient descent method\n";
    cout << string(90, '=') << endl;
    cout << "System of equations:\n";
    cout << "x^2 - 3y^2 + 2z^2 = -0.7\n";
    cout << "x - y^2 + 2z = 1.5\n";
    cout << "2x^2 - y - z^2 = -1.5\n";
    cout << string(90, '=') << endl;

    cout << "\nInitial approximation: x = " << x << ", y = " << y << ", z = " << z << endl;
    cout << "Tolerance: epsilon = " << epsilon << endl;

    gradientDescent(x, y, z, epsilon);

    // Output results
    cout << "\n" << string(90, '=') << endl;
    cout << "RESULT:\n";
    cout << "x = " << setprecision(8) << x << endl;
    cout << "y = " << setprecision(8) << y << endl;
    cout << "z = " << setprecision(8) << z << endl;

    return 0;
}