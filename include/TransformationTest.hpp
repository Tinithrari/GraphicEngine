#pragma once
#include "geometry/Transformation.hpp"

#include <TestCaller.h>
#include <TestResult.h>
#include <TestResultCollector.h>
#include <ui/text/TestRunner.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <stdexcept>

using namespace CppUnit;

/**
 * @class TransformationTest
 * @author xavier
 * @date 03/12/17
 * @file TransformationTest.hpp
 * @brief Test unitaire pour les transformations
 */
class TransformationTest : public TestFixture
{
public:

    /**
     * @brief Test les constructeurs des Transformations
     */
    void testConstructor()
    {
        /**********************************************
         * Test avec Quaternion
         **********************************************/
         const float angle = 180;
         geometry::Direction<real, 3> dir{0, 1, 0};
         geometry::Quaternion<real> qTest{angle, dir};
         geometry::Transformation<real> quaternionMat{qTest};
         geometry::Transformation<real> expectedMat{math::Mat44r{
           {-1, 0, 0, 0},
           {0,  1, 0, 0},
           {0, 0, -1, 0},
           {0, 0, 0, 0}
         }};
         
         CPPUNIT_ASSERT_EQUAL(expectedMat, quaternionMat);
         
         /**********************************************
         * Test avec angle et Direction
         **********************************************/
         geometry::Transformation<real> angDirMat{angle, dir};
         CPPUNIT_ASSERT_EQUAL(quaternionMat, angDirMat);
    }
    
    /**
     * @brief Test des methodes de transformations
     */
    void testTransform()
    {
        const float angle = 180;
        geometry::Direction<real, 3> dir{0, 1, 0};
        geometry::Transformation<real> mat{angle, dir};
        
        geometry::Point<real, 3> pt{1, 1, 1};
        geometry::Point<real, 3> expected{-1, 1, -1};
        
        CPPUNIT_ASSERT_EQUAL(expected, mat.transform(pt));
    }
    
    /**
     * @brief Test des methodes factory
     */
    void testFactory()
    {
        geometry::Transformation<real> translation = geometry::Transformation<real>::createTranslation(1.f, 1.f, 1.f);
        geometry::Transformation<real> expectedTranslation{math::Mat44r{
            {0, 0, 0, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 1},
            {0, 0, 0, 1}
        }};
        
        CPPUNIT_ASSERT_EQUAL(expectedTranslation, translation);
        
        geometry::Transformation<real> scaling = geometry::Transformation<real>::createScaling(1.f, 1.f, 1.f);
        geometry::Transformation<real> expectedScaling{math::Mat44r{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        }};
        
        CPPUNIT_ASSERT_EQUAL(expectedScaling, scaling);
    }
    
    void testConcat()
    {
        geometry::Transformation<real> translation = geometry::Transformation<real>::createTranslation(1.f, 1.f, 1.f);
        geometry::Transformation<real> scaling = geometry::Transformation<real>::createScaling(1.f, 1.f, 1.f);
        geometry::Transformation<real> transAndScale = translation.concat(scaling);

        geometry::Transformation<real> expectedConcat{math::Mat44r{
            {1, 0, 0, 1},
            {0, 1, 0, 1},
            {0, 0, 1, 1},
            {0, 0, 0, 1}
        }};
        
        CPPUNIT_ASSERT_EQUAL(expectedConcat, transAndScale);
    }

    /**
     * @brief Prepare la suite de tests pour les Transformations
     * @return La suite de tests pour les transformations
     */
    static TestSuite *suite()
    {
        TestSuite *suit = new TestSuite();
        suit->addTest(new TestCaller<TransformationTest>("testConstructor", &TransformationTest::testConstructor));
        suit->addTest(new TestCaller<TransformationTest>("testTransform", &TransformationTest::testTransform));
        suit->addTest(new TestCaller<TransformationTest>("testFactory", &TransformationTest::testFactory));
        suit->addTest(new TestCaller<TransformationTest>("testConcat", &TransformationTest::testConcat));
        
        return suit;
    }
};
