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

class TriangleTest : public TestFixture
{
public:

    /**
     * Test the constructor
     */
    void testCtorAndGetters()
    {
        geometry::Point<float, 3> p0 {0, 0, 0};
        geometry::Point<float, 3> p1 {1, 1, 0};
        geometry::Point<float, 3> p2 {1, 0, 0};

        geometry::Triangle<float> t {p0, p1, p2};

        CPPUNIT_ASSERT_EQUAL(t.get_p0(), p0);
        CPPUNIT_ASSERT_EQUAL(t.get_p1(), p1);
        CPPUNIT_ASSERT_EQUAL(t.get_p2(), p2);
    }
    
    /**
     * @brief Test the area function
     */
    void testArea()
    {
        geometry::Point<float, 3> p0 {0, 0, 0};
        geometry::Point<float, 3> p1 {1, 1, 0};
        geometry::Point<float, 3> p2 {1, 0, 0};
        
        geometry::Triangle<float> t(p0, p1, p2);
        
        float area = t.area();
        float expectedArea;
        
        math::Vector<float, 3> ab = p0 - p1;
        math::Vector<float, 3> ac = p0 - p2;
        
        expectedArea = ab.cross(ac).norm() / 2;
    
        CPPUNIT_ASSERT_EQUAL(expectedArea, area);
        
    }
    
    /**
     * @brief Test la detection de coordonnées nulle
     */
    void testIsNull()
    {
        geometry::Point<float, 3> p0 {0, NAN, 0};
        geometry::Point<float, 3> p1 {1, 1, 0};
        geometry::Point<float, 3> p2 {1, 0, 0};
        
        geometry::Triangle<float> t(p0, p1, p2);
        
        CPPUNIT_ASSERT(t.is_null());
        
        p0 = geometry::Point<float, 3> {0, 1, 0};
        p1 = geometry::Point<float, 3> {1, 1, NAN};
        p2 = geometry::Point<float, 3> {1, 0, 0};
        t = geometry::Triangle<float>(p0, p1, p2);
        
        CPPUNIT_ASSERT(t.is_null());
        
        p0 = geometry::Point<float, 3> {0, 1, 0};
        p1 = geometry::Point<float, 3> {1, 1, 0};
        p2 = geometry::Point<float, 3> {NAN, 0, 0};
        t = geometry::Triangle<float>(p0, p1, p2);
        
        CPPUNIT_ASSERT(t.is_null());
    
    }
    
    static TestSuite *suite()
    {
        TestSuite *suit = new TestSuite();
        suit->addTest(new TestCaller<TriangleTest>("testCtorAndGetters", &TriangleTest::testCtorAndGetters));
        suit->addTest(new TestCaller<TriangleTest>("testArea", &TriangleTest::testArea));
        suit->addTest(new TestCaller<TriangleTest>("testIsNull", &TriangleTest::testIsNull));

        return suit;
    }
};
