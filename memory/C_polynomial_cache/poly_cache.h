#ifndef POLYNOMIAL_CACHE_H
#define POLYNOMIAL_CACHE_H

#include "polynomial.h"
#include <memory>
#include <stdexcept>
#include <vector>

class PolynomialCache {
private:
  std::vector<std::unique_ptr<Polynomial>> polynomials;
  size_t max_size;

public:
  explicit PolynomialCache(size_t size) : max_size(size) {
    if (size == 0) {
      throw std::invalid_argument("Cache size must be > 0");
    }
  }

  PolynomialCache(const PolynomialCache &) = delete;
  PolynomialCache &operator=(const PolynomialCache &) = delete;

  void add(Polynomial &&p) {
    if (polynomials.size() >= max_size) {
      polynomials.erase(polynomials.begin());
    }
    polynomials.push_back(std::make_unique<Polynomial>(std::move(p)));
  }

  size_t size() const { return polynomials.size(); }

  size_t capacity() const { return max_size; }

  const Polynomial &at(size_t i) const {
    if (i >= polynomials.size()) {
      throw std::out_of_range("PolynomialCache index out of range");
    }
    return *polynomials[i];
  }

  void clear() { polynomials.clear(); }
  auto begin() const { return polynomials.begin(); };

  auto end() const { return polynomials.end(); };
};
#endif
