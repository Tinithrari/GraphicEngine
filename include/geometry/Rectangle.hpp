#pragma once

#include "geometry/Point.hpp"
#include "math/Vector.hpp"

#include <iostream>

#define RECTANGLE_DIMENSION 2

/**
 * @namespace geometry
 *
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur
 */
namespace geometry
{
    /**
     * @class Rectangle
     *
     * Définit un rectangle dans un espace 2D
     */
    template <class T>
    class Rectangle
    {
    private:
        Point<T, RECTANGLE_DIMENSION> origin; /*<! Origine du rectangle */
        math::Vector<T, RECTANGLE_DIMENSION> length; /*<! Longueur d'un rectangle */

    public:
        /**
         * Construit un rectangle à partir d'un point d'origine et d'une longueur
         * @param origin le point d'origine du rectangle
         * @param length la longueur du rectangle
         */
        Rectangle(Point<T, RECTANGLE_DIMENSION> &origin, math::Vector<T, RECTANGLE_DIMENSION> &length) : origin(origin), length(length)
        {

        }

        /**
         * Verifie si le rectangle ne contient pas de donnees invalides
         * @return true si le rectangle contient des donnees invalides, false sinon
         */
        bool is_null()
        {
            return origin.is_null() || length.is_null();
        }

        friend std::ostream& operator<<(std::ostream& out, Rectangle &r);
    };

    template<class T>
    std::ostream& operator<<(std::ostream& out, Rectangle<T> &r)
    {
        out << "Origine : " << r.origin << " Length : " << r.length;
        return out;
    }
}
