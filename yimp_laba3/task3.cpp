#include <iostream>
#include <iomanip>
#include <cmath>


double sincos_f(double x, unsigned m, unsigned n) { return sin(double(m) * x) * cos(double(n) * x); }
double sinsin_f(double x, unsigned m, unsigned n) { return sin(double(m) * x) * sin(double(n) * x); }
double coscos_f(double x, unsigned m, unsigned n) { return cos(double(m) * x) * cos(double(n) * x); }


double qf_3nodes_gauss_mn(double a, double b, unsigned m, unsigned n, double (*f)(double, unsigned, unsigned)) {
    double right_term = ((b - a) / 2.0) * sqrt(3.0 / 5.0);
    double x0 = (a + b) / 2.0;
    double x_m = x0 - right_term;
    double x_p = x0 + right_term;
    return ((b - a) / 18.0) * (5.0 * f(x_m, m, n) + 8.0 * f(x0, m, n) + 5.0 * f(x_p, m, n));
}


double qf_integral(
    double a, double b,
    unsigned m, unsigned n,
    double (*f)(double, unsigned, unsigned),
    int N
) {
    double a_k, b_k;
    double h = (b - a) / double(N);
    double approx = 0.0;

    for (int k = 0; k < N; ++k) {
        a_k = a + k * h;
        b_k = a_k + h;
        approx += qf_3nodes_gauss_mn(a_k, b_k, m, n, f);
    }

    return approx;
}

void calcIntegrals(int N) {
    constexpr double PI = 3.1415926535897931;

    unsigned tests[3][2] = { {1, 2}, {3, 3}, {0, 0} };

    std::cout << "\n--- Three-nodes Gauss formula ---\n";
    std::cout << std::fixed << std::setprecision(8);

    std::cout << "Integral [-pi, pi] sin(mx)cos(nx)\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "m=" << tests[i][0] << ", n=" << tests[i][1] << ", res=" << qf_integral(-PI, PI, tests[i][0], tests[i][1], sincos_f, N) << "\n";
    }

    std::cout << "\nIntegral [-pi, pi] sin(mx)sin(nx)\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "m=" << tests[i][0] << ", n=" << tests[i][1] << ", res=" << qf_integral(-PI, PI, tests[i][0], tests[i][1], sinsin_f, N) << "\n";
    }

    std::cout << "\nIntegral [-pi, pi] cos(mx)cos(nx)\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "m=" << tests[i][0] << ", n=" << tests[i][1] << ", res=" << qf_integral(-PI, PI, tests[i][0], tests[i][1], coscos_f, N) << "\n";
    }
}