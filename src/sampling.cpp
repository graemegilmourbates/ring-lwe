#include "types.h"
#include <cmath>
#include <random>

// Sample from a bounded discrete Gaussian (centered at 0, std_dev )
int sample_gaussian(std::mt19937& rng, double sigma, int bound) {
    std::normal_distribution<double> gaussian(0.0, sigma);
    while (true) {
        double val = gaussian(rng);
        int rounded = static_cast<int>(std::round(val));
        // Reject if outside bounds or with negligible probability
        if (std::abs(rounded) <= bound) {
            return rounded;
        }
    }
}

Polynomial gaussian_error(int n, double sigma, int q) {
    std::random_device rd;
    std::mt19937 rng(rd());
    Polynomial error_poly;
    int bound = std::min(static_cast<int>(6 * sigma), q / 2);

    for (int i = 0; i < n; ++i) {
        int coeff = sample_gaussian(rng, sigma, bound);
        coeff = (coeff % q + q) % q;
        error_poly.push_back(coeff);
    }
    return error_poly;
}

Polynomial uniform_poly_sample(Dimension n, Modulus q){
  /**/
  Polynomial p;
  std::random_device rand; // seed
  std::mt19937 rnd(rand()); // twister seed eng with seeded rand()
  std::uniform_int_distribution<> distrib(0,q-1);
  for(int i=0; i<n; ++i){
    // add uninformly at random unsigned int from [1,q]
    p.push_back(distrib(rnd));
  }
  return p;
}

Polynomial sample_ternary(Dimension n){
  Polynomial p;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(-1, 1);
  for(int i = 0; i < n; ++i){
    p.push_back(distrib(gen));
  }
  return p;
}

double compute_sigma(Dimension n, Modulus q, double bound, double margin){
    //return q / (tail_bound * noise_margin * std::sqrt(n));
    return std::sqrt(q)/2;
}
