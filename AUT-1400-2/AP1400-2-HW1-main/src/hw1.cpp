#include "hw1.h"


namespace algebra {
    Matrix zeros(size_t n, size_t m) {
        return Matrix(n, Vector(m, 0));
    }

    Matrix ones(size_t n, size_t m) {
        return Matrix(n, Vector(m, 1));
    }

    Matrix random(size_t n, size_t m, double min, double max) {
        if (min >= max)
            throw std::logic_error("min cannot be greater than max");

        // random number generator
        std::random_device rd;
        // Mersenne Twister engine with a seed from random device
        std::mt19937 gen(rd());
        // Generate random numbers between min and max
        std::uniform_real_distribution<double> dis(min, max);

        Matrix matrix(n, Vector(m));
        for (auto& row : matrix)
            for (auto& elem : row)
                elem = dis(gen);

        return matrix;
    }
}