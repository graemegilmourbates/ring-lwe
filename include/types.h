#pragma once
#include <vector>
#include <utility>

// Common types
using Modulus = int;
using Dimension = int;
using Polynomial = std::vector<int>;
using CipherText = std::pair<Polynomial, Polynomial>;
using Key = Polynomial;
using PublicKey = std::pair<Polynomial, Polynomial>;
using BitVector = std::vector<char>;
