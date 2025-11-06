#pragma once
#include <cmath>
#include <string>

/// quadrature formulas
double qf_rectangle_left_point(double, double, double (*)(double));
double qf_rectangle_middle_point(double, double, double (*)(double));
double qf_trapezoid(double, double, double (*)(double));
double qf_simpson(double, double, double (*)(double));
double qf_3nodes_gauss(double, double, double (*)(double));

/// maps
extern std::string qf_names[5];
extern double (*qf_array[5])(double, double, double (*)(double));
