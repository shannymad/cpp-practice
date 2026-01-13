#ifndef TERM_H
#define TERM_H

#include <cstddef> 

struct Term {
    int coeff;
    // TODO: для многомерного случая заменить degree на std::vector<size_t> exponents
    size_t degree;
};

#endif