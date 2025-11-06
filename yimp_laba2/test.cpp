#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// ==================== ОБЩИЕ ФУНКЦИИ ====================

// Функция для безопасного ввода числа
int getIntInput() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный ввод. Пожалуйста, введите число: ";
    }
    return value;
}

// Функция для безопасного ввода символа
char getCharInput() {
    char value;
    cin >> value;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// Функция для безопасного ввода double
double getDoubleInput() {
    double value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный ввод. Пожалуйста, введите число: ";
    }
    return value;
}

// ==================== ЗАДАНИЕ 1 ====================

double func(double x, double y) { return x + y; }
double gunc(double x, double y) { return 2.0 * std::exp(x) - x - 1.0; }

// Метод Адамса (predictor-corrector 2-го порядка)
void AdamsMethod(double a, double b, double y_a, int n, const string& filename = "") {
    cout << "\n===== Метод Адамса =====\n" << endl;

    ofstream file;
    if (!filename.empty()) {
        file.open(filename);
        file << fixed << setprecision(15);
        file << "x\ty_approx\ty_exact\terror\n";
    }

    double h = (b - a) / n;
    double x = a;
    double y = y_a;

    cout << fixed << setprecision(15);
    cout << "x\t\ty_Adams\t\ty_exact\t\tError" << endl;

    for (int i = 0; i <= n; i++) {
        double y_exact = gunc(x, y); // аналитическое решение
        double error = std::abs(y - y_exact);

        cout << x << "\t" << y << "\t" << y_exact << "\t" << error << endl;

        if (file.is_open()) {
            file << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        }

        if (i < n) {
            // Прогнозируем следующий шаг (predictor)
            double y_pred = y + h * func(x, y);
            double x_next = x + h;

            // Корректируем (corrector)
            y = y + (h / 2.0) * (func(x, y) + func(x_next, y_pred));
            x = x_next;
        }
    }

    if (file.is_open()) {
        file.close();
        cout << "Данные сохранены в файл: " << filename << endl;
    }
}

void runZad1() {
    cout << "\n=== ЗАДАНИЕ 1: Метод Адамса ===\n";

    double a, b;
    int n;
    const double y_a = 0.0;

    // Ввод a
    while (true) {
        cout << "Введите a (начало отрезка): ";
        a = getDoubleInput();
        break;
    }

    // Ввод b
    while (true) {
        cout << "Введите b (конец отрезка): ";
        b = getDoubleInput();
        if (b <= a) {
            cout << "Ошибка! Конец отрезка b должен быть больше начала a (" << a << ").\n";
        } else {
            break;
        }
    }

    // Ввод n
    while (true) {
        cout << "Введите n (число шагов): ";
        n = getIntInput();
        if (n <= 0) {
            cout << "Ошибка! Число шагов должно быть положительным.\n";
        } else {
            break;
        }
    }

    cout << "\nВведенные значения:\n";
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "n = " << n << endl;

    string filename;
    cout << "Введите имя файла для сохранения данных (или нажмите Enter для пропуска): ";
    cin.ignore();
    getline(cin, filename);

    AdamsMethod(a, b, y_a, n, filename);
}

// ==================== ЗАДАНИЕ 2 ====================

double f1(double x, double y) { return 3.0 * x * x; }
double g1(double x, double y) { return x * x * x + 1; }

double f2(double x, double y) { return y; }
double g2(double x, double y) { return std::exp(x); }

double f3(double x, double y) { return std::exp(x); }
double g3(double x, double y) { return std::exp(x); }

