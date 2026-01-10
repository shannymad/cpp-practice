#pragma once
#include <vector>
#include <initializer_list> 


struct Term {
    int coeff;
    size_t degree;
};

struct Polynomial {
    std::vector<Term> terms;


    Polynomial();
    Polynomial(std::initializer_list<Term> list);
    
    Polynomial(const Polynomial&) = delete;
    Polynomial& operator=(const Polynomial&) = delete;

    Polynomial(Polynomial&& other) noexcept = default;
    Polynomial& operator=(Polynomial&& other) noexcept = default;
};

void normalize(Polynomial& p);
Polynomial operator+(const Polynomial& a, const Polynomial& b);
Polynomial operator-(const Polynomial& a, const Polynomial& b);
Polynomial operator*(const Polynomial& a, const Polynomial& b);

Term lead_term(const Polynomial& p);
void print_polynomial(const Polynomial& p);
