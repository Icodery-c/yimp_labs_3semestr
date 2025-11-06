#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <vector>

double f1 ( double x, double y) { return 3.0 * x * x; }
double g1 ( double x, double y) { return x * x * x; }
//double f1 (double x, double y) { return 2.0 * x * (x * x + y); }
//double g1 (double x, double y) { return -x * x - 1 + 2 * std::exp(x * x);}

double f2 ( double x, double y) { return y; }
double g2 ( double x, double y) { return std::exp(x); }

double f3 ( double x, double y) { return std::exp(x); }
double g3 ( double x, double y) { return std::exp(x); }

double RungeKutta4Method (double a, double b, double y_a, int n,
                        double (*f) (double, double),
                        double (*g) (double, double), bool flag = true) {

    const double h = (b - a) / double(n);

    double x_0 = a;
    double y_0 = y_a;

    double x = x_0;
    double y = y_0;

    //std::cout << std::fixed << std::setprecision(15);
    //std::cout << "x\t\ty_approx\t\ty_exact\t\t|error|\n";
    //std::cout << "---------------------------------------------------------------\n";
    if (flag) {
          std::cout << std::fixed << std::setprecision(15);
          std::cout << "x\t\ty_approx\t\ty_exact\t\t|error|\n";
          std::cout << "---------------------------------------------------------------\n";
    }

    double k1 = 0.0, k2 = 0.0, k3 = 0.0, k4 = 0.0;

    for (int i = 0; i < n; i++) {

	     double y_g = g(x,y);
       double error = std::fabs(y-y_g);

	     //std::cout << x << "\t" << y << "\t" << y_g << "\t" << error << "\n";

       if (flag) { std::cout << x << "\t" << y << "\t" << y_g << "\t" << error << "\n"; }



         k1 = h * f(x,y);
         k2 = h * f(x + (h / 2.0), y + (k1 / 2.0));
         k3 = h * f(x + (h / 2.0), y + (k2 / 2.0));
         k4 = h * f(x + h, y + k3);

         y = y + (k1 + 2.0 * k2 + 2.0 * k3 + k4) / 6.0;
	       x = x + h;

    }

     return y;

}

void StudyError(double a, double b, double y_a,
                double (*f)(double, double),
                double (*g)(double, double)) {

    std::cout << "\n=== Исследование погрешности ===\n";
    std::cout << "m\t h=10^-m\t N\t\t MaxError\n";
    std::cout << "-------------------------------------------------\n";

    std::vector<int> exponents = {0, 3, 5, 7};  // степени для h = 10^-m

    for (double m : exponents) {
        double h = std::pow(10, -m);
        int n = static_cast<int>((b - a) / h);

        if (n <= 0) n = 1;  // защита от деления на ноль

        double y_approx = RungeKutta4Method(a, b, y_a, n, f, g, false);
        double y_exact = g(b, y_a);
        double error = std::fabs(y_approx - y_exact);

        std::cout << m << "\t " << h << "\t " << n << "\t "
                  << std::scientific << std::setprecision(15) << error << "\n";
    }
}

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

int main() {

    std::cout << std::fixed << std::setprecision(15);
    const double n = 10;

    while (true) {
        int choice;

        std::cout << "\nВыберите уравнение:\n";
        std::cout << "1) y'(x)=3x^2, y(0)=1, решение y=x^3+1\n";
        std::cout << "2) y'(x)=y, y(0)=1, решение y=e^x\n";
        std::cout << "3) y'(x)=e^x, y(0)=1, решение y=e^x\n";
        std::cout << "0) Выход из программы\n";
        std::cout << "Ваш выбор: ";

        choice = getIntInput();

        if (choice == 0) {
            std::cout << "Программа завершена.\n";
            break;
        }

        double a, b, y_a;

        double (*f) (double, double);
        double (*g) (double, double);

        switch (choice) {
                case 1:
                    a = 1.0;
                    b = 10.0;
                    y_a = 1.0;
                    f = f1; g = g1;
                    break;
                case 2:
                    a = 0.0;
                    b = 1.0;
                    y_a = 1.0;
                    f = f2; g = g2;
                    break;
                case 3:
                    a = 0.0;
                    b = 1.0;
                    y_a = 1.0;
                    f = f3; g = g3;
                    break;
                default:
                    std::cerr << "Неверный выбор! Пожалуйста, выберите 0-3.\n";
                    continue;
            }

        // Вывод основного решения
        RungeKutta4Method(a, b, y_a, n, f, g);

        // Исследование погрешности
        StudyError(a, b, y_a, f, g);

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
