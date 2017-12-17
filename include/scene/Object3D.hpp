#pragma once

#include "geometry/Point.hpp"
#include "geometry/Triangle.hpp"
#include "geometry/Sphere.hpp"

#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace math;
using namespace geometry;

namespace scene
{
    class Object3D
    {
    private:
        string nom; /**< Nom de l'objet */
        Vector<float, 3> position; /**< Position de l'objet */
        std::vector<Point<float, 3>> vertex; /**< Sommets de l'objet */
        std::vector<Triangle<float>> faces; /**< Faces de l'objet */

        /** \brief Calcul une sphere de base pour l'algorithme de Ritter
         *
         * \return une sphere de base pour l'algorithme de Ritter
         */
        Sphere<float> sphereFromDistantPoint() const
        {
            int minx = 0, miny = 0, minz = 0, maxx = 0, maxy = 0, maxz = 0;

            for (int i = 0; i < vertex.size(); ++i)
            {
                if (vertex[i][0] < vertex[minx][0])
                    minx = i;
                if (vertex[i][1] < vertex[miny][1])
                    miny = i;
                if (vertex[i][2] < vertex[minz][2])
                    minz = i;
                if (vertex[i][0] > vertex[maxx][0])
                    maxx = i;
                if (vertex[i][1] > vertex[maxy][1])
                    maxy = i;
                if (vertex[i][2] > vertex[maxz][2])
                    maxz = i;
            }

            float dist2x = dot(vertex[maxx] - vertex[minx], vertex[maxx] - vertex[minx]);
            float dist2y = dot(vertex[maxy] - vertex[miny], vertex[maxy] - vertex[miny]);
            float dist2z = dot(vertex[maxz] - vertex[minz], vertex[maxz] - vertex[minz]);

            int min = minx, max = maxx;

            if (dist2y > dist2x && dist2y > dist2z)
            {
                min = miny;
                max = maxy;
            }

            if (dist2z > dist2x && dist2z > dist2y)
            {
                min = minz;
                max = maxz;
            }

            Point<float, 3> center((vertex[min] + vertex[max]) * 0.5f);
            return Sphere<float>( center, std::sqrt( dot( vertex[max] - center, vertex[max] - center ) ) );
        }

        /** \brief Agrandit la sphere de collision afin qu'elle englobe la totalité des points de l'objet
         *
         * \param s Sphere& La sphere a agrandir
         */
        void growSphere(Sphere<float> &s) const
        {
            for (int i = 0; i < vertex.size(); ++i)
            {
                math::Vector<float, 3> vec = vertex[i] - s.getCenter();
                float dist2 = dot(vec, vec);

                if (dist2 > s.getRadius() * s.getRadius())
                {
                    float dist = std::sqrt(dist2);
                    float newRadius = (s.getRadius() + dist) * 0.5f;
                    float k = (newRadius - s.getRadius()) / dist;

                    s.setRadius(newRadius);
                    s.setCenter(s.getCenter() + (vec * k));
                }
            }
        }

    public:

        Object3D()
        {
        }

        Object3D(const Object3D &o) : vertex(o.vertex), faces(o.faces)
        {
            
        }

        /** \brief Construit un objet à l'aide de ces points
         *
         * \param vertex Points de l'objet
         * \return L'objet3D composé de points
         */
        Object3D(std::vector<Point<float, 3>> &vertex) : vertex(vertex)
        {

        }

        /** \brief Calcule la sphere englobante de l'objet en utilisant l'algorithme de Ritter
         *
         * \return La sphere englobante
         */
        Sphere<float> bsphere() const
        {
            Sphere<float> s = sphereFromDistantPoint();
            growSphere(s);
            return s;
        }

        /** \brief Obtient une face spécifique
         *
         * \param n L'index de la face
         * \return La face correspondant à l'index
         */
        Triangle<float> face(const unsigned int n) const
        {
            if (n >= faces.size())
                throw(std::invalid_argument("index out of bound"));

            return faces[n];
        }

        /** \brief Retourne le nombre de faces de la structure
         *
         * \return Le nombre de faces de l'objet
         */
        unsigned int num_faces() const
        {
            return faces.size();
        }

        /** \brief Ajoute une face
         *
         * \param f1 index du premier point
         * \param f2 index du second point
         * \param f3 index du troisieme point
         */
        void add_face(unsigned int f1, unsigned int f2, unsigned int f3)
        {
            if (f1 > vertex.size() || f2 > vertex.size() || f3 > vertex.size())
                throw(std::invalid_argument("One of the argument is out of bound"));

            Triangle<float> t(vertex[f1], vertex[f2], vertex[f3]);

            faces.push_back(t);
        }

        /** \brief Supprime une face de l'objet
         *
         * \param n L'index de la face  à supprimer
         */
        void remove_face(unsigned int n)
        {
            if (n >= faces.size())
                throw(std::invalid_argument("The index is out of bounds"));

            std::swap(faces[n], faces[faces.size() - 1]);
            faces.pop_back();
        }
    };
}
