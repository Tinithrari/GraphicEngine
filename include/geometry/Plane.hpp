#pragma once

#include "geometry/LineSegment.hpp"
#include "geometry/Point.hpp"
#include "geometry/Direction.hpp"

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
        Direction<T, PLANE_DIMENSION> n; /**< Normale du plan */
    public:

        /** \brief Construit un plan à l'aide du point par lequel il passe et un vector normal
         *
         * \param p Le point par lequel le point passe
         * \param n Le vecteur normal perpendiculaire au point p
         * \return Plane(Point<T, PLANE_DIMENSION> &p, Direction<T, PLANE_DIMENSION> &n):
         */
        Plane(const Point<T, PLANE_DIMENSION> &p, const Direction<T, PLANE_DIMENSION> &n) : p(p), n(n)
        {
            if (! this->n.is_unit())
                this->n = Direction<T, PLANE_DIMENSION>(this->n.to_unit());
            
            equation[0] = this->n[0];
            equation[1] = this->n[1];
            equation[2] = this->n[2];
            equation[3] = -(this->n * p);
        }

        /** \brief Calcule la position du point par rapport au point
         *
         * \param p Le point à tester
         * \return n < 0 si le point est derriere, n = 0 si le point appartient au plan, n > 0 si le point est devant
         */
        double positionFrom(Point<T, PLANE_DIMENSION> &pt) const
        {
            return (n * pt) + equation[3];
        }

        /** \brief Verifie si le plan est devant le point passé en paramètre
         *
         * \param p Le point dont on souhaite connaitre la disposition par rapport au plan
         * \return true si le plan est devant le plan, false sinon
         */
        bool isFrontOf(Point<T, PLANE_DIMENSION> &pt) const
        {
            return positionFrom(pt) < 0;
        }

        /** \brief Calcule le point d'intersection entre un segment et un point
         *
         * \param ls Le segement de droite
         * \return Le point d'intersection entre le plan et la droite
         */
        Point<T, PLANE_DIMENSION> intersec(LineSegment<T, PLANE_DIMENSION> &ls) const
        {
            double coef = intersectCoef(ls);
            if (coef == 0)
                throw(std::runtime_error("This function can be only called if there is an intersection point"));
            
            Point<T, EQUATION_VECTOR_DIM> s{ls.get_begin()[0], ls.get_begin()[1], ls.get_begin()[2], 1};
            Direction<T, PLANE_DIMENSION> dir {ls.get_begin().length_to(ls.get_end())};
            Direction<T, EQUATION_VECTOR_DIM> adaptedDir{dir[0], dir[1], dir[2], T()};

            Point<T, EQUATION_VECTOR_DIM> pt = s + (coef * adaptedDir);

            return Point<T, PLANE_DIMENSION>{pt[0], pt[1], pt[2]};
        }

        /** \brief
         *
         * \param ls LineSegment&
         * \return double
         */
        double intersectCoef(LineSegment<T, PLANE_DIMENSION> &ls) const
        {
            Point<T, EQUATION_VECTOR_DIM> s{ls.get_begin()[0], ls.get_begin()[1], ls.get_begin()[2], 1};
            Direction<T, PLANE_DIMENSION> vDim3{ls.get_begin().length_to(ls.get_end())};
            Direction<T, EQUATION_VECTOR_DIM> v = {vDim3[0], vDim3[1], vDim3[2], T()};
            
            if ((equation * v) == 0)
                return (equation * s == 0 ? 1.d : 0.d);

            return -((equation * s) / (equation * v));
        }

        template <class U>
        friend std::ostream& operator<<(std::ostream& out, Plane<U> &p);
    };

    template<class T>
    std::ostream& operator<<(std::ostream& out, const Plane<T> &p)
    {
        out << "Point : " << p.p << " direction : " << p.n << " Equation : " << p.equation;
        return out;
    }
}
