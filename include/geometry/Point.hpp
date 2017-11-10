#pragma once

#include "math/Vector.hpp"
#include "Plane.hpp"
#include "Quaternion.hpp"

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

        Point rotate()
        {
            return Point();
        }

        Direction<T, N> length_to(Point<T, N> &p)
        {
            return Direction();
        }
    };
}
