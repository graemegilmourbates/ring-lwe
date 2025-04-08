#include "types.h"

Polynomial mod_poly(const Polynomial& a, Modulus q){
  /* Handles positive and negative mods */
  Polynomial a_prime(a.size(), 0);
  int i=0;
  for(const auto& coef : a){
    a_prime[i] = ((coef % q)+q)%q;
    ++i;
  }
  return a_prime;
}

Polynomial add_poly(const Polynomial& a, const Polynomial& b, Modulus q){
  /**/
  int n = std::max(a.size(),b.size());
  Polynomial c(n,0);
  for(int i=0; i<n; ++i){
    if(i<a.size()) c[i] = c[i]+a[i];
    if(i<b.size()) c[i] = c[i]+b[i];
  }
  return mod_poly(c, q);
}

Polynomial subtract_poly(const Polynomial& a, const Polynomial& b, Modulus q){
  /**/
  int n = std::max(a.size(),b.size());
  Polynomial c(n,0);
  for(int i=0; i<n; ++i){
    if(i<a.size()) c[i] = c[i]+a[i];
    if(i<b.size()) c[i] = c[i]-b[i];
  }
  return mod_poly(c, q);
}

Polynomial multiply_poly(const Polynomial& a, const Polynomial& b, Modulus q){
  /**/
  int u = a.size();
  int w = b.size();
  int n = u+w-1;
  Polynomial c(n,0);
  for(int i=0; i<u; ++i){
    for(int j=0; j<w; ++j){
      c[i+j] += a[i]*b[j];
    }
  }
  return mod_poly(c, q);
}

Polynomial cyclic_mod(Polynomial a, Dimension n, Modulus q){
  /**/
  if(a.size() <= n) return mod_poly(a,q);
  // initialize zero polynomial
  Polynomial a_prime(n,0);
  int i=0, l, k;
  for(auto& coef : a){
    l = i%n;
    k = i/n;
    int sign = ((k%2==0) ? 1:-1);
    a_prime[l] = (a_prime[l]+coef*sign)%q;
    ++i;
  }
  return mod_poly(a_prime, q);
}
