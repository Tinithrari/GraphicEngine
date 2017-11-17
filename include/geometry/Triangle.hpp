#pragma once

#include "geometry/Point.hpp"

#include <iostream>

#define TRIANGLE_DIMENSION 3

/**
 * @namespace geometry
 *
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur
 */
namespace geometry
{
    /**
     * @class Triangle
     *
     * Représentation d'un triangle dans un espace 3D
     */
    template <class T>
    class Triangle
    {
    private:
        Point<T, TRIANGLE_DIMENSION> p0; /*<! Premier point du triangle */
        Point<T, TRIANGLE_DIMENSION> p1; /*<! Deuxieme point du triangle */
        Point<T, TRIANGLE_DIMENSION> p2; /*<! Troisieme point du triangle */

    public:

        /**
         * Construit un triangle a partir de trois points
         * @param p1 Le premier point du triangle
         * @param p2 Le deuxieme point du triangle
         * @param p3 Le troisieme point du triangle
         */
        Triangle(Point<T, TRIANGLE_DIMENSION> &p0, Point<T, TRIANGLE_DIMENSION> &p1, Point<T, TRIANGLE_DIMENSION> &p2) : p0(p0), p1(p1), p2(p2)
        {
        }

        /**
         * Calcul l'aire d'un triangle
         * @return Calcul l'aire d'un triangle et le retourne
         */
        double area()
        {
            return 0.5f * cross(p0 - p1, p0 - p2).norm();
        }

        /**
         * Verifie si le triangle contient une donnée invalide
         * @return true si le triangle contient une donnée invalide, false sinon
         */
        bool is_null()
        {
            return p0.is_null() || p1.is_null() || p2.is_null();
        }

        /**
         * Accesseur pour p0
         * @return p0
         */
        Point<T, TRIANGLE_DIMENSION> get_p0()
        {
            return p0;
        }

        /**
         * Accesseur pour p1
         * @return p1
         */
        Point<T, TRIANGLE_DIMENSION> get_p1()
        {
            return p1;
        }

        /**
         * Accesseur pour p2
         * @return p2
         */
        Point<T, TRIANGLE_DIMENSION> get_p2()
        {
            return p2;
        }

        template <class U>
        friend std::ostream& operator<<(std::ostream& out, const Triangle<U>& t);
    };

    template<class T>
    std::ostream& operator<<(std::ostream& out, const Triangle<T>& t)
    {
        out << "P0 : " << t.p0 << " P1 : " << t.p1 << " P2 : " << t.p2;
        return out;
    }
}
