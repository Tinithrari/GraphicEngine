#pragma once

#include "Point.hpp"

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
        Point<T, PLANE_DIMENSION> p1; /*<! Premier points du plan */
        Point<T, PLANE_DIMENSION> p2; /*<! Deuxieme points du plan */
        Point<T, PLANE_DIMENSION> p3; /*<! Troisieme points du plan */
        Point<T, PLANE_DIMENSION> p4; /*<! Quatrieme points du plan */

    public:
        /**
         * Constructeur par defaut
         * 
         * @param p1 Le premier point du plan
         * @param p2 Le deuxieme point du plan
         * @param p3 Le troisieme point du plan
         * @param p4 Le quatrieme point du plan
         */
        Plane(Point &p1, Point &p2, Point &p3, Point &p4) : p1(p1), p2(p2), p3(p3), p4(p4)
        {
        }

        isFrontOf(Point<T, PLANE_DIMENSION> &p)
        {
            return false;
        }
    };
}
