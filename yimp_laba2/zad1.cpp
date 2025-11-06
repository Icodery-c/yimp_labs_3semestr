#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

// double func(double x, double y) { return 2.0 * x * (x * x + y); }
// double gunc (double x, double y) { return -x * x - 1.0 + 2.0 * std::exp(x * x);}

// double func ( double x, double y) { return std::cos(x); }
//double gunc ( double x, double y) { return std::sin(x); }

double func(double x, double y) { return x+y; }
double gunc (double x, double y) { return 2.0 * std::exp(x) - x - 1.0;}

//Метод Адамса (predictor-corrector 2-го порядка)
void AdamsMethod(double a, double b, double y_a, int n) {

    std::cout << "\n===== Метод Адамса =====\n" << std::endl;

    double h = (b - a) / double(n);
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


int main () {

   double a; double b;

   int n;

   const double y_a = 0.0;

   //std::cout << "Введите a (начало отрезка): "; std::cin >> a;
   //std::cout << "Введите b (конец отрезка): ";  std::cin >> b;
   //std::cout << "Введите n (число шагов): "; std::cin >> n;


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
