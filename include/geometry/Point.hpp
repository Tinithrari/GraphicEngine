#pragma once

#include "math/Vector.hpp"
#include "geometry/Direction.hpp"

#include <iostream>

/**
 * @namespace geometry
 *
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur
 */
namespace geometry
{
    template <class T, unsigned int N>
    class Point : public math::Vector<T, N>
    {
    public:

        using math::Vector<T, N>::Vector; // Usage des constructeurs de la base class

        Point() : Point::Vector()
        {}

        Point(const math::Vector<T, N> &v) : Point::Vector(v)
        {}

        /** \brief Calcule la distance entre ce point et un autre
         *
         * \param p Le point dont on veut calculer la distance par rapport à celui-ci
         * \return La direction de ce point vers celui passé en paramètre
         */
        Direction<T, N> length_to(const Point<T, N> &p) const
        {
            Direction<T, N> dir;

            for (int i = 0; i < N; ++i)
                dir[i] = p[i] - this->at(i);

            return dir;
        }

        template <class U, unsigned int O>
        friend std::ostream& operator<<(std::ostream &out, Point<U, O> &p);
    };

    template <class T, unsigned int N>
    std::ostream& operator<<(std::ostream &out, Point<T, N> &p)
    {
        out << "(" << p[0];

        for (int i = 1; i < N; ++i)
            out << ", " << p[i];
        out << ")";

        return out;
    }
}
