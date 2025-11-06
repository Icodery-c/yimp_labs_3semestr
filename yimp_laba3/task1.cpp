#include <iostream>
#include <iomanip>
#include <cmath>
#include "qfs.h"


double sin_f(double x) { return sin(x); }
double sin_exact(double a, double b) { return cos(a) - cos(b); }
double sin_deriv1(double x) { return cos(x); }
double sin_deriv2(double x) { return -sin(x); }
double sin_deriv4(double x) { return sin(x); }
double sin_deriv6(double x) { return -sin(x); }
double (*sin_derivs[])(double) = { sin_deriv1, sin_deriv2, sin_deriv4, sin_deriv6 };

double exp_f(double x) { return exp(x); }
double exp_exact(double a, double b) { return exp(b) - exp(a); }
//double exp_deriv1(double x) { return exp(x); }
//double exp_deriv2(double x) { return exp(x); }
//double exp_deriv4(double x) { return exp(x); }
//double exp_deriv6(double x) { return exp(x); }
//double (*exp_derivs[])(double) = { exp_deriv1, exp_deriv2, exp_deriv4, exp_deriv6 };

double pow6_f(double x) { return pow(x, 6.0); }
//double pow6_exact(double a, double b) { return pow(b, 7.0) / 7.0 - pow(a, 7.0) / 7.0; }
//double pow6_deriv1(double x) { return 6.0 * pow(x, 5.0); }
//double pow6_deriv2(double x) { return 6.0 * 5.0 * pow(x, 4.0); }
//double pow6_deriv4(double x) { return 6.0 * 5.0 * 4.0 * 3.0 * pow(x, 2.0); }
//double pow6_deriv6(double x) { return 6.0 * 5.0 * 4.0 * 3.0 * 2.0 * 1.0 * pow(x, 0.0); }
//double (*pow6_derivs[])(double) = { pow6_deriv1, pow6_deriv2, pow6_deriv4, pow6_deriv6 };

/// custom functions
double poly_f(double x) { return x * x * x * x + 3.0 * x * x - 2.0 * x + 1.0; }
double poly_def(double x) { return (x * x * x * x * x) / 5.0 + x * x * x - x * x + x; }
double poly_exact(double a, double b) { return poly_def(b) - poly_def(a); }


void qf_integral(
    double a, double b, double (*f)(double),
    double (*qf)(double, double, double (*f)(double)),
    double (*exact_f)(double, double),
    std::string& qf_name,
    int max_iters = 20
) {
    int N0 = 1;
    double h;
    
    double approx = 0.0;
    double exact = exact_f(a, b);

    double abs_error = 0.0;
    double a_k, b_k;
    double eps = 1e-4;

    while (max_iters) {
        h = (b - a) / double(N0);
        approx = 0.0;

        for (int k = 0; k < N0; ++k) {
            a_k = a + k * h;
            b_k = a_k + h;
            approx += qf(a_k, b_k, f);
        }

        abs_error = fabs(exact - approx);

        if (abs_error <= eps) {
            break;
        }

        N0 *= 2;
        max_iters--;
    }

    if (max_iters <= 0) std::cout << "Calculation limit has been reached.\n";

    std::cout << std::fixed << std::setprecision(8) 
        << "\n--- " << qf_name << " ---\n"
        << "Slits: " << N0 << "\n"
        << "Approx: " << approx << "\n"
        << "Exact: " << exact << "\n"
        << "Abs err: " << abs_error << "\n"
        << "Epsilon: " << eps << "\n";
}

void defineF(char fNum, double (**f)(double), double (**exact_f)(double, double)) {
    switch (fNum) {
    case '2': { *f = exp_f; *exact_f = exp_exact; break; }
    case '3': { *f = poly_f; *exact_f = poly_exact; break; }
    default: { *f = sin_f; *exact_f = sin_exact; break; }
    }
}

void compareQuadratures(double a, double b, char fNum) {
    double (*f)(double);
    double (*exact_f)(double, double);
    defineF(fNum, &f, &exact_f);
    
    for (int i = 0; i < 5; ++i) {
        qf_integral(a, b, f, qf_array[i], exact_f, qf_names[i]);
    }
}