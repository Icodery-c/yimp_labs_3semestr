#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <vector>

// ==================== ЗАДАНИЕ 1 ====================

double func(double x, double y) { return 2.0 * x * (x * x + y); }
double gunc(double x, double y) { return -x * x - 1 + 2 * std::exp(x * x); }

// Метод Адамса (predictor-corrector 2-го порядка)
void AdamsMethod(double a, double b, double y_a, int n) {
    std::cout << "\n===== Метод Адамса =====\n" << std::endl;

    double h = (b - a) / n;
    double x = a;
    double y = y_a;

    std::cout << std::fixed << std::setprecision(15);
    std::cout << "x\t\ty_Adams\t\ty_exact\t\tError" << std::endl;

    for (int i = 0; i <= n; i++) {
        double y_exact = std::sin(x); // аналитическое решение
        double error = std::abs(y - y_exact);

        std::cout << x << "\t" << y << "\t" << y_exact << "\t" << error << std::endl;

        // Прогнозируем следующий шаг (predictor)
        double y_pred = y + h * func(x, y);
        double x_next = x + h;

        // Корректируем (corrector)
        y = y + (h / 2.0) * (func(x, y) + func(x_next, y_pred));
        x = x_next;
    }
}

void runZad1() {
    std::cout << "\n=== ЗАДАНИЕ 1: Метод Адамса ===\n";

    double a, b;
    int n;
    const double y_a = 0.0;

    // Ввод a
    while (true) {
        std::cout << "Введите a (начало отрезка): ";
        std::cin >> a;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Пожалуйста, введите число.\n";
        } else {
            break;
        }
    }

    // Ввод b
    while (true) {
        std::cout << "Введите b (конец отрезка): ";
        std::cin >> b;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Пожалуйста, введите число.\n";
        } else if (b <= a) {
            std::cout << "Ошибка! Конец отрезка b должен быть больше начала a (" << a << ").\n";
        } else {
            break;
        }
    }

    // Ввод n
    while (true) {
        std::cout << "Введите n (число шагов): ";
        std::cin >> n;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка! Пожалуйста, введите число.\n";
        } else if (n <= 0) {
            std::cout << "Ошибка! Число шагов должно быть положительным.\n";
        } else {
            break;
        }
    }

    std::cout << "\nВведенные значения:\n";
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "n = " << n << std::endl;

    AdamsMethod(a, b, y_a, n);
}

// ==================== ЗАДАНИЕ 2 ====================

double f1(double x, double y) { return 3.0 * x * x; }
double g1(double x, double y) { return x * x * x + 1; } // исправлено: +1 для y(0)=1

double f2(double x, double y) { return y; }
double g2(double x, double y) { return std::exp(x); }

double f3(double x, double y) { return std::exp(x); }
double g3(double x, double y) { return std::exp(x); }

double f4(double x, double y) { return std::sin(x) + std::cos(x); }
double g4(double x, double y) { return std::sin(x) - std::cos(x) + 2.0; }

double f5(double x, double y) { return std::cos(x); }
double g5(double x, double y) { return std::sin(x) + 1; } // исправлено: +1 для y(0)=1

double RungeKutta3Method(double a, double b, double y_a, int n,
                        double (*f)(double, double),
                        double (*g)(double, double), bool flag = true) {

    const double h = (b - a) / double(n);
    double x = a;
    double y = y_a;

    if (flag) {
        std::cout << std::fixed << std::setprecision(15);
        std::cout << "x\t\ty_approx\t\ty_exact\t\t|error|\n";
        std::cout << "---------------------------------------------------------------\n";
    }

    double k1, k2, k3;

    for (int i = 0; i < n; i++) {
        double y_exact = g(x, y);
        double error = std::fabs(y - y_exact);

        if (flag) {
            std::cout << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        }

        k1 = h * f(x, y);
        k2 = h * f(x + (h / 2.0), y + (k1 / 2.0));
        k3 = h * f(x + h, y - k1 + 2.0 * k2);

        y = y + (k1 + 4.0 * k2 + k3) / 6.0;
        x = x + h;
    }

    return y;
}

void StudyErrorZad2(double a, double b, double y_a,
                   double (*f)(double, double),
                   double (*g)(double, double)) {

    std::cout << "\n=== Исследование погрешности ===\n";
    std::cout << "m\t h=10^-m\t N\t\t Error\n";
    std::cout << "-------------------------------------------------\n";

    std::vector<int> exponents = {0, 3, 5, 7};

    for (double m : exponents) {
        double h = std::pow(10, -m);
        int n = static_cast<int>((b - a) / h);
        if (n <= 0) n = 1;

        double y_approx = RungeKutta3Method(a, b, y_a, n, f, g, false);
        double y_exact = g(b, y_a);
        double error = std::fabs(y_approx - y_exact);

        std::cout << m << "\t " << h << "\t " << n << "\t "
                  << std::scientific << std::setprecision(15) << error << "\n";
    }
}

