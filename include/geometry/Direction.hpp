#pragma once

#include "math/Vector.hpp"

/**
 * @namespace geometry
 *
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur
 */
namespace geometry
{
    /**
     * @class Direction
     * @brief Représente une direction
     *
     * Représente une direction de dimension N, où les coordonnées sont de type T
     */
    template <class T, unsigned int N>
    class Direction : math::Vector<T, N>
    {
    public:
        using math::Vector::Vector; /*<! Indique l'usage des constructeurs de Vector comme constructeurs de Direction */
    };
}
