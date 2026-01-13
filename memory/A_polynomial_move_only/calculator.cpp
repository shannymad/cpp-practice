#include <iostream>
#include "polynomial.h"
#include <cassert>

Polynomial read_poly() {
    Polynomial p;
    std::cout << "How many terms in polynomial? ";
    size_t n;
    std::cin >> n;

    if (n <= 0) {
        return p;
    }

    for (size_t i = 0; i < n; ++i) {
        int coeff;
        size_t degree;
        std::cout << "Term " << i + 1 << ": enter coefficient and degree: ";
        std::cin >> coeff >> degree;
        p.terms.push_back({coeff, degree});
    }

    normalize(p);
    return p;
}

int main() {
    std::cout << "=== Running tests ===\n";

    // Sum
    Polynomial p1({{2, 3}, {-1, 1}}); // 2x^3 - x
    Polynomial p2({{3, 3}, {5, 0}});  // 3x^3 + 5
    Polynomial sum = p1 + p2;         // 5x^3 - x + 5
    assert(sum.terms.size() == 3);
    assert(sum.terms[0].coeff == 5 && sum.terms[0].degree == 3);
    assert(sum.terms[1].coeff == -1 && sum.terms[1].degree == 1);
    assert(sum.terms[2].coeff == 5 && sum.terms[2].degree == 0);

    // Diff
    Polynomial diff = p1 - p2;        // -x^3 - x - 5
    assert(diff.terms.size() == 3);
    assert(diff.terms[0].coeff == -1 && diff.terms[0].degree == 3);

    // Prod
    Polynomial p3({{2, 1}});          // 2x
    Polynomial p4({{3, 2}});          // 3x^2
    Polynomial prod = p3 * p4;        // 6x^3
    assert(prod.terms.size() == 1);
    assert(prod.terms[0].coeff == 6 && prod.terms[0].degree == 3);

    // Lead
    Term lt = lead_term(sum);
    assert(lt.coeff == 5 && lt.degree == 3);

    std::cout << "All tests passed\n\n";

    std::cout << "=== Polynomial Calculator ===\n";
    std::cout << "Enter two polynomials to add:\n\n";

    std::cout << "First polynomial:\n";
    Polynomial a = read_poly();

    std::cout << "\nSecond polynomial:\n";
    Polynomial b = read_poly();

    std::cout << "\nResults:\n";
    std::cout << "Sum:      "; print_polynomial(a + b); std::cout << "\n";
    std::cout << "Diff:     "; print_polynomial(a - b); std::cout << "\n";
    std::cout << "Product:  "; print_polynomial(a * b); std::cout << "\n";

    Term lt_a = lead_term(a);
    if (lt_a.coeff != 0) {
        std::cout << "Lead term of first: ";
    }
}