#pragma once
#include "geometry/Point.hpp"

#include <TestCaller.h>
#include <TestResult.h>
#include <TestResultCollector.h>
#include <ui/text/TestRunner.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <stdexcept>

using namespace CppUnit;

/**
 * @class QuaternionTest
 * @author xavier
 * @date 03/12/17
 * @file QuaternionTest.hpp
 * @brief Fichier de tests unitaires pour les quaternions
 */
class QuaternionTest : public TestFixture
{
public:

    /**
     * @brief Test les constructeurs des quaternions
     */
    void testConstructor()
    {
        /*******************************************************
         * Test du constructeur avec un vecteur d'initialisation
         * *****************************************************/
        math::Vec4r initVector{0, 0, 0, 1};
        math::Vec3r imaginaryVector{0, 0, 1};
        geometry::Quaternion<real> ctor1(initVector);
        
        CPPUNIT_ASSERT_EQUAL(0.f, ctor1.re());
        CPPUNIT_ASSERT_EQUAL(imaginaryVector, ctor1.im());
        
        /*******************************************************
         * Test du constructeur avec un angle et une direction
         ******************************************************/
        geometry::Direction<real, 3> directionForAngle{1, 1, 1};
        geometry::Quaternion<real> ctor2(90.f, directionForAngle);
        math::Vec3r imVector2{(float) std::sin(deg2rad(45.f)), (float) std::sin(deg2rad(45.f)), (float) std::sin(deg2rad(45.f))};
        
        CPPUNIT_ASSERT_EQUAL((float) std::cos(deg2rad(45.f)), ctor2.re());
        CPPUNIT_ASSERT_EQUAL(imVector2, ctor2.im());
    }
    
    /**
     * @brief Test la methode conjugate de quaternion
     */
    void testConjugate()
    {
        geometry::Quaternion<real> q{math::Vec4r{0, 1, 1, 1}};
        geometry::Quaternion<real> conjugate{math::Vec4r{0, -1, -1, -1}};
        
        CPPUNIT_ASSERT_EQUAL(conjugate, q.conjugate());
    }

    /**
     * @brief Test la fonction norm du quaternion
     */
    void testNorm()
    {
        geometry::Quaternion<real> q{math::Vec4r{2, 2, 2, 2}};
        
        CPPUNIT_ASSERT_EQUAL(q.getMembers().norm(), q.norm());
    }
    
    void testInverse()
    {
        geometry::Quaternion<real> q{math::Vec4r{2, 2, 2, 2}};
        
        CPPUNIT_ASSERT_EQUAL(q.conjugate() / (q.norm() * q.norm()), q.inverse());
    }

    /**
     * @brief Genere la suite de test pour les quaternions
     * @return La suite de tests pour les quaternions
     */
    static TestSuite *suite()
    {
        TestSuite *suit = new TestSuite();
        suit->addTest(new TestCaller<QuaternionTest>("TestConstructor", &QuaternionTest::testConstructor));
        suit->addTest(new TestCaller<QuaternionTest>("TestConjugate", &QuaternionTest::testConjugate));
        suit->addTest(new TestCaller<QuaternionTest>("TestInverse", &QuaternionTest::testInverse));
        suit->addTest(new TestCaller<QuaternionTest>("TestNorm", &QuaternionTest::testNorm));
        
        return suit;
    }
};
