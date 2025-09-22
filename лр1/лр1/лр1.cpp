#include <iostream>
#include <Windows.h>
#include <cmath>
#include <stdexcept>

using namespace std;

#define MAXIMUM_ITERATIONS 1000

double equation_function(double x) {
    return exp(-2.0 * x) - 2.0 * x + 1.0;
}

double equation_derivative(double x) {
    return -2.0 * exp(-2.0 * x) - 2.0;
}

struct SolutionData {
    double solution_value;
    int iteration_count;
};

double compute_iteration_coefficient(double start_point, double end_point) {
    double derivative_at_start = equation_derivative(start_point);
    double derivative_at_end = equation_derivative(end_point);
    return 2.0 / (derivative_at_start + derivative_at_end);
}

SolutionData iterative_method(double initial_guess, double boundary, double precision) {
    int step_counter = 0;
    double current_approximation = initial_guess;
    double previous_approximation;

    double iteration_coeff = compute_iteration_coefficient(initial_guess, boundary);

    while (true) {
        previous_approximation = current_approximation;
        current_approximation = previous_approximation - iteration_coeff * equation_function(previous_approximation);
        step_counter++;

        if (step_counter > MAXIMUM_ITERATIONS) {
            throw runtime_error("Перевищено максимальну кількість ітерацій!");
        }

        if (fabs(current_approximation - previous_approximation) <= precision) {
            break;
        }
    }

    SolutionData result;
    result.solution_value = current_approximation;
    result.iteration_count = step_counter;
    return result;
}

SolutionData newton_raphson_method(double initial_guess, double precision) {
    int step_counter = 0;
    double current_approximation = initial_guess;
    double previous_approximation;

    while (true) {
        previous_approximation = current_approximation;
        double function_value = equation_function(previous_approximation);
        double derivative_value = equation_derivative(previous_approximation);

        current_approximation = previous_approximation - function_value / derivative_value;
        step_counter++;

        if (step_counter > MAXIMUM_ITERATIONS) {
            throw runtime_error("Перевищено максимальну кількість ітерацій!");
        }

        if (fabs(current_approximation - previous_approximation) <= precision) {
            break;
        }
    }

    SolutionData result;
    result.solution_value = current_approximation;
    result.iteration_count = step_counter;
    return result;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== РОЗВ'ЯЗАННЯ НЕЛІНІЙНОГО РІВНЯННЯ ===" << endl;
    cout << "Рівняння: f(x) = e^(-2x) - 2x + 1 = 0" << endl;
    cout << endl;
    cout << "Доступні методи розв'язання:" << endl;
    cout << "[1] Метод простих ітерацій" << endl;
    cout << "[2] Метод Ньютона" << endl;
    cout << endl;

    int method_selection;
    cout << "Оберіть метод (1 або 2): ";
    cin >> method_selection;

    double starting_point, accuracy;
    cout << "Початкове наближення (x0): ";
    cin >> starting_point;
    cout << "Точність обчислень (ε): ";
    cin >> accuracy;

    try {
        SolutionData computation_result;

        switch (method_selection) {
        case 1: {
            double upper_bound = 1.0;
            computation_result = iterative_method(starting_point, upper_bound, accuracy);
            cout << endl << "=== РЕЗУЛЬТАТ (Метод послідовних наближень) ===" << endl;
            break;
        }
        case 2: {
            computation_result = newton_raphson_method(starting_point, accuracy);
            cout << endl << "=== РЕЗУЛЬТАТ (Метод Ньютона-Рафсона) ===" << endl;
            break;
        }
        default: {
            cout << "Помилка: Невірний номер методу!" << endl;
            return EXIT_FAILURE;
        }
        }

        cout << "Корінь рівняння: " << computation_result.solution_value << endl;
        cout << "Кількість ітерацій: " << computation_result.iteration_count << endl;
        cout << "Похибка: f(" << computation_result.solution_value << ") = "
            << equation_function(computation_result.solution_value) << endl;
    }
    catch (const exception& error_message) {
        cout << "Помилка виконання: " << error_message.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
