# Ring-LWE

A C++ implementation of the Ring Learning With Errors (Ring-LWE) encryption scheme — a post-quantum public key cryptosystem based on hard lattice problems.

> **Note:** This is an educational implementation. It is not hardened for production use. See the accompanying [writeup](LWE.pdf) for background on the theory.

---

## Overview

Ring-LWE is a variant of the Learning With Errors problem that operates over the polynomial ring `ℤ_q[x] / (xⁿ + 1)`. It achieves the security of lattice-based cryptography with the efficiency of polynomial arithmetic, and underlies NIST post-quantum standards like Kyber.

This implementation supports:
- Key generation (private and public)
- Bit-vector encryption and decryption
- Basic homomorphic operations

Default parameters: `n = 256`, `q = 7681`.

---

## Structure

```
ring-lwe/
├── include/
│   ├── poly.h          # Polynomial type and arithmetic mod q
│   ├── keygen.h        # Private and public key generation
│   ├── encode.h        # Encryption / decryption
│   ├── homomorphic.h   # Homomorphic operations on ciphertexts
│   └── utils.h         # Sampling and utility functions
├── src/                # Implementations
├── main.cpp            # Demo: encrypt and decrypt a bit vector
├── CMakeLists.txt
└── Makefile
```

---

## Build

**With Make:**
```bash
make
./ring-lwe
```

**With CMake:**
```bash
mkdir build && cd build
cmake ..
make
./ring-lwe
```

---

## Usage

`main.cpp` demonstrates a full encrypt/decrypt round-trip:

```cpp
Dimension n = 256;
Modulus q = 7681;
BitVector msg = {1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1,1,1,1,0,0,0,1};

Key s          = private_key_gen(n, q);
PublicKey pub  = public_key_gen(s, n, q);
CipherText ct  = encode(pub, msg, n, q);
Polynomial pt  = decode(s, ct, n, q);
```

Expected output:
```
Original: 101101001100101011110001
Decoded:  101101001100101011110001

Match: PASS
```

---

## How It Works

Key generation samples a secret polynomial `s(x)` with small coefficients. The public key is a pair `(a(x), b(x))` where `b(x) = a(x)·s(x) + e(x)` for a small noise polynomial `e(x)`, all computed mod `(xⁿ + 1, q)`.

Encryption encodes each message bit as a coefficient — `0` or `⌊q/2⌋` — then masks it with fresh noise drawn from the public key. Decryption recovers the message by canceling the secret and rounding: values close to `0` decode as `0`, values close to `q/2` decode as `1`.

Security rests on the hardness of distinguishing `(a, a·s + e)` from a uniform pair — believed to be intractable even for quantum adversaries.

For a more detailed treatment of the underlying mathematics, see [LWE.pdf](LWE.pdf).

---

## References

- Regev, O. (2005). *On Lattices, Learning with Errors, Random Linear Codes, and Cryptography*
- Lyubashevsky et al. (2013). *On Ideal Lattices and Learning with Errors over Rings*
- Peikert, C. (2016). *A Decade of Lattice-Based Cryptography*
