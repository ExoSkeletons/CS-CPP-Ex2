//
// Created by Aviad Levine on 14/04/2025.
//

#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H
#include <stdexcept>

namespace matrix {
    class SquareMat {
        // Deletes a given row and col from matrix (returns n-1 matrix)
        static SquareMat delRowCol(const SquareMat &mat, int row, int col);

        // Recursively calculates the determinant of the given matrix
        static double det(const SquareMat &mat);

    public:
        static SquareMat diagonal(int n, double value);

        static SquareMat identity(const int n) { return diagonal(n, 1); }

    private:
        // Matrix memory pointer
        double **matrix;

    public:
        const int n;

        explicit SquareMat(int n);

        SquareMat(const SquareMat &copy);

        ~SquareMat();


        // Determinant
        double det() const { return det(*this); }

        // Element Sum
        double sum() const;

        /* Element Access */

        double *operator[](const int i) { return matrix[i]; }

        const double *operator[](const int i) const { return matrix[i]; }


        /* Math Operators */

        // Matrix addition
        SquareMat operator+(const SquareMat &other) const;

        // Matrix subtraction
        SquareMat operator-(const SquareMat &other) const;

        // Matrix multiplication
        SquareMat operator*(const SquareMat &other) const;

        // Single Element-wise multiplication
        SquareMat operator%(const SquareMat &other) const;

        // Scalar multiplication
        SquareMat operator*(double scalar) const;

        // Scalar division
        SquareMat operator/(double scalar) const;

        // Scalar modulo multiplication
        SquareMat operator%(int scalar) const;

        // Matrix power
        SquareMat operator^(int exp) const;


        /* Assignments */

        SquareMat &operator=(const SquareMat &copy) {
            if (copy.n != n) throw std::invalid_argument("Matrix size mismatch");
            if (this != &copy) {
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        this->matrix[i][j] = copy.matrix[i][j];
            }
            return *this;
        }

        SquareMat &operator*=(const SquareMat &other) { return *this = *this * other; }

        SquareMat &operator%=(const SquareMat &other) { return *this = *this % other; }

        SquareMat &operator*=(const double scalar) { return *this = *this * scalar; }

        SquareMat &operator/=(const double scalar) {
            if (scalar == 0) throw std::invalid_argument("Division by zero");
            return *this = *this / scalar;
        }

        SquareMat &operator%=(const int scalar) {
            if (scalar == 0) throw std::invalid_argument("Division by zero");
            return *this = *this % scalar;
        }


        /* Incrementation */

        // Prefix increment
        SquareMat &operator++();

        // Postfix increment
        SquareMat operator++(int);

        // Prefix decrement
        SquareMat &operator--();

        // Postfix decrement
        SquareMat operator--(int);


        /* Unary Operators */

        // Negation
        SquareMat operator-() const;

        // Transpose
        SquareMat operator~() const;

        // Determinant
        double operator!() const;


        /* Comparison */

        bool operator==(const SquareMat &other) const;

        bool operator!=(const SquareMat &other) const { return !(*this == other); }

        bool operator<(const SquareMat &other) const;

        bool operator<=(const SquareMat &other) const { return (*this < other) || (*this == other); }

        bool operator>(const SquareMat &other) const { return other < *this; }

        bool operator>=(const SquareMat &other) const { return !(*this < other); }


        /* Friends */

        friend std::ostream &operator<<(std::ostream &os, const SquareMat &mat);
    };

    inline SquareMat operator*(const double scalar, const SquareMat &mat) { return mat * scalar; }

    // Stream
    std::ostream &operator<<(std::ostream &os, const SquareMat &mat);
} // matrix

#endif //SQUARE_MATRIX_H