double RungeKutta3Method(double a, double b, double y_a, int n,
                        double (*f)(double, double),
                        double (*g)(double, double),
                        bool flag = true,
                        const string& filename = "") {

    ofstream file;
    if (!filename.empty()) {
        file.open(filename);
        file << fixed << setprecision(15);
        file << "x\ty_approx\ty_exact\terror\n";
    }

    const double h = (b - a) / double(n);
    double x = a;
    double y = y_a;

    if (flag) {
        cout << fixed << setprecision(15);
        cout << "x\t\ty_approx\t\ty_exact\t\t|error|\n";
        cout << "---------------------------------------------------------------\n";
    }

    double k1, k2, k3;

    for (int i = 0; i < n; i++) {
        double y_exact = g(x, y);
        double error = std::fabs(y - y_exact);

        if (flag) {
            cout << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        }

        if (file.is_open()) {
            file << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        }

        k1 = h * f(x, y);
        k2 = h * f(x + (h / 2.0), y + (k1 / 2.0));
        k3 = h * f(x + h, y - k1 + 2.0 * k2);

        y = y + (k1 + 4.0 * k2 + k3) / 6.0;
        x = x + h;
    }

    // Записываем последнюю точку
    double y_exact = g(x, y);
    double error = std::fabs(y - y_exact);
    if (file.is_open()) {
        file << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        file.close();
        if (flag) {
            cout << "Данные сохранены в файл: " << filename << endl;
        }
    }

    return y;
}

void StudyErrorZad2(double a, double b, double y_a,
                   double (*f)(double, double),
                   double (*g)(double, double)) {

    cout << "\n=== Исследование погрешности ===\n";
    cout << "m\t h=10^-m\t N\t\t Error\n";
    cout << "-------------------------------------------------\n";

    vector<int> exponents = {0, 3, 5, 7};

    for (double m : exponents) {
        double h = std::pow(10, -m);
        int n = static_cast<int>((b - a) / h);
        if (n <= 0) n = 1;

        double y_approx = RungeKutta3Method(a, b, y_a, n, f, g, false);
        double y_exact = g(b, y_a);
        double error = std::fabs(y_approx - y_exact);

        cout << m << "\t " << h << "\t " << n << "\t "
                  << scientific << setprecision(6) << error << "\n";
    }
}

void runZad2() {
    cout << "\n=== ЗАДАНИЕ 2: Метод Рунге-Кутты 3-го порядка ===\n";

    const int n = 10;

    while (true) {
        int choice;
        cout << "\nВыберите уравнение:\n";
        cout << "1) y'(x)=3x^2, y(0)=1, решение y=x^3+1\n";
        cout << "2) y'(x)=y, y(0)=1, решение y=e^x\n";
        cout << "3) y'(x)=e^x, y(0)=1, решение y=e^x\n";
        cout << "0) Возврат в главное меню\n";
        cout << "Ваш выбор: ";

        choice = getIntInput();

        if (choice == 0) break;

        double a, b, y_a;
        double (*f)(double, double);
        double (*g)(double, double);

        switch (choice) {
            case 1:
                a = 0.0; b = 2.0; y_a = 1.0;
                f = f1; g = g1;
                break;
            case 2:
                a = 0.0; b = 1.0; y_a = 1.0;
                f = f2; g = g2;
                break;
            case 3:
                a = 0.0; b = 1.0; y_a = 1.0;
                f = f3; g = g3;
                break;
            default:
                cout << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
                continue;
        }

        string filename;
        cout << "Введите имя файла для сохранения данных (или нажмите Enter для пропуска): ";
        cin.ignore();
        getline(cin, filename);

        RungeKutta3Method(a, b, y_a, n, f, g, true, filename);
        StudyErrorZad2(a, b, y_a, f, g);
    }
}

// ==================== ЗАДАНИЕ 3 ====================

