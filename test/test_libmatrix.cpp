// test_matrix.cpp
//
// Tiago de Lima <tiago.delima@univ-artois.fr>
// 29 sep 2017
//
// Tests libmatrix.

#include <array>
#include <vector>
#include <iostream>
#include "unit_test.h"
#include "math/Matrix.hpp"
#include "math/Vector.hpp"

using namespace math;

int test_is_null()
{
    Vec2i a;
    Vec3i b;
    Vec4i c;
    Vec2r d;
    Vec3r e;
    Vec4r f;
    Vec2r g { NAN , 0 };
    Vec3r h { 0, NAN, 0 };
    Vec4r i { 0, 0, NAN, 0};

    TestVector test_vec
    {
        { "a.is_null()", a.is_null() == false },
        { "b.is_null()", b.is_null() == false },
        { "c.is_null()", c.is_null() == false },
        { "d.is_null()", d.is_null() == false },
        { "e.is_null()", e.is_null() == false },
        { "f.is_null()", f.is_null() == false },
        { "g.is_null()", g.is_null() == true },
        { "h.is_null()", h.is_null() == true },
        { "i.is_null()", i.is_null() == true }
    };

    return run_tests( "is_null()", test_vec );
}

int test_is_unit()
{
    std::vector<Vec3r> t
    {
        { 0, 0, 1 },
        { 0, 1, 0 },
        { 1, 0, 0 },
        { sqrt(2.0f)/2, sqrt(2.0f)/2, 0 },
    };
    std::vector<Vec3r> f
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.1f, 0.0f, 0.1f },
        { 3.0f, 0.0f, 1.0f },
        { 0.5f, 0.5f, 0.5f }
    };

    TestVector test_vec;
    for( int i { 0 }; i < t.size(); ++i )
    {
        test_vec.push_back( { "t[" + std::to_string(i) + "].is_unit()", t[i].is_unit() == true } );
    }
    for( int i { 0 }; i < f.size(); ++i )
    {
        test_vec.push_back( { "f[" + std::to_string(i) + "].is_unit()", f[i].is_unit() == false } );
    }

    return run_tests( "is_unit()", test_vec );
}

int test_norm()
{
    std::vector<Vec3r> v
    {
        { 0, 1, 2 },
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 9, 0, 0 }
    };
    TestVector test_vec
    {
        {"v[0].norm() == sqrt( 5.0f )", v[0].norm() == sqrt( 5.0f ) },
        {"v[1].norm() == sqrt( 14.0f )", v[1].norm() == sqrt( 14.0f ) },
        {"v[2].norm() == sqrt( 16.0f + 25.0f + 36.0f )", v[2].norm() == sqrt( 16.0f + 25.0f + 36.0f ) },
        {"v[3].norm() == 9.0f", v[3].norm() == 9.0f },
    };

    return run_tests( "norm()", test_vec );
}

int test_operator_sub()
{
    std::vector<Vec3r> v
    {
        { 0, 0, 1 },
        { 0.5f, 0.5f, 0.5f },
        { sqrt(2.0f)/2, -sqrt(2.0f)/2, 1.0f }
    };

    v[0][1] = 3;
    v[1][2] = 7;
    v[2][0] = 8;

    TestVector test_vec
    {
        {"v[0][1] == 3", v[0][1] == 3},
        {"v[1][2] == 7", v[1][2] == 7},
        {"v[2][0] == 8", v[2][0] == 8},
    };

    return run_tests( "operator[]", test_vec);
}

