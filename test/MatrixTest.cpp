#include <iostream>
#include <TestCaller.h>
#include <TestResult.h>
#include <ui/text/TestRunner.h>

#include "MatrixTest.hpp"
#include "math/Vector.hpp"
#include "math/Matrix.hpp"

using namespace math;
using namespace std;

void MatrixTest::testAddition()
{
    Mat44r matrice {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    Mat44r expected {{2, 1, 1, 1}, {1, 2, 1, 1}, {1, 1, 2, 1}, {1, 1, 1, 2}};
    Mat44r result = matrice + Identity4r;

    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void MatrixTest::testAt()
{
    Matrix<int, 3, 3> m1 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    CPPUNIT_ASSERT(m1.at(0,0) == 1);
    CPPUNIT_ASSERT(m1.at(0,1) == 2);
    CPPUNIT_ASSERT(m1.at(0,2) == 3);

    CPPUNIT_ASSERT(m1.at(1,0) == 4);
    CPPUNIT_ASSERT(m1.at(1,1) == 5);
    CPPUNIT_ASSERT(m1.at(1,2) == 6);

    CPPUNIT_ASSERT(m1.at(2,0) == 7);
    CPPUNIT_ASSERT(m1.at(2,1) == 8);
    CPPUNIT_ASSERT(m1.at(2,2) == 9);
}

void MatrixTest::testDirAccessor()
{
    Matrix<int, 3, 3> m1 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    CPPUNIT_ASSERT(m1[0][0] == 1);
    CPPUNIT_ASSERT(m1[0][1] == 2);
    CPPUNIT_ASSERT(m1[0][2] == 3);

    CPPUNIT_ASSERT(m1[1][0] == 4);
    CPPUNIT_ASSERT(m1[1][1] == 5);
    CPPUNIT_ASSERT(m1[1][2] == 6);

    CPPUNIT_ASSERT(m1[2][0] == 7);
    CPPUNIT_ASSERT(m1[2][1] == 8);
    CPPUNIT_ASSERT(m1[2][2] == 9);
}

void MatrixTest::testDirAddition()
{
    Mat44r matrice {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    Mat44r expected {{2, 1, 1, 1}, {1, 2, 1, 1}, {1, 1, 2, 1}, {1, 1, 1, 2}};
    matrice += Identity4r;

    CPPUNIT_ASSERT_EQUAL(expected, matrice);
}

void MatrixTest::testDirMulWithScalar()
{
    Mat44r matrice {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    Mat44r expected {{2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}};
    
    matrice *= 2;

    CPPUNIT_ASSERT_EQUAL(expected, matrice);
}

void MatrixTest::testInverse()
{

}

void MatrixTest::testIsNull()
{
    Mat44r m1;
    
    CPPUNIT_ASSERT(m1.is_null());
    CPPUNIT_ASSERT(! (Identity4i.is_null()));
}

void MatrixTest::testIsOrtho()
{
    Matrix<int, 3, 3> matriceOrthogonale {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
    
    CPPUNIT_ASSERT(matriceOrthogonale.is_ortho());

    // TODO cas non orthogonal
}

void MatrixTest::testMultWithScalar()
{
    Matrix<int, 3, 3> m1 {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<int, 3, 3> expected {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}};

    CPPUNIT_ASSERT_EQUAL(expected, m1 * 2);
}

void MatrixTest::testMulWithVector()
{
    Matrix<int, 2, 3> matrice {{1, 2, 0}, {4, 3, -1}};
    Vector<int, 3> vecteur {5, 2, 3};
    Matrix<int, 2, 1> expected {{9}, {23}};
    Matrix<int, 2, 1> result = matrice * vecteur;

    CPPUNIT_ASSERT_EQUAL(expected, result);
}

void MatrixTest::testMulWithMatrix()
{
    Matrix<int, 2, 3> m1 {{1, 2, 0}, {4, 3, -1}};
    Matrix<int, 3, 2> m2 {{5, 1}, {2, 3}, {3, 4}};
    Matrix<int, 2, 2> expected {{9, 7}, {23, 9}};
}

void MatrixTest::testOutStreamOperator()
{
    // TODO
}

void MatrixTest::testTranspose()
{
    Matrix<int, 3, 3> matrice {{0, 1, 0}, {0, 0, 1}, {1, 0, 0}};
    Matrix<int, 3, 3> expected {{0, 1, 0}, {1, 0, 0}, {0, 0, 1}};

    CPPUNIT_ASSERT_EQUAL(expected, matrice.transpose());
}

TestSuite *MatrixTest::suite()
{
    TestSuite *suit = new TestSuite();
    suit->addTest(new TestCaller<MatrixTest>("testAddition", &MatrixTest::testAddition));
    suit->addTest(new TestCaller<MatrixTest>("testInverse", &MatrixTest::testInverse));
    suit->addTest(new TestCaller<MatrixTest>("testAt", &MatrixTest::testAt));
    suit->addTest(new TestCaller<MatrixTest>("testDirAccessor", &MatrixTest::testDirAccessor));
    suit->addTest(new TestCaller<MatrixTest>("testDirAddition", &MatrixTest::testDirAddition));
    suit->addTest(new TestCaller<MatrixTest>("testDirMulWithScalar", &MatrixTest::testDirMulWithScalar));
    suit->addTest(new TestCaller<MatrixTest>("testIsNull", &MatrixTest::testIsNull));
    suit->addTest(new TestCaller<MatrixTest>("testIsOrtho", &MatrixTest::testIsOrtho));
    suit->addTest(new TestCaller<MatrixTest>("testMultWithScalar", &MatrixTest::testMultWithScalar));
    suit->addTest(new TestCaller<MatrixTest>("testMulWithMatrix", &MatrixTest::testMulWithMatrix));
    suit->addTest(new TestCaller<MatrixTest>("testMulWithVector", &MatrixTest::testMulWithVector));
    suit->addTest(new TestCaller<MatrixTest>("testOutStreamOperator", &MatrixTest::testOutStreamOperator));
    suit->addTest(new TestCaller<MatrixTest>("testTranspose", &MatrixTest::testTranspose));

    return suit;
}

int main(void)
{
    TestSuite *suite = MatrixTest::suite();
    TextUi::TestRunner runner;
    
    runner.addTest(suite);

    runner.run();

    return 0;
}