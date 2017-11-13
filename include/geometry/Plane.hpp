#pragma once

#include "math/Vector.hpp"
#include "Point.hpp"
#include "Direction.hpp"

#include <stdexcept>
#include <iostream>

#define EQUATION_VECTOR_DIM 4
#define PLANE_DIMENSION 3

/**
 * @namespace geometry
 *
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur
 */
namespace geometry
{
    template <class T>
    class Plane
    {
    private:
        Point<T, PLANE_DIMENSION> p; /**< Le point par lequelle le point passe */
        math::Vector<T, EQUATION_VECTOR_DIM> equation; /**< L'equation du plan */
        math::Direction<T, PLANE_DIMENSION> n;
    public:

        /** \brief Construit un plan à l'aide du point par lequel il passe et un vector normal
         *
         * \param p Le point par lequel le point passe
         * \param n Le vecteur normal perpendiculaire au point p
         * \return Plane(Point<T, PLANE_DIMENSION> &p, Direction<T, PLANE_DIMENSION> &n):
         */
        Plane(Point<T, PLANE_DIMENSION> &p, Direction<T, PLANE_DIMENSION> &n) : p(p), n(n)
        {
            equation[0] = n[0] * p[0];
            equation[1] = n[1] * p[1];
            equation[2] = n[2] * p[2];
            equation[4] = (-n).dot(p);
        }

        /** \brief Calcule la position du point par rapport au point
         *
         * \param p Le point à tester
         * \return n < 0 si le point est derriere, n = 0 si le point appartient au plan, n > 0 si le point est devant
         */
        double positionFrom(Point<T, PLANE_DIMENSION &p)
        {
            return n.dot(p) + equation[3];
        }

        /** \brief Verifie si le plan est devant le point passé en paramètre
         *
         * \param p Le point dont on souhaite connaitre la disposition par rapport au plan
         * \return true si le plan est devant le plan, false sinon
         */
        bool isFrontOf(Point<T, PLANE_DIMENSION> &p)
        {
            return positionFrom(p) < 0;
        }

        /** \brief Calcule le point d'intersection entre un segment et un point
         *
         * \param ls Le segement de droite
         * \return Le point d'intersection entre le plan et la droite
         */
        Point<T, PLANE_DIMENSION> intersec(LineSegment<T, PLANE_DIMENSION> &ls)
        {
            double coef = intersecCoef(ls);
            if (coef != 0)
                throw(std::runtime_error("This function can be only called if there is an intersection point"));

            Direction<T, PLANE_DIMENSION> dir = ls.get_begin().length_to(le.get_end());
            Direction<T, EQUATION_VECTOR_DIM> adaptedDir(dir[0], dir[1], dir[2], 0);

            double denominateur = l.dot(adaptedDir);

            if (denominateur == 0)
                throw (std::runtime_error("Bad state for the intersection call"));

            double t = coef / denominateur;

            return s + (t * dir);
        }

        /** \brief
         *
         * \param ls LineSegment&
         * \return double
         */
        double intersectCoef(LineSegment<T, PLANE_DIMENSION> &ls)
        {
            Point<T, EQUATION_VECTOR_DIM> s(ls.get_begin()[0], ls.get_begin()[1], ls.get_begin()[2], 0);

            return equation.dot(s);
        }

        friend std::ostream& operator<<(std::ostream& out, Plane &p);
    };

    template<class T>
    std::ostream& operator<<(std::ostream& out, Plane<T> &p)
    {
        out << "Point : " << p.p << " direction : " << p.n << "Equation : " << p.equation;
    }
}
