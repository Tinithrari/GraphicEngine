#pragma once

#include "Point.hpp"

#include <stdexcept>

#define SPHERE_DIMENSION 3

/**
 * @namespace geometry
 * 
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur 
 */
namespace geometry
{
    template <class T>
    class Sphere
    {
    private:
        Point<T, SPHERE_DIMENSION> center; /*<! Center of the circle */
        float radius; /*<! Radius of the circle */
    public:
        Sphere() center(), radius(0)
        {

        }

        Sphere(Point &center, float radius) : center(center)
        {
            if (radius < 0)
                throw std::invalid_argument("The radius must be postive");

            this->radius = radius;
        }
    };
}