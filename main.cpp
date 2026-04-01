#include <iostream>
#include "poly.h"
#include "keygen.h"
#include "encode.h"
#include "homomorphic.h"
#include "utils.h"

int main() {
  Dimension n = 256;
  Modulus   q = 7681;

  BitVector msg = {1,0,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1,1,1,1,0,0,0,1};

  Key s        = private_key_gen(n, q);
  PublicKey pub = public_key_gen(s, n, q);

  CipherText encoded = encode(pub, msg, n, q);
  Polynomial decoded = decode(s, encoded, n, q);

  std::cout << "Original: ";
  for(auto b : msg)     std::cout << (int)b;
  std::cout << "\nDecoded:  ";
  for(size_t i = 0; i < msg.size(); ++i) std::cout << (int)decoded[i];
  std::cout << "\n\nMatch: " << (msg == BitVector(decoded.begin(), decoded.begin() + msg.size()) ? "PASS" : "FAIL") << "\n";
}
