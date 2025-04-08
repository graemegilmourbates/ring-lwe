#pragma once
#include "types.h"
#include <cmath>
#include <random>

int sample_gaussian(std::mt19937&, double, int);
Polynomial uniform_poly_sample(Dimension, Modulus);
Polynomial gaussian_error(int, double, int);
Polynomial sample_ternary(Dimension);
double compute_sigma(Dimension, Modulus, double = 3, double = 8);
