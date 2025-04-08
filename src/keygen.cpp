#include "types.h"
#include "poly.h"
#include "sampling.h"

Key private_key_gen(Dimension n, Modulus q){
  /*
    our secret key s(x) is an element of the quotient ring Z_q[x]/(x^n+1)
    ie, has degree at most n-1
  */
  // return sample_ternary(n);
  // small vector key, small ~ sqrt(q)/8
  return uniform_poly_sample(n,std::sqrt(q)/8);
}

PublicKey public_key_gen(Key s, Dimension n, Modulus q){
  /*
    a(x) is a random polynomial in the quotient ring.
    b(x) = a(x)*s(x)+e(x) mod q
  */
  Polynomial a = uniform_poly_sample(n, q);
  Polynomial b = multiply_poly(a, s, q);
  double sigma = compute_sigma(n, q);
  Polynomial e = gaussian_error(n, sigma, q);
  b = add_poly(b, e, q);
  b = cyclic_mod(b, n, q);
  return std::make_tuple(a,b);
}
