#pragma once

#include "geometry/Point.hpp"
#include "geometry/Plane.hpp"

#include <stdexcept>
#include <iostream>

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
        /** \brief Constructeur par défaut
         *
         */
        Sphere() : center(), radius(0)
        {

        }

        /** \brief Construit une sphere avec son centre et son rayon
         *
         * \param center Le centre de la sphere
         * \param radius le rayon de la sphere
         * \return Sphere(Point &center, float radius):
         */
        Sphere(Point<T, SPHERE_DIMENSION> &center, float radius) : center(center)
        {
            if (radius < 0)
                throw std::invalid_argument("The radius must be postive");

            this->radius = radius;
        }

        /** \brief Verifie si la sphere est derriere un plan
         *
         * \param p Le plan à verifier
         * \return true si la sphere est derriere le plan, false sinon
         */
        bool behind(Plane &p)
        {
            return p.positionFrom(center) < 0;
        }

        /** \brief Vérifie si un point est contenu dans la sphere
         *
         * \param p Le point à verifier
         * \return true si le point est dans la sphere, false sinon
         */
        bool contains(Point<T, SPHERE_DIMENSION> &p)
        {
            return (p[0] >= center[0] - radius && p[0] <= center[0] + radius) && (p[1] >= center[1] - radius && p[1] <= center[1] + radius) && (p[2] >= center[2] - radius && p[2] <= center[2] + radius);
        }

        /** \brief Verifie si la sphere ne contient pas de coordonnées invalides
         *
         * \return true si les coordonnées sont invalides, false sinon
         */
        bool is_null()
        {
            return center.is_null() || std::isnan(radius);
        }

        /** \brief Accesseur pour le centre de la sphere
         *
         * \return Le centre de la sphere
         */
        Point<T, SPHERE_DIMENSION> getCenter() const
        {
            return center;
        }


        /** \brief Accesseur pour le centre de la sphere
         *
         * \return Le centre de la sphere
         */
        void setCenter(Point<T, SPHERE_DIMENSION> &p)
        {
            center = p;
        }

        /** \brief Accesseur pour le rayon de la sphere
         *
         * \return Le rayon de la sphere
         */
        float getRadius() const
        {
            return radius;
        }

        /** \brief Accesseur pour le rayon de la sphere
         *
         * \return Le rayon de la sphere
         */
        void setRadius(float r)
        {
            radius = r;
        }
    };

    template<class T>
    std::ostream& operator<<(std::ostream& out, Sphere<T> &s)
    {
        out << "Centre : " << s.getCenter() << " rayon : " << s.getRadius();
        return out;
    }
}
