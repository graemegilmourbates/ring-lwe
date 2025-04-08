#pragma once
#include "types.h"
#include "poly.h" 

CipherText homomorphic_add(const CipherText&, const CipherText&, Dimension, Modulus);
CipherText homomorphic_mult(const CipherText&, const CipherText&, Dimension, Modulus);
CipherText homomorphic_scalar_mult(const CipherText&, Polynomial, Dimension, Modulus);
