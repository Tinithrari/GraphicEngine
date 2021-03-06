#pragma once
#include <TestFixture.h>
#include <TestSuite.h>

using namespace CppUnit;

class MatrixTest : public TestFixture
{
public:
    void testAt();
    void testInverse();
    void testIsNull();
    void testIsOrtho();
    void testTranspose();
    void testOutStreamOperator();
    void testDirAccessor();
    void testAddition();
    void testDirAddition();
    void testMultWithScalar();
    void testMulWithVector();
    void testMulWithMatrix();
    void testDirMulWithScalar();
    static TestSuite *suite();
};