int test_operator_putout()
{
    std::cout << "Testing <<..." << std::endl;

    std::vector<Vec3r> v
    {
        { 0, 0, 1 },
        { 0.5f, 0.5f, 0.5f },
        { sqrt(2.0f)/2, -sqrt(2.0f)/2, 1.0f }
    };
    std::cout <<
        v[0] << std::endl <<
        v[1] << std::endl <<
        v[2] << std::endl;
    Vec4r a { 1.0f, 3.5f, 1.2f, 4.4f };
    Vec4r b { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4r c { 0.0f, 1.5f, -1.8f, 0.4f };
    std::cout <<
        a << std::endl <<
        b << std::endl <<
        c << std::endl;
    std::cout << std::endl;

    return 0;
}

int test_operator_plus()
{
    std::vector<Vec3r> v
    {
        { 0.0f, 0.0f, 0.0f },
        { 0.1f, 0.0f, 0.1f },
        { 0.2f, 0.0f, 0.2f },
        { 3.0f, 0.0f, 1.0f },
        { 3.1f, 0.0f, 1.1f },
        { 0.5f, 0.5f, 0.5f },
        { 3.6f, 0.5f, 1.6f }
    };
    TestVector test_vec
    {
        { "v[0] + v[1] == v[1]", v[0] + v[1] == v[1] },
        { "v[0] + v[2] == v[2]", v[0] + v[2] == v[2] },
        { "v[1] + v[1] == v[2]", v[1] + v[1] == v[2] },
        { "v[1] + v[3] == v[4]", v[1] + v[3] == v[4] },
        { "v[4] + v[5] == v[6]", v[4] + v[5] == v[6] }
    };

    return run_tests( "operator+( Vector )", test_vec );
}

int test_operator_pluseq()
{
    std::vector<Vec3r> v
    {
        { 0.1f, 0.0f, 0.1f },
        { 0.0f, 0.1f, 0.0f },
        { 0.2f, 0.0f, 0.2f },
        { 0.1f, 0.1f, 0.1f },
        { 0.2f, 0.1f, 0.2f }
    };
    v[0] += v[0];
    v[1] += v[0];
    v[3] += v[0];
    TestVector test_vec
    {
        { "v[0] == v[2]", !(v[0] != v[2]) },
        { "v[1] == v[4]", !(v[1] != v[4]) },
        { "v[3] != v[4]", v[3] != v[4] }
    };

    return run_tests( "operator+=( Vector )", test_vec );
}

int test_operator_minus1()
{
    std::vector<Vec3r> v
    {
        { 1, 2, 3 },
        { -1, -2, -3 },
        { 4, 5, 6 },
        { -4, -5, -6}
    };
    TestVector test_vec
    {
        { "-v[0] == v[1]", -v[0] == v[1] },
        { "-v[1] == v[0]", -v[1] == v[0] },
        { "-v[2] == v[3]", -v[2] == v[3] },
        { "-v[3] == v[2]", -v[3] == v[2] },
        { "--v[3] == v[3]", -(-v[3]) == v[3] }
    };

    return run_tests( "operator-()", test_vec );
}

int test_operator_minus2()
{
    Vec4r a { 1.0f, 3.5f, 1.2f, 4.4f };
    Vec4r b { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4r c { 0.0f, 1.5f, -1.8f, 0.4f };
    TestVector test_vec
    {
        { "a - b == c", a - b == c }
    };

    return run_tests( "operator-( Vector )", test_vec );
}

int test_dot1()
{
    Vec4r a { 1.0f, 3.5f, 1.2f, 4.4f };
    Vec4r b { 2.0f, 7.0f, 2.4f, 8.8f };
    Vec4r c { -1.0f, -3.5f, -1.2f, -4.4f };
    real x { 1.0f };
    real y { 2.0f };
    real z { -0.5f };
    real w { -1.0f };
    TestVector test_vec
    {
        { "dot( a, x ) == a", dot( a, x ) == a },
        { "dot( a, y ) == b", dot( a, y ) == b },
        { "dot( b, z ) == c", dot( b, z ) == c },
        { "dot( c, w ) == a", dot( c, w ) == a }
    };
    TestVector test_vec2
    {
        { "dot( x, a ) == a", dot( x, a ) == a },
        { "dot( y, a ) == b", dot( y, a ) == b },
        { "dot( z, b ) == c", dot( z, b ) == c },
        { "dot( w, c ) == a", dot( w, c ) == a }
};

    return run_tests( "dot( Vector, scalar )", test_vec ) +
           run_tests( "dot( scalar, Vector )", test_vec2 );
}

int test_dot2()
{
    Vec4r a { 1.0f, 3.0f, 1.0f, 4.0f };
    Vec4r b { 2.0f, 7.0f, 2.4f, 8.8f };
    Vec4r c { 1.0f, 2.0f, 3.0f, 4.0f };
    Vec4r d { 5.0f, 6.0f, 7.0f, 8.0f };
    real x { 60.6f };
    real y { 70.0f };
    TestVector test_vec
    {
        { "dot( a, b ) == x", dot( a, b ) == x },
        { "dot( c, d ) == y", dot( c, d ) == y }
    };

    return run_tests( "dot( Vector, Vector )", test_vec );
 }

int test_cross()
{
	Vec4r v0 { 0, 1, 2, 3 };
	Vec4r v1 { 3, 4, 5, 6 };
	Vec4r v2 { 5 - 8, 6 - 0, 0 - 3, 0 }; 
    Vec4r a { 0, 0, 1, 0 };
    Vec4r b { 0, 1, 0, 0 };
    Vec4r c { -1, 0, 0, 0 };
    TestVector test_vec
    {
        { "cross( v0, v1 ) == v2", cross( v0, v1 ) == v2 },
        { "cross( a, b ) == c", cross( a, b ) == c }
    };

    return run_tests( "cross( Vector, Vector )", test_vec );
}
int main()
{
    int failures { 0 };

    failures += test_operator_sub();
    failures += test_is_null();
    failures += test_is_unit();
    failures += test_norm();
    failures += test_operator_plus();
    failures += test_operator_pluseq();
    failures += test_operator_minus1();
    failures += test_operator_minus2();
    failures += test_dot1();
    failures += test_dot2();
    failures += test_cross();
    failures += test_operator_putout();

    if( failures > 0 )
    {
        std::cout << "Total failures : " << failures << std::endl;
        std::cout << "TEST FAILED!!" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Success!" << std::endl;
        return 0;
    }
}
