#include <iostream>
#include <iomanip>
#include <cmath>
#include "qfs.h"

double cos1000_f(double x) { return cos(1000.0 * x); }
double cos1000_exact(double a, double b) { return (sin(1000.0 * b) - sin(1000.0 * a)) / 1000.0; }

double exp1000_f(double x) { return exp(-1000.0 * x); }
double exp1000_exact(double a, double b) { return (exp(-1000.0 * a) - exp(-1000.0 * b)) / 1000.0; }

double tabular_f(double x) { return 1.0 / sqrt(1.0 - x * x); }
double tabular_exact(double a, double b) { return asin(b) - asin(a); }


void qf_integral(
    double a, double b, double (*f)(double), int N,
    double (*qf)(double, double, double (*)(double)),
    double (*exact_f)(double, double),
    std::string& qf_name
) {

    double a_k, b_k;
    double h = (b - a) / N;

    double approx = 0.0;
    double exact = exact_f(a,b);
    
    double abs_error;

    for (int k = 0; k < N; ++k) {
        a_k = a + k * h;
        b_k = a_k + h;
        approx += qf(a_k, b_k, f);
    }

    abs_error = fabs(exact - approx);

    std::cout << std::fixed << std::setprecision(8) 
        << "\n--- " << qf_name << " ---\n"
        << "Approx: " << approx << "\n"
        << "Exact : " << exact << "\n"
        << "Abs err: " << abs_error << "\n";
}

void defineF2(char fNum, double (**f)(double), double (**exact_f)(double, double)) {
    switch (fNum) {
    case '2': { *f = exp1000_f; *exact_f = exp1000_exact; break; }
    case '3': { *f = tabular_f; *exact_f = tabular_exact; break; }
    default: { *f = cos1000_f; *exact_f = cos1000_exact; break; }
    }
}

void compareQuadraturesN(double a, double b, int N, char fNum) {
    double (*f)(double);
    double (*exact_f)(double, double);
    defineF2(fNum, &f, &exact_f);

    std::cout << "Iterations: " << N << "\n";
    for (int i = 0; i < 5; ++i) {
        qf_integral(a, b, f, N, qf_array[i], exact_f, qf_names[i]);
    }
    
}
