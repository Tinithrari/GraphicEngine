#pragma once

#include "scene/Frustum.hpp"
#include "geometry/LineSegment.hpp"
#include "geometry/Sphere.hpp"
#include "geometry/Point.hpp"

#include <TestCaller.h>
#include <TestResult.h>
#include <TestResultCollector.h>
#include <ui/text/TestRunner.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace scene;
using namespace geometry;
using namespace CppUnit;

/**
 * @class FrustumTest
 * @author xavier
 * @date 06/12/17
 * @file FrustumTest.hpp
 * @brief Classe de test pour le frustum
 */
class FrustumTest : public TestFixture
{
private:
    /**
     * @brief Initialise le frustum et le retourne
     * @return Un frustum initialise
     */
    static Frustum initBoxView()
    {
        Plane<real> near(Point<real, 3>{0, 0, 0}, Direction<real, 3>{0, 0, -1});
        Plane<real> far(Point<real, 3>{0, 0, -1}, Direction<real, 3>{0, 0, 1});
        Plane<real> left(Point<real, 3>{-1, 0, -0.5f}, Direction<real, 3>{1, 0, 0});
        Plane<real> right(Point<real, 3>{1, 0, -0.5f}, Direction<real, 3>{-1, 0, 0});
        Plane<real> top(Point<real, 3>{0.5f, 1, -0.5f}, Direction<real, 3>{0, -1, 0});
        Plane<real> bottom(Point<real, 3>{0.5f, -1, -0.5f}, Direction<real, 3>{0, 1, 0});
        
        return Frustum(near, far, left, right, top, bottom);
    }
public:

    /**
     * @brief Test outside
     */
    void testOutside()
    {
        /************************************************
         * Test avec un point
         ***********************************************/
         Point<real, 3> inside{0.5f, 0.5f, -0.5f};
         Point<real, 3> outside{2.f, 2.f, 2.f};
         
         Frustum f = FrustumTest::initBoxView();
         
         CPPUNIT_ASSERT(f.outside(outside));
         CPPUNIT_ASSERT(! f.outside(inside));
        
        /************************************************
         * Test avec une sphere
         ***********************************************/
         Sphere<real> inside_sphere{inside, 1};
         Sphere<real> intersec_sphere{outside, 2};
         Sphere<real> outside_sphere{outside, 0.5f};
         
         CPPUNIT_ASSERT(f.outside(outside_sphere));
         CPPUNIT_ASSERT(! f.outside(intersec_sphere));
         CPPUNIT_ASSERT(! f.outside(inside_sphere));
    }
    
    void testInter()
    {
        Frustum f = FrustumTest::initBoxView();
        
        LineSegment<real, 3> noIntersection(Point<real, 3>{2, 2, 2}, Point<real, 3>{3, 3, 3});
        LineSegment<real, 3> inside(Point<real, 3>{-0.5, 0, 0}, Point<real, 3>{0.5, 0, 0});
        LineSegment<real, 3> perfore(Point<real, 3>{0, 0, 2}, Point<real, 3>{0, 0, 0.5});
        
        try
        {
            f.inter(noIntersection);
            CPPUNIT_FAIL("Runtime exception not launched");
        }
        catch (std::runtime_error &e)
        {
            CPPUNIT_ASSERT_EQUAL(inside, f.inter(inside));
            LineSegment<real, 3> expected{Point<real, 3>{0, 0, 0}, Point<real, 3>{0, 0, 0.5}};
            CPPUNIT_ASSERT_EQUAL(expected, f.inter(perfore));
        }
    }

    /**
     * @brief Prepare la suite de test et la retourne
     * @return La suite de test pour le frustum
     */
    static TestSuite* suite()
    {
        TestSuite *suit = new TestSuite();
        
        suit->addTest(new TestCaller<FrustumTest>("TestOutside", &FrustumTest::testOutside));
        suit->addTest(new TestCaller<FrustumTest>("TestInter", &FrustumTest::testInter));
        
        return suit;
    }
};

