#include <iostream>
#include "poly.h"
#include "keygen.h"
#include "encode.h"
#include "homomorphic.h"
#include "utils.h"

int main() {
  Dimension n=8;
  Modulus q=7919;
  std::vector<char> msg={'0','0','1','0','1','1','0','1'};

  Key s = private_key_gen(n,q);
  PublicKey pub = public_key_gen(s,n,q);

  CipherText encoded = encode(pub, msg, n, q);
  Polynomial decoded = decode(s, encoded, n, q);

  std::cout << "Key: < ";
  for(auto& bit : s) std::cout << bit << " ";
  std::cout << ">\n" << std::endl;

  std::cout << "Original: < ";
  for(auto& bit : msg) std::cout << bit << " ";
  std::cout << ">\n" << std::endl;

  std::cout << "Decoded:  < ";
  for(auto& bit : decoded) std::cout << bit << " ";
  std::cout << ">\n" << std::endl;
}
