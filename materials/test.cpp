// Лабораторная работа №3. Задача 2-4-2. Улучшенная версия

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>

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

// Составные квадратурные формулы
double IntegralLeftDot(double a, double b, double (*f)(double), int N) {
    double h = (b - a) / N;
    double result = 0.0;
    for (int i = 0; i < N; i++) {
        result += f(a + i * h);
    }
    return result * h;
}

double IntegralCenterDot(double a, double b, double (*f)(double), int N) {
    double h = (b - a) / N;
    double result = 0.0;
    for (int i = 0; i < N; i++) {
        result += f(a + (i + 0.5) * h);
    }
    return result * h;
}

double IntegralTrapezoid(double a, double b, double (*f)(double), int N) {
    double h = (b - a) / N;
    double result = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < N; i++) {
        result += f(a + i * h);
    }
    return result * h;
}

double IntegralSimpson(double a, double b, double (*f)(double), int N) {
    if (N % 2 != 0) N++; // Убедимся, что N четное для метода Симпсона
    double h = (b - a) / N;
    double result = f(a) + f(b);

    for (int i = 1; i < N; i++) {
        double coefficient = (i % 2 == 0) ? 2.0 : 4.0;
        result += coefficient * f(a + i * h);
    }

    return result * h / 3.0;
}

double IntegralGauss3(double a, double b, double (*f)(double), int N) {
    double h = (b - a) / N;
    double result = 0.0;

    // Узлы и веса для квадратуры Гаусса с 3 узлами
    const double xi[3] = { -std::sqrt(3.0/5.0), 0.0, std::sqrt(3.0/5.0) };
    const double wi[3] = { 5.0/9.0, 8.0/9.0, 5.0/9.0 };

    for (int i = 0; i < N; i++) {
        double x0 = a + i * h;
        double x1 = a + (i + 1) * h;
        double xm = (x0 + x1) / 2.0;
        double xr = (x1 - x0) / 2.0;

        for (int j = 0; j < 3; j++) {
            result += wi[j] * f(xm + xr * xi[j]);
        }
    }

    return result * h / 2.0;
}

// Улучшенные тестовые функции
double f1(double x) {
    // cos(1000x) - очень быстрые осцилляции
    return std::cos(1000.0 * x);
}

double f2(double x) {
    // exp(-1000x) - очень быстро убывающая функция
    return std::exp(-1000.0 * x);
}

double f3(double x) {
    // 1/sqrt(1-x^2) - особенность на границах
    // Используем более безопасный подход
    double delta = 1e-10;
    if (x >= 1.0 - delta) x = 1.0 - delta;
    if (x <= -1.0 + delta) x = -1.0 + delta;
    return 1.0 / std::sqrt(1.0 - x * x);
}

// Аналитические решения
double exact_f1() {
    // ∫cos(1000x)dx от 0 до 100π = [sin(1000x)/1000] = 0
    return 0.0;
}

double exact_f2() {
    // ∫exp(-1000x)dx от 0 до 100 = [-exp(-1000x)/1000] = (1 - exp(-100000))/1000 ≈ 0.001
    return (1.0 - std::exp(-100000.0)) / 1000.0;
}

double exact_f3() {
    // ∫1/sqrt(1-x^2)dx от -1 до 1 = [arcsin(x)] = π
    return M_PI;
}

int main() {
    std::cout << std::fixed << std::setprecision(15);

    // Массивы методов интегрирования
    std::string method_names[] = {
        "LeftRectangle", "CenterRectangle", "Trapezoid", "Simpson", "Gauss3"
    };

    double (*methods[])(double, double, double (*)(double), int) = {
        IntegralLeftDot, IntegralCenterDot, IntegralTrapezoid,
        IntegralSimpson, IntegralGauss3
    };

    // Тестовые случаи с улучшенными параметрами
    struct TestCase {
        std::string name;
        double (*f)(double);
        double (*exact)();
        double a, b;
        std::vector<int> N_values;
        std::string description;
    };

    std::vector<TestCase> test_cases = {
        {
            "cos(1000x)", f1, exact_f1, 0, 100 * M_PI,
            {100000, 500000, 1000000, 5000000, 10000000},
            //"Быстроосциллирующая функция - требуется очень много разбиений"
        },
        {
            "exp(-1000x)", f2, exact_f2, 0, 100,
            {10000, 50000, 100000, 500000, 1000000},
            //"Быстроубывающая функция - важна точность в начале отрезка"
        },
        {
            "1/sqrt(1-x^2)", f3, exact_f3, -1, 1,
            {1000, 5000, 10000, 50000, 100000},
            //"Функция с особенностями на границах - избегаем точек ±1"
        }
    };

    while (true) {
        std::cout << "\nВыберите тестовую функцию:\n";
        std::cout << "1) cos(1000x) на [0, 100π]\n";
        std::cout << "2) exp(-1000x) на [0, 100]\n";
        std::cout << "3) 1/sqrt(1-x^2) на [-, 1]\n";
        std::cout << "0) Выход из программы\n";
        std::cout << "Ваш выбор: ";

        int choice = getIntInput();

        if (choice == 0) {
            std::cout << "Программа завершена.\n";
            break;
        }

        if (choice < 1 || choice > 3) {
            std::cout << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
            continue;
        }

        TestCase test = test_cases[choice - 1];
        double exact_value = test.exact();

        std::cout << "\n" << std::string(120, '=') << "\n";
        std::cout << "Функция: " << test.name << " на [" << test.a << ", " << test.b << "]\n";
        std::cout << "Точное значение: " << exact_value << "\n";
        //std::cout << "Описание: " << test.description << "\n";
        std::cout << std::string(120, '=') << "\n";

        // Вывод таблицы для каждого метода
        for (int method_idx = 0; method_idx < 5; method_idx++) {
            std::cout << "\n" << std::string(100, '-') << "\n";
            std::cout << "Method: " << method_names[method_idx] << "\n";
            std::cout << std::string(100, '-') << "\n";
            std::cout << "N\t\tApproximate\t\tExact\t\t\tError\t\t\tEstError\n";
            std::cout << std::string(100, '-') << "\n";

            for (int N : test.N_values) {
                double approx = methods[method_idx](test.a, test.b, test.f, N);
                double error = std::fabs(exact_value - approx);
                double relative = (exact_value != 0) ? error / std::fabs(exact_value) : error;

                std::cout << N << "\t\t"
                          << std::setw(15) << approx << "\t"
                          << std::setw(15) << exact_value << "\t"
                          << std::setw(15) << error << "\t"
                          << std::setw(15) << relative << "\n";
            }
            std::cout << std::string(100, '-') << "\n";
        }



        // Запрос на продолжение
        while (true) {
            std::cout << "\nХотите протестировать другую функцию? (y/n): ";
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
