#pragma once

#include "geometry/Plane.hpp"
#include "geometry/Direction.hpp"
 
#include <TestCaller.h>
#include <TestResult.h>
#include <TestResultCollector.h>
#include <ui/text/TestRunner.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <stdexcept>
#include <iostream>

using namespace CppUnit;

class PlaneTest : public TestFixture
{
public:

    void testCtor()
    {
        geometry::Point<float, 3> p{0,0,0};
        geometry::Direction<float, 3> dir{-1, 0, 0};
        
        geometry::Plane<float> plane{p, dir};
    }
    
    void testPositionFrom()
    {
        geometry::Point<float, 3> p{0,0,0};
        geometry::Direction<float, 3> dir{1, 0, 0};
        
        geometry::Plane<float> plane{p, dir};
        
        geometry::Point<float, 3> front{1, 0, 0};
        geometry::Point<float, 3> on{0, 0, 0};
        geometry::Point<float, 3> behind{-1, 0, 0};
        
        CPPUNIT_ASSERT_EQUAL(1.d, plane.positionFrom(front));
        CPPUNIT_ASSERT_EQUAL(0.d, plane.positionFrom(on));
        CPPUNIT_ASSERT_EQUAL(-1.d, plane.positionFrom(behind));
    }
    
    void testIsFrontOf()
    {
        geometry::Point<float, 3> p{0,0,0};
        geometry::Direction<float, 3> dir{1, 0, 0};
        
        geometry::Plane<float> plane{p, dir};
        
        geometry::Point<float, 3> front{1, 0, 0};
        geometry::Point<float, 3> behind{-1, 0, 0};
        
        CPPUNIT_ASSERT(! plane.isFrontOf(front));
        CPPUNIT_ASSERT(plane.isFrontOf(behind));
    }
    
    void testIntersectCoef()
    {
        geometry::LineSegment<float, 3> intersect{geometry::Point<float, 3>{-1, 0, 0}, geometry::Point<float, 3>{1, 0, 0}};
        geometry::LineSegment<float, 3> noIntersect{geometry::Point<float, 3>{1, 1, 0}, geometry::Point<float, 3>{1, -1, 0}};
        
        geometry::Point<float, 3> p{0,0,0};
        geometry::Direction<float, 3> dir{-1, 0, 0};
        
        geometry::Plane<float> plane{p, dir};
        
        CPPUNIT_ASSERT_EQUAL(0.5d, plane.intersectCoef(intersect));
        CPPUNIT_ASSERT_EQUAL(0.d, plane.intersectCoef(noIntersect));
    }
    
    void testIntersec()
    {
        geometry::LineSegment<float, 3> intersect{geometry::Point<float, 3>{-1, 0, 0}, geometry::Point<float, 3>{1, 0, 0}};
        geometry::LineSegment<float, 3> noIntersect{geometry::Point<float, 3>{1, 1, 0}, geometry::Point<float, 3>{1, -1, 0}};
        
        geometry::Point<float, 3> p{0,0,0};
        geometry::Direction<float, 3> dir{-1, 0, 0};
        
        geometry::Plane<float> plane{p, dir};
        
        CPPUNIT_ASSERT_EQUAL(p, plane.intersec(intersect));
        
        try
        {
            plane.intersec(noIntersect);
            CPPUNIT_FAIL("Runtime exception not launched");
        }
        catch (std::runtime_error &e)
        {
        }
    }

    static TestSuite *suite()
    {
        TestSuite *suit = new TestSuite();
        suit->addTest(new TestCaller<PlaneTest>("testCtor", &PlaneTest::testCtor));
        suit->addTest(new TestCaller<PlaneTest>("testPositionFrom", &PlaneTest::testPositionFrom));
        suit->addTest(new TestCaller<PlaneTest>("testIsFrontOf", &PlaneTest::testIsFrontOf));
        suit->addTest(new TestCaller<PlaneTest>("testIntersectCoef", &PlaneTest::testIntersectCoef));
        suit->addTest(new TestCaller<PlaneTest>("testIntersec", &PlaneTest::testIntersec));

        return suit;
    }
};