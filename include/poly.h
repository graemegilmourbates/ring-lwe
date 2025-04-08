#pragma once
#include "types.h"

Polynomial mod_poly(const Polynomial&, Modulus);
Polynomial add_poly(const Polynomial&, const Polynomial&, Modulus);
Polynomial multiply_poly(const Polynomial&, const Polynomial&, Modulus);
Polynomial cyclic_mod(Polynomial, Dimension, Modulus);
Polynomial subtract_poly(const Polynomial&, const Polynomial&, Modulus);
