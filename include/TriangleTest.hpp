#pragma once

#include "geometry/Point.hpp"
#include "geometry/Triangle.hpp"

#include <TestCaller.h>
#include <TestResult.h>
#include <TestResultCollector.h>
#include <ui/text/TestRunner.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <stdexcept>
#include <iostream>

using namespace CppUnit;

class TestTriangle : public TestFixture
{
public:

    /**
     * Test the constructor
     */
    void testCtor()
    {
        geometry::Point<float, 3> p0{0, 0, 0};
        geometry::Point<float, 3> p1{1, 1, 0};
        geometry::Point<float, 3> p2{1, 0, 0};

        geometry::Triangle<float> t{p0, p1, p2};

        CPPUNIT_ASSERT_EQUAL(t.get_p0(), p0);
        CPPUNIT_ASSERT_EQUAL(t.get_p1(), p1);
        CPPUNIT_ASSERT_EQUAL(t.get_p2(), p2);
    }
    
    /**
     * @brief Test the area function
     */
    void testArea()
    {
        geometry::Point<float, 3> p0{0, 0, 0};
        geometry::Point<float, 3> p1{1, 1, 0};
        geometry::Point<float, 3> p2{1, 0, 0};
        
        geometry::Triangle<float> t(p0, p1, p2);
        
        float area = t.area();
        
        p1 - p0;
        p2 - p0;
    }
};