void runZad2() {
    std::cout << "\n=== ЗАДАНИЕ 2: Метод Рунге-Кутты 3-го порядка ===\n";

    const double y_a = 1.0;
    const int n = 10;

    while (true) {
        int choice;
        std::cout << "\nВыберите уравнение:\n";
        std::cout << "1) y'(x)=3x^2, y(0)=1, решение y=x^3+1\n";
        std::cout << "2) y'(x)=y, y(0)=1, решение y=e^x\n";
        std::cout << "3) y'(x)=e^x, y(0)=1, решение y=e^x\n";
        std::cout << "4) y'(x)=sinx+cosx, y(0)=1, решение y=sinx-cosx+2\n";
        std::cout << "5) y'(x)=cosx, y(0)=1, решение y=sinx+1\n";
        std::cout << "0) Возврат в главное меню\n";
        std::cout << "Ваш выбор: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод!\n";
            continue;
        }

        if (choice == 0) break;

        double a, b;
        double (*f)(double, double);
        double (*g)(double, double);

        switch (choice) {
            case 1: a = 0.0; b = 2.0; f = f1; g = g1; break;
            case 2: a = 0.0; b = 1.0; f = f2; g = g2; break;
            case 3: a = 0.0; b = 1.0; f = f3; g = g3; break;
            case 4: a = 0.0; b = 2.0; f = f4; g = g4; break;
            case 5: a = 0.0; b = 2.0; f = f5; g = g5; break;
            default:
                std::cout << "Неверный выбор! Пожалуйста, выберите 0-5.\n";
                continue;
        }

        RungeKutta3Method(a, b, y_a, n, f, g);
        StudyErrorZad2(a, b, y_a, f, g);
    }
}

// ==================== ЗАДАНИЕ 3 ====================

double RungeKutta4Method(double a, double b, double y_a, int n,
                        double (*f)(double, double),
                        double (*g)(double, double), bool flag = true) {

    const double h = (b - a) / double(n);
    double x = a;
    double y = y_a;

    if (flag) {
        std::cout << std::fixed << std::setprecision(15);
        std::cout << "x\t\ty_approx\t\ty_exact\t\t|error|\n";
        std::cout << "---------------------------------------------------------------\n";
    }

    double k1, k2, k3, k4;

    for (int i = 0; i < n; i++) {
        double y_exact = g(x, y);
        double error = std::fabs(y - y_exact);

        if (flag) {
            std::cout << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        }

        k1 = h * f(x, y);
        k2 = h * f(x + (h / 2.0), y + (k1 / 2.0));
        k3 = h * f(x + (h / 2.0), y + (k2 / 2.0));
        k4 = h * f(x + h, y + k3);

        y = y + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        x = x + h;
    }

    return y;
}

void StudyErrorZad3(double a, double b, double y_a,
                   double (*f)(double, double),
                   double (*g)(double, double)) {

    std::cout << "\n=== Исследование погрешности ===\n";
    std::cout << "m\t h=10^-m\t N\t\t Error\n";
    std::cout << "-------------------------------------------------\n";

    std::vector<int> exponents = {0, 3, 5, 7};

    for (double m : exponents) {
        double h = std::pow(10, -m);
        int n = static_cast<int>((b - a) / h);
        if (n <= 0) n = 1;

        double y_approx = RungeKutta4Method(a, b, y_a, n, f, g, false);
        double y_exact = g(b, y_a);
        double error = std::fabs(y_approx - y_exact);

        std::cout << m << "\t " << h << "\t " << n << "\t "
                  << std::scientific << std::setprecision(15) << error << "\n";
    }
}

void runZad3() {
    std::cout << "\n=== ЗАДАНИЕ 3: Метод Рунге-Кутты 4-го порядка ===\n";

    const double y_a = 1.0;
    const int n = 10;

    while (true) {
        int choice;
        std::cout << "\nВыберите уравнение:\n";
        std::cout << "1) y'(x)=3x^2, y(0)=1, решение y=x^3+1\n";
        std::cout << "2) y'(x)=y, y(0)=1, решение y=e^x\n";
        std::cout << "3) y'(x)=e^x, y(0)=1, решение y=e^x\n";
        std::cout << "4) y'(x)=sinx+cosx, y(0)=1, решение y=sinx-cosx+2\n";
        std::cout << "5) y'(x)=cosx, y(0)=1, решение y=sinx+1\n";
        std::cout << "0) Возврат в главное меню\n";
        std::cout << "Ваш выбор: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод!\n";
            continue;
        }

        if (choice == 0) break;

        double a, b;
        double (*f)(double, double);
        double (*g)(double, double);

        switch (choice) {
            case 1: a = 0.0; b = 2.0; f = f1; g = g1; break;
            case 2: a = 0.0; b = 1.0; f = f2; g = g2; break;
            case 3: a = 0.0; b = 1.0; f = f3; g = g3; break;
            case 4: a = 0.0; b = 2.0; f = f4; g = g4; break;
            case 5: a = 0.0; b = 2.0; f = f5; g = g5; break;
            default:
                std::cout << "Неверный выбор! Пожалуйста, выберите 0-5.\n";
                continue;
        }

        RungeKutta4Method(a, b, y_a, n, f, g);
        StudyErrorZad3(a, b, y_a, f, g);
    }
}

// ==================== ГЛАВНОЕ МЕНЮ ====================

int main() {
    std::cout << std::fixed << std::setprecision(15);

    while (true) {
        int choice;
        std::cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n";
        std::cout << "1. Задание 1: Метод Адамса\n";
        std::cout << "2. Задание 2: Метод Рунге-Кутты 3-го порядка\n";
        std::cout << "3. Задание 3: Метод Рунге-Кутты 4-го порядка\n";
        std::cout << "0. Выход из программы\n";
        std::cout << "Выберите задание: ";

        std::cin >> choice;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод! Пожалуйста, введите число.\n";
            continue;
        }

        switch (choice) {
            case 1: runZad1(); break;
            case 2: runZad2(); break;
            case 3: runZad3(); break;
            case 0:
                std::cout << "Программа завершена. До свидания!\n";
                return 0;
            default:
                std::cout << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
        }
    }

    return 0;
}
