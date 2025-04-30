# Learning With Errors  
**Author:** Graeme Bates  

## Abstract  
The goal of this paper is to give readers an intuitive understanding of the Learning With Errors problem (LWE). This paper gives a high-level overview of the LWE and the associated hard lattice problems. Although it includes a simple implementation of the Ring-Learning With Errors (Ring-LWE) problem in C++, it is not intended as a comprehensive guide for building secure cryptosystems. Practical system design requires thoughtful choices of error magnitude, sampling distributions, modulus size, and error correction methods — especially when supporting features like Fully Homomorphic Encryption (FHE).

---

## Introduction  
The **Learning With Errors** (LWE) problem is a modern cryptographic protocol in lattice-based cryptography. Proposed in 2005 by Oded Regev, LWE and its variants (like Ring-LWE) are the foundation for public key cryptographic schemes believed to be secure against quantum attacks.

---

## Motivation  
LWE was developed in response to the threat posed by quantum computers, which can break RSA and discrete log-based systems using quantum algorithms. In contrast, LWE offers **quantum-safe security**.

Another key feature of LWE-based schemes is support for **Fully Homomorphic Encryption (FHE)**, which enables computation on encrypted data. While powerful, FHE is challenged by ciphertext expansion and error growth — prompting techniques like *bootstrapping* to mitigate these issues.

---

## Lattice Preliminaries  

### Lattices  
A lattice \(\mathcal{L}\) is a set of all integer linear combinations of a basis:  
\[
\mathcal{L} = \left\{ \sum_{i=1}^n k_i \mathbf{b}_i : k_i \in \mathbb{Z} \right\}
\]

Think of this as a grid formed by vectors in Euclidean space.

### Basis and Complexity  
A “good” basis has short, nearly orthogonal vectors, making navigation easy. A “bad” basis (long, nearly parallel vectors) makes problems like **Closest Vector Problem (CVP)** hard — especially in high dimensions.

### Hard Lattice Problems  

- **Closest Vector Problem (CVP):** Given a point in \(\mathbb{R}^n\), find the closest lattice point. With a bad basis, CVP is NP-hard.
- **Bounded Distance Decoding (BDD):** A restricted form of CVP where the point is guaranteed to be close to the lattice. LWE is provably hard via reduction to BDD.

### NTRU Cryptosystem  
NTRU is a public key cryptosystem built using polynomial rings. Ring-LWE adapts many of its ideas, combining efficiency with provable security.

---

## Learning With Errors (LWE)  

LWE is essentially solving noisy systems of linear equations mod \(q\), where \(q\) is a large prime.

### Key Generation  

- Choose secret vector \(\mathbf{s} \in \mathbb{Z}_q^n\)  
- Choose random matrix \(A \in \mathbb{Z}_q^{m \times n}\)  
- Add small noise vector \(\mathbf{e} \in \mathbb{Z}^m\)  
- Compute public key: \(\mathbf{y} = A\mathbf{s} + \mathbf{e}\)

**Public key:** \((A, \mathbf{y})\)  
**Private key:** \(\mathbf{s}\)

### Encoding  

To send bit \(p_i\):
- Randomly sum rows of \(A\) and corresponding values in \(\mathbf{y}\)
- If \(p_i = 0\), send sum as is  
- If \(p_i = 1\), add \(\lfloor q/2 \rceil\) to the result

This hides the message in noisy sums.

### Decoding  

Alice computes:  
\[
\mathbf{B} \cdot \mathbf{s} = \mathbf{w}
\]  
Then she computes \(d_i = c_i - w_i \mod q\):

- If \(d_i \approx 0\), \(p_i = 0\)  
- If \(d_i \approx q/2\), \(p_i = 1\)

Small noise ensures recovery is reliable.

### Drawbacks  

- **Inefficient** for practical use  
- Requires many operations and stores \(n + 1\) integers per bit  

---

## Ring-LWE  

To improve efficiency, Ring-LWE uses a polynomial ring \(\mathbb{Z}_q[x]/(x^n + 1)\):

- Keys and messages are polynomials  
- Message bit \(b_i\) is encoded as \(0\) or \(q/2\) in a polynomial  
- Encryption uses:
  - \(c_1(x) = a(x)r(x) + e_1(x)\)  
  - \(c_2(x) = b(x)r(x) + e_2(x) + m(x)\)  

Decryption is:
\[
m(x) + \text{noise} = c_2(x) - s(x)c_1(x)
\]

### Advantages  

- Compact: one message = one polynomial  
- Fast: uses efficient polynomial arithmetic (e.g., NTT)  
- Secure: Ring-LWE is as hard as approximate-SIVP  

**Used in:** Kyber (NIST post-quantum finalist)

---

## References  

- Regev, O. (2005). *On Lattices, Learning with Errors...*  
- Peikert, C. (2016). *A Decade of Lattice-Based Cryptography*  
- Lyubashevsky et al. (2013). *On Ideal Lattices and LWE over Rings*  
- Regev, O. (2010). *The Learning with Errors Problem (Survey)*  
- Harrigan, S. (2020). *Lattice-Based Cryptography and LWE*

---

## Appendix A: NTRU Protocol  

### Key Generation  

- Polynomial ring: \(\mathbb{Z}[X]/(X^n \pm 1)\)  
- Modulus \(q\): large odd number  
- Generate \(\mathbf{f}, \mathbf{g}\) with coefficients in \(\{-1,0,1\}\)  
- Ensure \(\mathbf{f}\) has inverse mod \(p\) and \(q\)  
- Compute public key: \(\mathbf{h} = p \mathbf{f}_q \cdot \mathbf{g} \mod q\)

**Private key:** \(\mathbf{f}, \mathbf{f}_q, \mathbf{g}\)

### Encryption  

- Convert message to polynomial  
- Encrypt and decrypt using arithmetic in the ring \(R_q\)

---

## Appendix B: Ring-LWE Sampling Methods  

**Sampling functions include:**
- Bounded discrete Gaussian  
- Uniform sampling from \(\mathbb{Z}_q\)  
- Ternary sampling from \(\{-1, 0, 1\}\)  
- Noise scaling via standard deviation \(\sigma = \sqrt{q}/2\)
