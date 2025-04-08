#include "types.h"
#include "poly.h"
#include "sampling.h"
#include <cmath>

CipherText encode(
  const PublicKey& p, const BitVector& msg, Dimension n, Modulus q
){
  /*
    b=b1,b2,b3,...bl bi in {0,1} (ie bit vector)
    m(x) = <m1 m2 m3 ... ml > mi=0 if bi=0 mi=q/2 if bi=1

    r(x) is small random vector
    c1(x) = a(x)*r(x)+e1(x)
    c2(x) = b(x)*r(x)+e2(x)+m(x)

    return (c1,c2)
  */
  Polynomial m(n,0);
  int i=0;
  // populate message polynomial... may want to add check that b.size()<n
  for(auto& bit : msg){
    if(bit=='1')m[i]=(q/2)+1;
    ++i;
  }
  double sigma = compute_sigma(n, q);
  // Get random small vectors
  Polynomial r = sample_ternary(n);
  Polynomial e1 = gaussian_error(n, sigma, q);
  Polynomial e2 = gaussian_error(n, sigma, q);
  Polynomial a, b, c1, c2;
  a = std::get<0>(p);
  b = std::get<1>(p);

  c1 = multiply_poly(a, r, q);
  c1 = add_poly(c1, e1, q);

  c2 = multiply_poly(b, r, q);
  c2 = add_poly(c2,e2,q);
  c2 = add_poly(c2,m,q);

  c1 = cyclic_mod(c1, n, q);
  c2 = cyclic_mod(c2, n, q);

  return std::make_tuple(c1, c2);
}

Polynomial filter_noise(const Polynomial& m, Modulus q) {
  Polynomial clean(m.size(), 0);
  for (size_t i = 0; i < m.size(); ++i) {
    Modulus noisy = m[i] % q;
    clean[i] = (noisy >= q/4 && noisy <= 3*q/4) ? 1 : 0;
  }
  return clean;
}

Polynomial decode(const Key& s, const CipherText& c, Dimension n, Modulus q){
  /*
    c2(x)-s(x)c1(x)=m(x)+noise
  */
  Polynomial c1,c2,m;

  c1 = std::get<0>(c);
  c2 = std::get<1>(c);
  c1 = multiply_poly(c1, s, q);
  m = subtract_poly(c2, c1, q);
  m = cyclic_mod(m,n,q);
  m = filter_noise(m, q);
  return m;
}
