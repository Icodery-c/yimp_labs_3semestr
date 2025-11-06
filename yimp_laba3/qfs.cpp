#include <iostream>
#include <cmath>
#include "qfs.h"

/// quadrature formulas
double qf_rectangle_left_point(double a, double b, double (*f)(double)) { return (b - a) * f(a); }
double qf_rectangle_middle_point(double a, double b, double (*f)(double)) { return (b - a) * f((a + b) / 2.0); }
double qf_trapezoid(double a, double b, double (*f)(double)) { return ((b - a) / 2.0) * (f(a) + f(b)); }
double qf_simpson(double a, double b, double (*f)(double)) { return ((b - a) / 6.0) * (f(a) + 4.0 * f((a + b) / 2.0) + f(b)); }
double qf_3nodes_gauss(double a, double b, double (*f)(double)) {
    double right_term = ((b - a) / 2.0) * sqrt(3.0 / 5.0);
    double x0 = (a + b) / 2.0;
    double x_m = x0 - right_term;
    double x_p = x0 + right_term;
    return ((b - a) / 18.0) * (5.0 * f(x_m) + 8.0 * f(x0) + 5.0 * f(x_p));
}

/// mapping
std::string qf_names[5] = {
    "Left rectangle point formula",
    "Middle rectangle point formula",
    "Trapezoid formula",
    "Simpson formula",
    "Three-nodes Gauss formula",
};

double (*qf_array[5])(double, double, double (*)(double)) = {
    qf_rectangle_left_point,
    qf_rectangle_middle_point,
    qf_trapezoid,
    qf_simpson,
    qf_3nodes_gauss
};