double RungeKutta4Method(double a, double b, double y_a, int n,
                        double (*f)(double, double),
                        double (*g)(double, double),
                        bool flag = true,
                        const string& filename = "") {

    ofstream file;
    if (!filename.empty()) {
        file.open(filename);
        file << fixed << setprecision(15);
        file << "x\ty_approx\ty_exact\terror\n";
    }

    const double h = (b - a) / double(n);
    double x = a;
    double y = y_a;

    if (flag) {
        cout << fixed << setprecision(15);
        cout << "x\t\ty_approx\t\ty_exact\t\t|error|\n";
        cout << "---------------------------------------------------------------\n";
    }

    double k1, k2, k3, k4;

    for (int i = 0; i < n; i++) {
        double y_exact = g(x, y);
        double error = std::fabs(y - y_exact);

        if (flag) {
            cout << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        }

        if (file.is_open()) {
            file << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        }

        k1 = h * f(x, y);
        k2 = h * f(x + (h / 2.0), y + (k1 / 2.0));
        k3 = h * f(x + (h / 2.0), y + (k2 / 2.0));
        k4 = h * f(x + h, y + k3);

        y = y + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
        x = x + h;
    }

    // Записываем последнюю точку
    double y_exact = g(x, y);
    double error = std::fabs(y - y_exact);
    if (file.is_open()) {
        file << x << "\t" << y << "\t" << y_exact << "\t" << error << "\n";
        file.close();
        if (flag) {
            cout << "Данные сохранены в файл: " << filename << endl;
        }
    }

    return y;
}

void StudyErrorZad3(double a, double b, double y_a,
                   double (*f)(double, double),
                   double (*g)(double, double)) {

    cout << "\n=== Исследование погрешности ===\n";
    cout << "m\t h=10^-m\t N\t\t Error\n";
    cout << "-------------------------------------------------\n";

    vector<int> exponents = {0, 3, 5, 7};

    for (double m : exponents) {
        double h = std::pow(10, -m);
        int n = static_cast<int>((b - a) / h);
        if (n <= 0) n = 1;

        double y_approx = RungeKutta4Method(a, b, y_a, n, f, g, false);
        double y_exact = g(b, y_a);
        double error = std::fabs(y_approx - y_exact);

        cout << m << "\t " << h << "\t " << n << "\t "
                  << scientific << setprecision(6) << error << "\n";
    }
}

void runZad3() {
    cout << "\n=== ЗАДАНИЕ 3: Метод Рунге-Кутты 4-го порядка ===\n";

    const int n = 10;

    while (true) {
        int choice;
        cout << "\nВыберите уравнение:\n";
        cout << "1) y'(x)=3x^2, y(0)=1, решение y=x^3+1\n";
        cout << "2) y'(x)=y, y(0)=1, решение y=e^x\n";
        cout << "3) y'(x)=e^x, y(0)=1, решение y=e^x\n";
        cout << "0) Возврат в главное меню\n";
        cout << "Ваш выбор: ";

        choice = getIntInput();

        if (choice == 0) break;

        double a, b, y_a;
        double (*f)(double, double);
        double (*g)(double, double);

        switch (choice) {
            case 1:
                a = 0.0; b = 2.0; y_a = 1.0;
                f = f1; g = g1;
                break;
            case 2:
                a = 0.0; b = 1.0; y_a = 1.0;
                f = f2; g = g2;
                break;
            case 3:
                a = 0.0; b = 1.0; y_a = 1.0;
                f = f3; g = g3;
                break;
            default:
                cout << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
                continue;
        }

        string filename;
        cout << "Введите имя файла для сохранения данных (или нажмите Enter для пропуска): ";
        cin.ignore();
        getline(cin, filename);

        RungeKutta4Method(a, b, y_a, n, f, g, true, filename);
        StudyErrorZad3(a, b, y_a, f, g);
    }
}

// ==================== ГЛАВНОЕ МЕНЮ ====================

int main() {
    cout << fixed << setprecision(15);

    while (true) {
        int choice;
        cout << "\n========== ГЛАВНОЕ МЕНЮ ==========\n";
        cout << "1. Задание 1: Метод Адамса\n";
        cout << "2. Задание 2: Метод Рунге-Кутты 3-го порядка\n";
        cout << "3. Задание 3: Метод Рунге-Кутты 4-го порядка\n";
        cout << "0. Выход из программы\n";
        cout << "Выберите задание: ";

        choice = getIntInput();

        switch (choice) {
            case 1: runZad1(); break;
            case 2: runZad2(); break;
            case 3: runZad3(); break;
            case 0:
                cout << "Программа завершена. До свидания!\n";
                return 0;
            default:
                cout << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
        }
    }

    return 0;
}
