#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "term.h"
#include <stdexcept>
#include <vector>

class Polynomial {
private:
  std::vector<Term> terms;

public:
  Polynomial() = default;

  Polynomial(std::vector<Term> &&terms) : terms(std::move(terms)) {}

  Polynomial(const Polynomial &) = delete;
  Polynomial &operator=(const Polynomial &) = delete;

  Polynomial(Polynomial &&) noexcept = default;
  Polynomial &operator=(Polynomial &&) noexcept = default;

  size_t size() const { return terms.size(); }

  bool is_zero() const { return terms.empty(); }
  const Term &leading_term() const {
    if (terms.empty()) {
      throw std::logic_error("Zero polynomial has no leading term");
    }
    return terms.front();
  }
  const std::vector<Term> &get_terms() const { return terms; }

  auto begin() const { return terms.begin(); };
  auto end() const { return terms.end(); };
};
#endif