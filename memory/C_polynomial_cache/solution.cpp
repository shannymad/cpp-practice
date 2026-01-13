#include "poly_cache.h"
#include "polynomial.h"
#include <iostream>

int main() {
  PolynomialCache cache(2);

  for (int i = 0; i < 5; ++i) {
    Polynomial p(
        {{i + 1, static_cast<size_t>(i + 2)}}); // (i + 1) * x ^ (i + 2)
    cache.add(std::move(p));
    std::cout << "Added poly " << i + 1 << ", cache size: " << cache.size()
              << "\n";
  }

  std::cout << "\nFinal cache content\n";
  for (size_t i = 0; i < cache.size(); ++i) {
    const auto &poly = cache.at(i);
    const auto &lt = poly.leading_term();
    std::cout << "  Poly[" << i << "]: " << lt.coeff << "x^" << lt.degree
              << "\n";
  }
  return 0;
}
