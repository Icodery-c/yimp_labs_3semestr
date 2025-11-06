// Лабораторная работа №3. Задача 2-4-1.

#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

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

// Функция для безопасного ввода границ
void getDataInput(double& a, double& b) {
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
}

double f_exp(double x) { return std::exp(x); }
double exact_exp(double a, double b) { return std::exp(b) - std::exp(a); }

double f_sin(double x) { return std::sin(x); }
double exact_sin(double a, double b) { return -std::cos(b) + std::cos(a); }

double f_pow0(double x) { return 1.0; }
double exact_pow0(double a, double b) { return b - a; }

double f_pow1(double x) { return x; }
double exact_pow1(double a, double b) { return (b*b - a*a) / 2.0; }

double f_pow2(double x) { return x*x; }
double exact_pow2(double a, double b) { return (b*b*b - a*a*a) / 3.0; }

double f_pow3(double x) { return x*x*x; }
double exact_pow3(double a, double b) { return (b*b*b*b - a*a*a*a) / 4.0; }

double f_pow4(double x) { return x*x*x*x; }
double exact_pow4(double a, double b) { return (b*b*b*b*b - a*a*a*a*a) / 5.0; }

double f_pow5(double x) { return x*x*x*x*x; }
double exact_pow5(double a, double b) { return (b*b*b*b*b*b - a*a*a*a*a*a) / 6.0; }

double f_pow6(double x) { return x*x*x*x*x*x; }
double exact_pow6(double a, double b) { return (std::pow(b, 7) - std::pow(a, 7)) / 7.0; }

double f_pow10(double x) { return std::pow(x, 10); }
double exact_pow10(double a, double b) { return (std::pow(b, 11) - std::pow(a, 11)) / 11.0; }

double IntegralLeftDot(double a, double b, double (*f)(double)) {
    return (b-a) * f(a);
}

double IntegralCenterDot(double a, double b, double (*f)(double)) {
    return (b-a) * f((a+b) / 2.0);
}

double IntegralTrapezoid(double a, double b, double (*f)(double)) {
    return (b-a) * (f(a) + f(b)) / 2.0;
}

double IntegralSimpson(double a, double b, double (*f)(double)) {
    return (b-a) * (f(a) + 4.0 * f((a+b)/2.0) + f(b)) / 6.0;
}

double IntegralGauss3(double a, double b, double (*f)(double)) {
    double t1 = (a + b) / 2.0;
    double t2 = (b - a) / 2.0 * std::sqrt(3.0/5.0);

    double x1 = t1 - t2;
    double x2 = t1;
    double x3 = t1 + t2;

    return (b-a) * (5.0 * f(x1) + 8.0 * f(x2) + 5.0 * f(x3)) / 18.0;
}

