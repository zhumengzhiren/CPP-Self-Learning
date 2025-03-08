#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>
#include <random>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

namespace algebra {
    Matrix zeros(size_t n, size_t m);
    Matrix ones(size_t n, size_t m);
    Matrix random(size_t n, size_t m, double min, double max);
}

#endif //AP_HW1_H
