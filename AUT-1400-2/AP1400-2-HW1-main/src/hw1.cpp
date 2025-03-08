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

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dis(min, max);

        Matrix matrix(n, Vector(m));
        for (auto& row : matrix)
            for (auto& elem : row)
                elem = dis(gen);

        return matrix;
    }
}