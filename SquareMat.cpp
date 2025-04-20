//
// Created by Aviad Levine on 14/04/2025.
//

#include "SquareMat.h"
#include <iostream>
#include <cmath>

namespace matrix {
    SquareMat SquareMat::delRowCol(const SquareMat &mat, const int row, const int col) {
        /*
        std::cout << mat << std::endl;
        std::cout << "removing " << row << "," << col << std::endl;
        */
        SquareMat smaller(mat.n - 1);
        for (int i = 0, is = 0; i < mat.n; i++) {
            if (i == row) continue;
            for (int j = 0, js = 0; j < mat.n; j++) {
                if (j == col) continue;
                smaller[is][js] = mat.matrix[i][j];
                js++;
            }
            is++;
        }
        // std::cout << smaller << std::endl;
        return smaller;
    }

    double SquareMat::det(const SquareMat &mat) {
        if (mat.n == 1) return mat.matrix[0][0];
        if (mat.n == 2)
            return mat.matrix[0][0] * mat.matrix[1][1] - mat.matrix[0][1] * mat.matrix[1][0];

        if (mat == identity(mat.n)) return 1.0;

        double sum = 0;
        for (int i = 0, sign = 1; i < mat.n; i++, sign *= -1) {
            if (const auto element = mat.matrix[0][i]; element != 0)
                // recursively multiply with smaller det
                sum += sign * element * det(delRowCol(mat, 0, i));
        }
        return sum;
    }


    SquareMat::SquareMat(const int n): n(n) {
        if (n == 0) throw std::invalid_argument("Matrix size must be positive non-zero");

        this->matrix = new double *[n];
        for (int i = 0; i < n; i++)
            this->matrix[i] = new double[n];

        *this = 0;
    }

    SquareMat::SquareMat(const SquareMat &copy): SquareMat(copy.n) {
        *this = copy;
    }

    SquareMat::~SquareMat() {
        for (int i = 0; i < n; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;
    }

    SquareMat SquareMat::diagonal(const int n, const double value) {
        SquareMat result(n);
        for (int i = 0; i < n; i++)
            result.matrix[i][i] = value;
        return result;
    }


    double SquareMat::sum() const {
        double sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                sum += this->matrix[i][j];
        return sum;
    }


    SquareMat SquareMat::operator+(const SquareMat &other) const {
        if (n != other.n) throw std::invalid_argument("Matrix size mismatch");
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        return result;
    }

    SquareMat SquareMat::operator-(const SquareMat &other) const {
        if (n != other.n) throw std::invalid_argument("Matrix size mismatch");
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        return result;
    }

    SquareMat SquareMat::operator*(const SquareMat &other) const {
        if (n != other.n) throw std::invalid_argument("Matrix size mismatch");
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int k = 0; k < n; ++k)
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
        return result;
    }

    SquareMat SquareMat::operator%(const SquareMat &other) const {
        if (n != other.n) throw std::invalid_argument("Matrix size mismatch");
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                result.matrix[i][j] = matrix[i][j] * other.matrix[i][j];
        return result;
    }

    SquareMat SquareMat::operator*(const double scalar) const {
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                result.matrix[i][j] = matrix[i][j] * scalar;
        return result;
    }

    SquareMat SquareMat::operator/(const double scalar) const {
        if (scalar == 0) throw std::invalid_argument("Division by zero");
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                result.matrix[i][j] = matrix[i][j] / scalar;
        return result;
    }

    SquareMat SquareMat::operator%(const int scalar) const {
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                result.matrix[i][j] = fmod(matrix[i][j], scalar);
        return result;
    }

    SquareMat SquareMat::operator^(const int exp) const {
        if (exp < 0) throw std::invalid_argument("Negative exponent not supported");
        if (exp == 1) return *this;

        // Make identity
        SquareMat result = identity(n);
        // Apply repeat mul
        for (int i = 0; i < exp; ++i)
            result *= *this;

        return result;
    }


    SquareMat &SquareMat::operator++() {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ++matrix[i][j];
        return *this;
    }

    SquareMat SquareMat::operator++(int) {
        SquareMat pre(*this);
        ++(*this);
        return pre;
    }

    SquareMat &SquareMat::operator--() {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                --matrix[i][j];
        return *this;
    }

    SquareMat SquareMat::operator--(int) {
        SquareMat pre(*this);
        --(*this);
        return pre;
    }


    SquareMat SquareMat::operator-() const {
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                result.matrix[i][j] = -matrix[i][j];
        return result;
    }

    SquareMat SquareMat::operator~() const {
        SquareMat result(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                result.matrix[i][j] = matrix[j][i];
        return result;
    }

    double SquareMat::operator!() const {
        return det();
    }

    bool SquareMat::operator==(const SquareMat &other) const {
        return this->sum() == other.sum();
    }

    bool SquareMat::operator<(const SquareMat &other) const {
        return this->sum() < other.sum();
    }


    std::ostream &operator<<(std::ostream &os, const SquareMat &mat) {
        for (int i = 0; i < mat.n; i++) {
            for (int j = 0; j < mat.n; j++)
                os << mat.matrix[i][j] << '\t';
            os << '\n';
        }
        return os;
    }
} // matrix
