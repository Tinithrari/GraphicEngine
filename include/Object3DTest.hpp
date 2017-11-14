#pragma once

#include "scene/Object3D.hpp"

#include <TestCaller.h>
#include <TestResult.h>
#include <TestResultCollector.h>
#include <ui/text/TestRunner.h>
#include <TestFixture.h>
#include <TestSuite.h>
#include <stdexcept>

using namespace CppUnit;

class Object3DTest : public TestFixture
{
public:
    /** \brief Test de la sphere de collision
     */
    void testBSphere()
    {

    }

    /** \brief Test de l'accesseur pour les faces
     */
    void testFace()
    {
        std::vector<Point<float, 3>> points{geometry::Point<float, 3>{0, 0, 0}, geometry::Point<float, 3>{1, 0, 0}, geometry::Point<float, 3>{0, 0, 1}};

        scene::Object3D o{points};

        o.add_face(0, 1, 2);

        CPPUNIT_ASSERT_EQUAL(points[0], o.face(0).get_p0());
        CPPUNIT_ASSERT_EQUAL(points[1], o.face(0).get_p1());
        CPPUNIT_ASSERT_EQUAL(points[2], o.face(0).get_p2());

        try {
            o.face(1);
            CPP_UNIT_FAIL("An illegal_argument exception must be launched");
        } catch (std::illegal_argument &e) {
        }
    }

    /** \brief Test pour l'ajout de face
     */
    void testAddFace()
    {
        std::vector<Point<float, 3>> points{geometry::Point<float, 3>{0, 0, 0}, geometry::Point<float, 3>{1, 0, 0}, geometry::Point<float, 3>{0, 0, 1}};

        scene::Object3D o{points};

        o.add_face(0, 1, 2);

        CPPUNIT_ASSERT_EQUAL(points[0], o.face(0).get_p0());
        CPPUNIT_ASSERT_EQUAL(points[1], o.face(0).get_p1());
        CPPUNIT_ASSERT_EQUAL(points[2], o.face(0).get_p2());
    }

    /** \brief Test pour le nombre de faces
     */
    void testNumFace()
    {
        std::vector<Point<float, 3>> points{geometry::Point<float, 3>{0, 0, 0}, geometry::Point<float, 3>{1, 0, 0}, geometry::Point<float, 3>{0, 0, 1}};

        scene::Object3D o{points};

        CPPUNIT_ASSERT_EQUAL(0, o.num_faces());

        o.add_face(0, 1, 2);

        CPPUNIT_ASSERT_EQUAL(1, o.num_faces);
    }

    /** \brief Test de suppression de sommet
     */
    void testRemoveFace()
    {
        std::vector<Point<float, 3>> points{geometry::Point<float, 3>{0, 0, 0}, geometry::Point<float, 3>{1, 0, 0}, geometry::Point<float, 3>{0, 0, 1}};

        scene::Object3D o{points};

        o.add_face(0, 1, 2);

        o.remove_face(0);

        CPPUNIT_ASSERT_EQUAL(0, o.num_faces());

        try {
            o.remove_face(0);
            CPPUNIT_FAIL("An illegal_argument exception must be launched when the index is incorrect");
        } catch (std::illegal_argument &e) {
        }
    }

    /** \brief Obtient la suite de test
     *
     * \return La suite de test lié à un Object3D
     */
    static TestSuite *suite()
    {
        TestSuite *suit = new TestSuite();
        suit->addTest(new TestCaller<Object3DTest>("testBSphere", &Object3DTest::testBSphere));
        suit->addTest(new TestCaller<Object3DTest>("testFace", &Object3DTest::testFace));
        suit->addTest(new TestCaller<Object3DTest>("testAddFace", &Object3DTest::testAddFace));
        suit->addTest(new TestCaller<Object3DTest>("testRemoveFace", &Object3DTest::testRemoveFace));
        suit->addTest(new TestCaller<Object3DTest>("testNumFace", &Object3DTest::testNumFace));
    }
};