// Функция для вычисления максимума функции на отрезке [a, b]
double abs_func_norm(double a, double b, double (*f)(double)) {
    int N = 1000;
    double h = (b - a) / N;
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

// Производные для оценки погрешностей
double f_exp_deriv1(double x) { return std::exp(x); }
double f_exp_deriv2(double x) { return std::exp(x); }

double f_exp_deriv4(double x) { return std::exp(x); }
double f_exp_deriv6(double x) { return std::exp(x); }

double f_sin_deriv1(double x) { return std::cos(x); }
double f_sin_deriv2(double x) { return -std::sin(x); }
double f_sin_deriv4(double x) { return std::sin(x); }
double f_sin_deriv6(double x) { return -std::sin(x); }

double f_pow0_deriv1(double x) { return 0.0; }
double f_pow0_deriv2(double x) { return 0.0; }
double f_pow0_deriv4(double x) { return 0.0; }
double f_pow0_deriv6(double x) { return 0.0; }

double f_pow1_deriv1(double x) { return 1.0; }
double f_pow1_deriv2(double x) { return 0.0; }
double f_pow1_deriv4(double x) { return 0.0; }
double f_pow1_deriv6(double x) { return 0.0; }

double f_pow2_deriv1(double x) { return 2.0 * x; }
double f_pow2_deriv2(double x) { return 2.0; }
double f_pow2_deriv4(double x) { return 0.0; }
double f_pow2_deriv6(double x) { return 0.0; }

double f_pow3_deriv1(double x) { return 3.0 * x * x; }
double f_pow3_deriv2(double x) { return 6.0 * x; }
double f_pow3_deriv4(double x) { return 0.0; }
double f_pow3_deriv6(double x) { return 0.0; }

double f_pow4_deriv1(double x) { return 4.0 * std::pow(x, 3); }
double f_pow4_deriv2(double x) { return 12.0 * x * x; }
double f_pow4_deriv4(double x) { return 24.0; }
double f_pow4_deriv6(double x) { return 0.0; }

double f_pow5_deriv1(double x) { return 5.0 * std::pow(x, 4); }
double f_pow5_deriv2(double x) { return 20.0 * std::pow(x, 3); }
double f_pow5_deriv4(double x) { return 60.0 * x * x; }
double f_pow5_deriv6(double x) { return 0.0; }

double f_pow6_deriv1(double x) { return 6.0 * std::pow(x, 5); }
double f_pow6_deriv2(double x) { return 30.0 * std::pow(x, 4); }
double f_pow6_deriv4(double x) { return 360.0 * x * x; }
double f_pow6_deriv6(double x) { return 720.0; }

double f_pow10_deriv1(double x) { return 10.0 * std::pow(x, 9); }
double f_pow10_deriv2(double x) { return 90.0 * std::pow(x, 8); }
double f_pow10_deriv4(double x) { return 5040.0 * std::pow(x, 6); }
double f_pow10_deriv6(double x) { return 151200.0 * std::pow(x, 4); }

// Функции оценки погрешности
double err_rectangle_left_point(double a, double b, double (*f_deriv)(double)) {
    return abs_func_norm(a, b, f_deriv) * std::pow(b - a, 2.0) / 2.0;
}

double err_rectangle_middle_point(double a, double b, double (*f_deriv)(double)) {
    return abs_func_norm(a, b, f_deriv) * std::pow(b - a, 3.0) / 24.0;
}

double err_trapezoid(double a, double b, double (*f_deriv)(double)) {
    return abs_func_norm(a, b, f_deriv) * std::pow(b - a, 3.0) / 12.0;
}

double err_simpson(double a, double b, double (*f_deriv)(double)) {
    return abs_func_norm(a, b, f_deriv) * std::pow(b - a, 5.0) / 2880.0;
}

double err_3nodes_gauss(double a, double b, double (*f_deriv)(double)) {
    return abs_func_norm(a, b, f_deriv) * std::pow(b - a, 7.0) / 2016000.0;
}

int main() {
    std::cout << std::fixed << std::setprecision(15);

    // Массивы для хранения информации о методах интегрирования
    std::string method_names[] = {
        "LeftRectangle", "CenterRectangle", "Trapezoid", "Simpson", "Gauss3"
    };

    double (*methods[])(double, double, double (*)(double)) = {
        IntegralLeftDot, IntegralCenterDot, IntegralTrapezoid,
        IntegralSimpson, IntegralGauss3
    };

    double (*error_funcs[])(double, double, double (*)(double)) = {
        err_rectangle_left_point, err_rectangle_middle_point, err_trapezoid,
        err_simpson, err_3nodes_gauss
    };

    while (true) {
        int choice;
        std::cout << "\nВыберите уравнение:\n";
        std::cout << "1) y = sin(x)\n";
        std::cout << "2) y = x^n\n";
        std::cout << "3) y = e^x\n";
        std::cout << "0) Выход из программы\n";
        std::cout << "Ваш выбор: ";

        choice = getIntInput();

        if (choice == 0) {
            std::cout << "Программа завершена.\n";
            break;
        }

        double a, b;
        double (*f)(double);
        double (*exact)(double, double);
        double (*derivatives[5])(double); // Производные для каждого метода
        // Выбор степени для степенной функции
        int power = 0;
        if (choice == 2) {
            std::cout << "Введите степень n: ";
            power = getIntInput();
        }

        // Установка функции и ее точного значения
        switch (choice) {
            case 1:
                getDataInput(a, b);
                f = f_sin;
                exact = exact_sin;
                // Установка производных для методов
                derivatives[0] = f_sin_deriv1;
                derivatives[1] = f_sin_deriv2;
                derivatives[2] = f_sin_deriv2;
                derivatives[3] = f_sin_deriv4;
                derivatives[4] = f_sin_deriv6;
                break;
            case 2:
                getDataInput(a, b);
                // Выбор соответствующей степенной функции
                switch (power) {
                    case 0:
                        f = f_pow0; exact = exact_pow0;
                        derivatives[0] = f_pow0_deriv1;
                        derivatives[1] = f_pow0_deriv2;
                        derivatives[2] = f_pow0_deriv2;
                        derivatives[3] = f_pow0_deriv4;
                        derivatives[4] = f_pow0_deriv6;
                        break;
                    case 1:
                        f = f_pow1; exact = exact_pow1;
                        derivatives[0] = f_pow1_deriv1;
                        derivatives[1] = f_pow1_deriv2;
                        derivatives[2] = f_pow1_deriv2;
                        derivatives[3] = f_pow1_deriv4;
                        derivatives[4] = f_pow1_deriv6;
                        break;
                    case 2:
                        f = f_pow2; exact = exact_pow2;
                        derivatives[0] = f_pow2_deriv1;
                        derivatives[1] = f_pow2_deriv2;
                        derivatives[2] = f_pow2_deriv2;
                        derivatives[3] = f_pow2_deriv4;
                        derivatives[4] = f_pow2_deriv6;
                        break;
                    case 3:
                        f = f_pow3; exact = exact_pow3;
                        derivatives[0] = f_pow3_deriv1;
                        derivatives[1] = f_pow3_deriv2;
                        derivatives[2] = f_pow3_deriv2;
                        derivatives[3] = f_pow3_deriv4;
                        derivatives[4] = f_pow3_deriv6;
                        break;
                    case 4:
                        f = f_pow4; exact = exact_pow4;
                        derivatives[0] = f_pow4_deriv1;
                        derivatives[1] = f_pow4_deriv2;
                        derivatives[2] = f_pow4_deriv2;
                        derivatives[3] = f_pow4_deriv4;
                        derivatives[4] = f_pow4_deriv6;
                        break;
                    case 5:
                        f = f_pow5; exact = exact_pow5;
                        derivatives[0] = f_pow5_deriv1;
                        derivatives[1] = f_pow5_deriv2;
                        derivatives[2] = f_pow5_deriv2;
                        derivatives[3] = f_pow5_deriv4;
                        derivatives[4] = f_pow5_deriv6;
                        break;
                    case 6:
                        f = f_pow6; exact = exact_pow6;
                        derivatives[0] = f_pow6_deriv1;
                        derivatives[1] = f_pow6_deriv2;
                        derivatives[2] = f_pow6_deriv2;
                        derivatives[3] = f_pow6_deriv4;
                        derivatives[4] = f_pow6_deriv6;
                        break;
                    case 10:
                        f = f_pow10; exact = exact_pow10;
                        derivatives[0] = f_pow10_deriv1;
                        derivatives[1] = f_pow10_deriv2;
                        derivatives[2] = f_pow10_deriv2;
                        derivatives[3] = f_pow10_deriv4;
                        derivatives[4] = f_pow10_deriv6;
                        break;
                    default:
                    std::cout << "Степень " << power << " не поддерживается. Используется n=6.\n";
                        f = f_pow6; exact = exact_pow6;
                        derivatives[0] = f_pow6_deriv1;
                        derivatives[1] = f_pow6_deriv2;
                        derivatives[2] = f_pow6_deriv2;
                        derivatives[3] = f_pow6_deriv4;
                        derivatives[4] = f_pow6_deriv6;
                        break;
                }
                break;
            case 3:
                getDataInput(a, b);
                f = f_exp;
                exact = exact_exp;
                derivatives[0] = f_exp_deriv1;
                derivatives[1] = f_exp_deriv2;
                derivatives[2] = f_exp_deriv2;
                derivatives[3] = f_exp_deriv4;
                derivatives[4] = f_exp_deriv6;
                break;
            default:
                std::cerr << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
                continue;
        }

        double exact_value = exact(a, b);

        // Вывод заголовка таблицы
        std::cout << "\n" << std::string(100, '-') << "\n";
        std::cout << "IntegralMethod\t\tapprox\t\t\texact\t\t\test_error\t\terror\n";
        std::cout << std::string(100, '-') << "\n";

        // Вычисление и вывод результатов для каждого метода
        for (int i = 0; i < 5; i++) {
            double approx = methods[i](a, b, f);
            double error = std::fabs(exact_value - approx);
            double est_error = error_funcs[i](a, b, derivatives[i]);

            std::cout << method_names[i] << "\t\t"
                      << approx << "\t"
                      << exact_value << "\t"
                      << est_error << "\t"
                      << error << "\n";
        }
        std::cout << std::string(100, '-') << "\n";

        while (true) {
            std::cout << "\nХотите решить другое уравнение? (y/n): ";
            char continue_choice = getCharInput();

            if (continue_choice == 'n' || continue_choice == 'N') {
                std::cout << "Программа завершена.\n";
                return 0;
            }
            else if (continue_choice == 'y' || continue_choice == 'Y') {
                break;
            }
            else {
                std::cout << "Неверный ввод. Пожалуйста, введите 'y' или 'n'.\n";
            }
        }
    }

    return 0;
}
