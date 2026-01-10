#include "polynomial.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

Polynomial::Polynomial() = default;

Polynomial::Polynomial(std::initializer_list<Term> list) : terms(list) {
    normalize(*this);
}

void normalize(Polynomial& p) {

    std::sort(p.terms.begin(), p.terms.end(), [](const Term& a, const Term& b) {
        return a.degree > b.degree;
    });


    std::vector<Term> merged;
    merged.reserve(p.terms.size());

    for (const auto& term: p.terms) {
        if (merged.empty()) {
            merged.push_back(term);
        } else {
            Term& last = merged.back();
            if (last.degree == term.degree) {
                last.coeff += term.coeff;
            } else {
                merged.push_back(term);
            }
        }
    }

    auto new_end = std::remove_if(merged.begin(), merged.end(), [](const Term& t) {
        return t.coeff == 0;
    });
    merged.erase(new_end, merged.end());
    p.terms = std::move(merged);

}

Polynomial operator+(const Polynomial& a, const Polynomial& b) {
    Polynomial p;
    p.terms.insert(p.terms.end(), a.terms.begin(), a.terms.end());
    p.terms.insert(p.terms.end(), b.terms.begin(), b.terms.end());
    normalize(p);
    return p;
}

Polynomial operator-(const Polynomial& a, const Polynomial& b) {
    Polynomial p;
    p.terms.insert(p.terms.end(), a.terms.begin(), a.terms.end());

    for (const auto& term: b.terms) {
        p.terms.push_back({-term.coeff, term.degree});
    }
    normalize(p);
    return p;
}


Polynomial operator*(const Polynomial& a, const Polynomial& b) {
    Polynomial p;

    if (a.terms.empty() || b.terms.empty()) {
        return p;
    }


    for (const auto& t1: a.terms) {
        for (const auto& t2: b.terms) {
            p.terms.push_back({
                t1.coeff * t2.coeff,
                t1.degree + t2.degree
            });
        }
    }

    normalize(p);
    return p;

}


Term lead_term(const Polynomial& p) {
    if (p.terms.empty()) {
        return {0, 0};
    }
    return p.terms[0];
}
void print_polynomial(const Polynomial& p) {
    if (p.terms.empty()) {
        std::cout << "0";
        return;
    }

    bool first = true;
    for (auto it = p.terms.rbegin(); it != p.terms.rend(); ++it) {
        int coef = it->coeff;
        size_t deg = it->degree;

        if (coef == 0) continue;

        if (!first) {
            std::cout << (coef > 0 ? " + " : " - ");
        } else if (coef < 0) {
            std::cout << "-";
        }

        int absolute = std::abs(coef);
        if (absolute != 1 || deg == 0) {
            std::cout << absolute;
        }

        if (deg > 0) {
            std::cout << "x";
            if (deg > 1) {
                std::cout << "^" << deg;
            }
        }

        if (first) first = false;
    }
}