#pragma once

#include "math/Vector.hpp"
#include "Plane.hpp"
#include "Quaternion.hpp"
#include "Direction.hpp"

#include <iostream>

/**
 * @namespace geometry
 *
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur
 */
namespace geometry
{
    template <class T, unsigned int N>
    class Point : math::Vector<T, N>
    {
    public:
        using math::Vector::Vector; // Usage des constructeurs de la base class

        /** \brief
         *
         * \param q Le quaternion utilisé pour la la rotation du point
         * \return Point
         */
        Point rotate(Quaternion& q)
        {
            Point<T, QUATERNION_DIMENSION> p(at(0), at(1), at(2), 1);

            Point<T, QUATERNION_DIMENSION> rotatedP(p * q.getMembers());

            return Point(rotatedP[0], rotatedP[1], rotatedP[2]);
        }

        /** \brief Calcule la distance entre ce point et un autre
         *
         * \param p Le point dont on veut calculer la distance par rapport à celui-ci
         * \return La direction de ce point vers celui passé en paramètre
         */
        Direction<T, N> length_to(Point<T, N> &p)
        {
            Direction<T, N> dir;

            for (int i = 0; i < N; ++i)
                dir[i] = p[i] - at(i);

            return dir;
        }

        friend std::ostream& operator<<(std::ostream &out, Point &p);
    };

    template <class T, unsigned int N>
    std::ostream& operator<<(std::ostream &out, Point &p)
    {
        out << "(" << p[0];

        for (int i = 1; i < N; ++i)
            out << ", " << p[i];
        out << ")";

        return out;
    }
}
