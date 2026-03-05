# Learning With Errors

**Author:** Graeme Bates

## Abstract

The goal of this paper is to give readers an intuitive understanding of the Learning With Errors problem (LWE). This paper gives a high-level overview of LWE and the associated hard lattice problems. Although it includes a simple implementation of the Ring-Learning With Errors (Ring-LWE) problem in C++, it is not intended as a comprehensive guide for building secure cryptosystems. Practical system design requires thoughtful choices of error magnitude, sampling distributions, modulus size, and error correction methods — especially when supporting features like Fully Homomorphic Encryption (FHE).

---

## Introduction

The **Learning With Errors** (LWE) problem is a modern cryptographic protocol in lattice-based cryptography. Proposed in 2005 by Oded Regev, LWE and its variants (like Ring-LWE) are the foundation for public key cryptographic schemes believed to be secure against quantum attacks.

---

## Motivation

LWE was developed in response to the threat posed by quantum computers, which can break RSA and discrete log-based systems using Shor's algorithm. In contrast, LWE offers **quantum-safe security**.

Another key feature of LWE-based schemes is support for **Fully Homomorphic Encryption (FHE)**, which enables computation on encrypted data. While powerful, FHE is challenged by ciphertext expansion and error growth — prompting techniques like *bootstrapping* to mitigate these issues.

---

## Lattice Preliminaries

### Lattices

A lattice `L` is a set of all integer linear combinations of a basis:

```
L = { sum(k_i * b_i) : k_i ∈ ℤ,  i = 1..n }
```

Think of this as a regular grid of points formed by vectors in Euclidean space.

### Basis and Complexity

A "good" basis has short, nearly orthogonal vectors, making navigation easy. A "bad" basis (long, nearly parallel vectors) makes problems like the **Closest Vector Problem (CVP)** hard — especially in high dimensions.

### Hard Lattice Problems

**Closest Vector Problem (CVP):** Given a point in ℝⁿ, find the closest lattice point. With a bad basis, CVP is NP-hard.

**Bounded Distance Decoding (BDD):** A restricted form of CVP where the target point is guaranteed to be close to the lattice. LWE is provably hard via reduction to BDD.

### NTRU Cryptosystem

NTRU is a public key cryptosystem built using polynomial rings. Ring-LWE adapts many of its ideas, combining efficiency with provable security. See [Appendix A](#appendix-a-ntru-protocol) for details.

---

## Learning With Errors (LWE)

LWE is essentially the problem of solving noisy systems of linear equations mod `q`, where `q` is a large prime.

### Key Generation

- Choose a secret vector `s ∈ ℤ_q^n`
- Choose a random matrix `A ∈ ℤ_q^(m×n)`
- Sample a small noise vector `e ∈ ℤ^m`
- Compute the public key: `y = A·s + e`

| Key | Value |
|-----|-------|
| Public key | `(A, y)` |
| Private key | `s` |

### Encoding

To send bit `p_i`:
1. Randomly select and sum rows of `A` and the corresponding entries of `y`
2. If `p_i = 0`, send the sum as-is
3. If `p_i = 1`, add `⌊q/2⌉` to the result

This hides the message within noisy sums.

### Decoding

Alice computes `w = B·s`, then derives `d_i = c_i - w_i mod q`:

- If `d_i ≈ 0` → `p_i = 0`
- If `d_i ≈ q/2` → `p_i = 1`

The small noise guarantees reliable recovery.

### Drawbacks

- **Inefficient** for practical use — requires many operations
- Stores `n + 1` integers per bit of plaintext

---

## Ring-LWE

To improve efficiency, Ring-LWE operates over the polynomial ring `ℤ_q[x] / (x^n + 1)`:

- Keys and messages are represented as polynomials
- Each message bit `b_i` is encoded as `0` or `q/2` in a polynomial coefficient
- Encryption produces two ciphertexts:
  - `c₁(x) = a(x)·r(x) + e₁(x)`
  - `c₂(x) = b(x)·r(x) + e₂(x) + m(x)`

Decryption recovers the message via:

```
m(x) + noise = c₂(x) - s(x)·c₁(x)
```

### Advantages

- **Compact:** one message maps to one polynomial
- **Fast:** supports efficient polynomial arithmetic (e.g., NTT)
- **Secure:** Ring-LWE hardness reduces to approximate-SIVP

Ring-LWE underlies **Kyber**, a NIST post-quantum finalist.

---

## References

- Regev, O. (2005). *On Lattices, Learning with Errors, Random Linear Codes, and Cryptography*
- Peikert, C. (2016). *A Decade of Lattice-Based Cryptography*
- Lyubashevsky et al. (2013). *On Ideal Lattices and Learning with Errors over Rings*
- Regev, O. (2010). *The Learning with Errors Problem (Survey)*
- Harrigan, S. (2020). *Lattice-Based Cryptography and LWE*

---

## Appendix A: NTRU Protocol

### Key Generation

- Work in the polynomial ring `ℤ[X] / (X^n ± 1)`
- Choose large odd modulus `q`
- Generate polynomials `f` and `g` with coefficients in `{-1, 0, 1}`
- Ensure `f` is invertible mod `p` and mod `q`
- Compute public key: `h = p · f_q · g mod q`

| Key | Value |
|-----|-------|
| Public key | `h` |
| Private key | `f`, `f_q`, `g` |

### Encryption

Messages are converted to polynomials, then encrypted and decrypted using ring arithmetic in `R_q`.

---

## Appendix B: Ring-LWE Sampling Methods

| Method | Description |
|--------|-------------|
| Bounded discrete Gaussian | Samples small errors from a Gaussian distribution |
| Uniform | Samples uniformly from `ℤ_q` |
| Ternary | Samples from `{-1, 0, 1}` |
| Noise scaling | Sets standard deviation `σ = √q / 2` |
