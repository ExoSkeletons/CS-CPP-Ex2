#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.h"

using namespace matrix;

TEST_SUITE("Square Matrix") {
    TEST_CASE("Construction, Copy") {
        SquareMat a(2);
        a[0][0] = 1;
        a[0][1] = 2;
        a[1][0] = 3;
        a[1][1] = 4;

        auto b = SquareMat(a);
        CHECK(b[0][0] == 1);
        CHECK(b[1][1] == 4);
    }

    TEST_CASE("Element Access, Sum") {
        SquareMat m(2);
        m[0][0] = 5;
        m[0][1] = 3;
        m[1][0] = 2;
        m[1][1] = 0;
        CHECK(m[0][0] == 5);
        CHECK(m[0][1] == 3);
        CHECK(m[1][0] == 2);
        CHECK(m[1][1] == 0);
        CHECK(m.sum() == 10);
    }

    TEST_CASE("Addition, Subtraction") {
        SquareMat a(2), b(2);
        a[0][0] = 1;
        a[0][1] = 2;
        a[1][0] = 3;
        a[1][1] = 4;
        b[0][0] = 5;
        b[0][1] = 6;
        b[1][0] = 7;
        b[1][1] = 8;

        auto c = a + b;
        CHECK(c[1][1] == 12);

        auto d = b - a;
        CHECK(d[0][0] == 4);

        SquareMat e(3);
        CHECK_THROWS(a + e);
        CHECK_THROWS(a - e);
        CHECK_THROWS(e+a);
        CHECK_THROWS(e-b);
    }

    TEST_CASE("Matrix Multiplication") {
        SquareMat a(2), b(2);
        a[0][0] = 1;
        a[0][1] = 2;
        a[1][0] = 3;
        a[1][1] = 4;

        b[0][0] = 2;
        b[0][1] = 0;
        b[1][0] = 1;
        b[1][1] = 2;

        auto c = a * b;
        CHECK(c[0][0] == 4); // 1*2 + 2*1
        CHECK(c[1][1] == 8); // 3*0 + 4*2

        auto d = a % b;
        CHECK(d[0][0] == 2); // 1*2
        CHECK(d[0][1] == 0); // 2*0
        CHECK(d[1][0] == 3); // 3*1
        CHECK(d[1][1] == 8); // 4*2

        SquareMat e(3);
        CHECK_THROWS(a * e);
        CHECK_THROWS(e * b);
        CHECK_THROWS(a % e);
        CHECK_THROWS(b % e);
    }

    TEST_CASE("Scalar Multiplication, Division, Mod") {
        SquareMat a(2);
        a[0][0] = 3;
        a[0][1] = 6;
        a[1][0] = 9;
        a[1][1] = 12;

        auto b = a * 2.0;
        CHECK(b[1][0] == 18);

        auto c = b / 3.0;
        CHECK(c[1][1] == 8);

        auto d = a % 5;
        CHECK(d[0][1] == 1); // 6 % 5

        CHECK_THROWS(a %= 0); // Mod by zero
        CHECK_THROWS(a /= 0); // Div by zero
    }

    TEST_CASE("Assignment") {
        SquareMat a(2), b(2);
        a[0][0] = 1;
        a[0][1] = 2;
        a[1][0] = 3;
        a[1][1] = 4;

        b = a;
        CHECK(b[0][0] == 1);
        CHECK(b[0][1] == 2);
        CHECK(b[1][0] == 3);
        CHECK(b[1][1] == 4);

        SquareMat c(3);
        CHECK_THROWS(a = c);

        b *= 2;
        CHECK(b[1][1] == 8);

        b /= 2;
        CHECK(b[1][1] == 4);

        b %= 3;
        CHECK(b[1][1] == 1);
    }

    TEST_CASE("Power") {
        SquareMat m(2);
        m[0][0] = 1;
        m[0][1] = 1;
        m[1][0] = 1;
        m[1][1] = 0;

        auto m0 = m ^ 0;
        auto m1 = m ^ 1;
        auto m2 = m ^ 2;

        CHECK_THROWS(m ^ -1);
        CHECK(m0 == SquareMat::identity(m.n));
        CHECK(m1 == m);
        CHECK(m2[0][0] == 2);
        CHECK(m2[1][0] == 1);
    }

    TEST_CASE("Negation") {
        SquareMat a(2);
        a[0][0] = 1;
        a[0][1] = -2;
        a[1][0] = 3;
        a[1][1] = -4;

        auto na = -a;
        CHECK(na[0][0] == -1);
        CHECK(na[0][1] == 2);
        CHECK(na[1][0] == -3);
        CHECK(na[1][1] == 4);
    }

    TEST_CASE("Transpose") {
        SquareMat a(2);
        a[0][0] = 1;
        a[0][1] = -2;
        a[1][0] = 3;
        a[1][1] = -4;

        auto t = ~a;
        CHECK(t[1][0] == -2);
    }

    TEST_CASE("Increment, Decrement") {
        SquareMat a(2);
        a[0][0] = 1;
        a[0][1] = 1;
        a[1][0] = 1;
        a[1][1] = 1;

        ++a;
        CHECK(a[0][0] == 2);

        a++;
        CHECK(a[1][1] == 3);

        --a;
        CHECK(a[0][1] == 2);

        a--;
        CHECK(a[1][0] == 1);
    }

    TEST_CASE("Determinant") {
        SquareMat m1(1), m2(2), m3(3);
        m1[0][0] = 5;

        m2[0][0] = 1;
        m2[0][1] = 2;
        m2[1][0] = 3;
        m2[1][1] = 4;

        m3[0][0] = 2;
        m3[0][1] = 4;
        m3[0][2] = 2;
        m3[1][0] = 1;
        m3[1][1] = 0;
        m3[1][2] = -1;
        m3[2][0] = 3;
        m3[2][1] = 1;
        m3[2][2] = 2;


        CHECK(!m1==5);
        CHECK(!m2 == -2.0);
        CHECK(!m3 == -16.0);
        CHECK(!SquareMat::identity(6) == 1.0);
        CHECK(!SquareMat(7) == 0.0);

        CHECK(m2.det() == !m2);
    }

    TEST_CASE("Comparison (by sum)") {
        SquareMat a(2), b(2), c(2), d(3);
        a[0][0] = 1;
        a[0][1] = 1;
        a[1][0] = 1;
        a[1][1] = 1;

        d[0][0] = 2;
        d[2][2] = 2;

        b = a;
        c = a * 2;

        CHECK(a == b);
        CHECK(a != c);
        CHECK(a < c);
        CHECK(a <= c);
        CHECK(c > b);
        CHECK(c >= b);

        CHECK(a == d);
    }
}
