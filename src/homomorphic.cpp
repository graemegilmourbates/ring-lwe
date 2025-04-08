#include "types.h"
#include "poly.h" 

CipherText homomorphic_add(
  const CipherText& c1, const CipherText& c2, Dimension n, Modulus q
){
  /**/
  Polynomial c1_1 = std::get<0>(c1);
  Polynomial c1_2 = std::get<1>(c1);
  Polynomial c2_1 = std::get<0>(c2);
  Polynomial c2_2 = std::get<1>(c2);

  Polynomial res1 = add_poly(c1_1, c2_1, q);
  Polynomial res2 = add_poly(c1_2, c2_2, q);
  res1 = cyclic_mod(res1, n, q);
  res2 = cyclic_mod(res2, n, q);

  return std::make_tuple(res1, res2);
}

CipherText homomorphic_mult(
  CipherText c1, CipherText c2, Dimension n, Modulus q
){
  /**/
  Polynomial c1_1 = std::get<0>(c1);
  Polynomial c1_2 = std::get<1>(c1);
  Polynomial c2_1 = std::get<0>(c2);
  Polynomial c2_2 = std::get<1>(c2);

  Polynomial res1 = multiply_poly(c1_1, c2_1, q);
  Polynomial res2 = multiply_poly(c1_2, c2_2, q);
  res1 = cyclic_mod(res1, n, q);
  res2 = cyclic_mod(res2, n, q);

  return std::make_tuple(res1, res2);
}

CipherText homomorphic_scalar_mult(
  CipherText c, Polynomial p, Dimension n, Modulus q
){
  /**/
  Polynomial c1_1 = std::get<0>(c);
  Polynomial c1_2 = std::get<1>(c);

  Polynomial res1 = multiply_poly(c1_1, p, q);
  Polynomial res2 = multiply_poly(c1_2, p, q);
  res1 = cyclic_mod(res1, n, q);
  res2 = cyclic_mod(res2, n, q);

  return std::make_tuple(res1, res2);
}
