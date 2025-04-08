#pragma once
#include "types.h"
#include "poly.h"
#include "sampling.h"

Key private_key_gen(Dimension, Modulus);
PublicKey public_key_gen(Key, Dimension, Modulus);
