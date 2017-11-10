#pragma once

#include "math/Vector.hpp"

#define NB_POINTS_IN_PLANE 4
#define PLANE_DIMENSION 3

/**
 * @namespace geometry
 * 
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur 
 */
namespace geometry
{
    template <class T>
    class Plane<T, PLANE_DIMENSION>
    {
    private:
        math::Point<T, PLANE_DIMENSION> points[NB_POINTS_IN_PLANE]; /*<! Points du plan */

    public:
        /**
         * Constructeur par defaut 
         */
        Plane()
        {
        }

        Plane(const initializer_list<T> &list)
        {
            for (int i = 0; i < NB_POINTS_IN_PLANE; ++i)
            {
                points
            }
        }

        isFrontOf(Point<T, PLANE_DIMENSION> &p)
        {
            return false;
        }
    };
}
