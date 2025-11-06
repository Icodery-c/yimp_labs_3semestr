
// Лабораторная работа №3. Задача 2-4-2.

#include <iostream>
#include <cmath>
#include <iomanip>

// Функция для безопасного ввода числа
int getIntInput() {
    int value;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод. Пожалуйста, введите число: ";
    }
    return value;
}

// Функция для безопасного ввода символа
char getCharInput() {
    char value;
    std::cin >> value;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

double IntegralLeftDot (double a, double b, double (*f) (double), int N ) {

  double h = (b - a) / double(N);

  double result = 0.0;

  for (int i = 0; i < N; i++) { result += f(a + double(i) * h); }

  return result * h;
}

double IntegralCenterDot (double a, double b, double (*f) (double), int N ) {

  double h = (b - a) / double(N);

  double result = 0.0;

  for (int i = 0; i < N; i++) { result += f(a + (double(i) + 0.5) * h); }

  return result * h;

}

double IntegralTrapezoid (double a, double b, double (*f) (double), int N ) {

  double h = (b - a) / double(N);

  double result = (f(a) + f(b)) / 2.0;

  for (int i = 1; i < N; i++) { result += f(a + double(i) * h); }

  return result * h;

}

double IntegralSimpson (double a, double b, double (*f) (double), int N ) {

  double h = (b - a) / double(N);

  double result = f(a) + f(b);

  for (int i = 1; i < N; i++) { double x = (a + double(i) * h); result += (i % 2 == 0 ? 2.0 : 4.0) * f(x); }

  return h * result / 3.0;

}

double IntegralGauss3 (double a, double b, double (*f) (double), int N ) {

  double h = (b - a) / double(N);

  double result = 0.0;

  double xi[3] = { -std::sqrt(3.0 / 5.0), 0.0, std::sqrt(3.0 / 5.0) };
  double wi[3] = { 5.0 / 9.0, 8.0 / 9.0, 5.0 / 9.0 };

  for (int i = 0; i < N; i++) {

    double x0 = a + double(i) * h;
    double x1 = a + (double(i) + 1.0) * h;

    double xm = (x0 + x1) / 2.0;
    double xr = (x1 - x0) / 2.0;

    for (int j = 0; j < 3; j++) { result += wi[j] * f(xm + xr * xi[i]); }

  }

  return (result * h) / 2.0;

}

double f1(double x) { return std::cos(1000.0 * x); }
double exact_f1(double a, double b) { return 0.0; } // ∫cos(1000x)dx = 0

double f2(double x) { return std::exp(-1000.0 * x); }
double exact_f2(double a, double b) {
    return (1.0 - std::exp(-1000.0 * b)) / 1000.0;
}

double f3(double x) {
    // Избегаем деления на ноль в концах отрезка
    if (x <= -1.0 + 1e-12 || x >= 1.0 - 1e-12) {
        return 0.0;
    }
    return 1.0 / std::sqrt(1.0 - x * x);
}
double exact_f3(double a, double b) {
    return std::asin(b) - std::asin(a);
}

double abs_func_norm(double a, double b, double (*f)(double), int N) {

    double h = (b - a) / double(N);
    double max_val = 0.0;

    for (int i = 0; i <= N; i++) {
        double x = a + i * h;
        double cur_val = std::fabs(f(x));
        if (cur_val > max_val) {
            max_val = cur_val;
        }
    }
    return max_val;
}

// f1''''''(x) = -1000000000000000000 * cos(1000x)
double f1_deriv6(double x) {
    return -1000000000000000000.0 * std::cos(1000.0 * x);
}

// f2(x) = exp(-1000x)
// f2'(x) = -1000 * exp(-1000x)
double f2_deriv(double x) {
    return -1000.0 * std::exp(-1000.0 * x);
}

// f2''(x) = 1000000 * exp(-1000x)
double f2_deriv2(double x) {
    return 1000000.0 * std::exp(-1000.0 * x);
}

// f2''''(x) = 1000000000000 * exp(-1000x)
double f2_deriv4(double x) {
    return 1000000000000.0 * std::exp(-1000.0 * x);
}

// f2''''''(x) = 1000000000000000000 * exp(-1000x)
double f2_deriv6(double x) {
    return 1000000000000000000.0 * std::exp(-1000.0 * x);
}

// f3(x) = 1/sqrt(1-x^2)
// f3'(x) = x/((1-x^2)^(3/2))
double f3_deriv(double x) {
    double delta = 1e-10;
    if (x >= 1.0 - delta) x = 1.0 - delta;
    if (x <= -1.0 + delta) x = -1.0 + delta;
    return x / std::pow(1.0 - x*x, 1.5);
}

// f3''(x) = (2x^2+1)/((1-x^2)^(5/2))
double f3_deriv2(double x) {
    double delta = 1e-10;
    if (x >= 1.0 - delta) x = 1.0 - delta;
    if (x <= -1.0 + delta) x = -1.0 + delta;
    return (2.0*x*x + 1.0) / std::pow(1.0 - x*x, 2.5);
}

// f3''''(x) - сложное выражение, упростим вычисление
double f3_deriv4(double x) {
    double delta = 1e-10;
    if (x >= 1.0 - delta) x = 1.0 - delta;
    if (x <= -1.0 + delta) x = -1.0 - delta;
    double x2 = x*x;
    double denom = std::pow(1.0 - x2, 4.5);
    return (24.0*x2*x2 + 72.0*x2 + 9.0) / denom;
}

// f3''''''(x) - очень сложное выражение
double f3_deriv6(double x) {
    double delta = 1e-10;
    if (x >= 1.0 - delta) x = 1.0 - delta;
    if (x <= -1.0 + delta) x = -1.0 - delta;
    double x2 = x*x;
    double denom = std::pow(1.0 - x2, 7.5);
    return (720.0*x2*x2*x2 + 3240.0*x2*x2 + 2430.0*x2 + 225.0) / denom;
}

// Функции оценки погрешности
double err_rectangle_left_point(double a, double b, double (*f_deriv)(double), int N) {
    double h = (b - a) / N;
    return abs_func_norm(a, b, f_deriv) * std::pow(b - a, 2.0) / (2.0 * N);
}

double err_rectangle_middle_point(double a, double b, double (*f_deriv2)(double), int N) {
    double h = (b - a) / N;
    return abs_func_norm(a, b, f_deriv2) * std::pow(b - a, 3.0) / (24.0 * N * N);
}

double err_trapezoid(double a, double b, double (*f_deriv2)(double), int N) {
    double h = (b - a) / N;
    return abs_func_norm(a, b, f_deriv2) * std::pow(b - a, 3.0) / (12.0 * N * N);
}

double err_simpson(double a, double b, double (*f_deriv4)(double), int N) {
    double h = (b - a) / N;
    return abs_func_norm(a, b, f_deriv4) * std::pow(b - a, 5.0) / (2880.0 * N * N * N * N);
}

double err_3nodes_gauss(double a, double b, double (*f_deriv6)(double), int N) {
    double h = (b - a) / N;
    return abs_func_norm(a, b, f_deriv6) * std::pow(b - a, 7.0) / (2016000.0 * N * N * N * N * N * N);
}



int main() {
    std::cout << std::fixed << std::setprecision(15);
    int N = 10000;

    std::cout << "Integral cos(1000x): "
              << IntegralTrapezoid(0, 100 * M_PI, f1, N) << std::endl;
    std::cout << "Integral exp(-1000x): "
              << IntegralTrapezoid(0, 100, f2, N) << std::endl;
    std::cout << "Integral 1/sqrt(1-x^2): "
              << IntegralSimpson(-1, 1, f3, N) << std::endl;
}
