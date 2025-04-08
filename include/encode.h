#pragma once
#include "types.h"
#include "poly.h"
#include "sampling.h"
#include <cmath>

CipherText encode(const PublicKey&, const std::vector<char>&, Dimension, Modulus);
Polynomial decode(const Key&, const CipherText&, Dimension, Modulus);
Polynomial filter_noise(const Polynomial&, Modulus);
