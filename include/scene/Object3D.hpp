#pragma once

#include "geometry/Point.hpp"
#include "geometry/Triangle.hpp"
#include "geometry/Sphere.hpp"

#include <stdexcept>
#include <vector>
#include <algorithm>

namespace scene
{
    class Object3D
    {
    private:
        string nom; /**< Nom de l'objet */
        math::Vector<float, 3> position; /**< Position de l'objet */
        std::vector<geometry::Point<float, 3>> vertex; /**< Sommets de l'objet */
        std::vector<geometry::Triangle<float>> faces; /**< Faces de l'objet */

        /** \brief Calcul une sphere de base pour l'algorithme de Ritter
         *
         * \return une sphere de base pour l'algorithme de Ritter
         */
        Sphere sphereFromDistantPoint() const
        {
            int minx = 0, miny = 0, minz = 0, maxx = 0, maxy = 0; maxz = 0;

            for (int i = 0; i < vertex.size(); ++i)
            {
                if (vertex[i] < vertex[minx])
                    minx = i;
                if (vertex[i] < vertex[miny])
                    miny = i;
                if (vertex[i] < vertex[minz])
                    minz = i;
                if (vertex[i] > vertex[maxx])
                    maxx = i;
                if (vertex[i] > vertex[maxy])
                    maxy = i;
                if (vertex[i] > vertex[maxz])
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

            geometry::Point<float, 3> center{ (vertex[min] + vertex[max]) * 0.5f };
            geometry::Sphere<float> s{ center, std::sqrt( dot( pt[max] - center, pt[max] - center ) ) }
        }

        /** \brief Agrandit la sphere de collision afin qu'elle englobe la totalité des points de l'objet
         *
         * \param s Sphere& La sphere a agrandir
         */
        void growSphere(Sphere &s)
        {
            for (int i = 0; i < n; ++i)
            {
                math::Vector<float, 3> vec = vertex[i] - s.getCenter();
                float dist2 = dot(d, d);

                if (dist2 > s.getRadius() * s.getRadius())
                {
                    float dist = std::sqrt(dist2);
                    float newRadius = (s.getRadius() + dist) * 0.5f;
                    float k = (newRadius - s.getRadius()) / dist;

                    s.setRadius(newRadius);
                    s.setCenter(s.getCenter() (+ dist * k));
                }
            }
        }

    public:

        /** \brief Construit un objet à l'aide de ces points
         *
         * \param vertex Points de l'objet
         * \return L'objet3D composé de points
         */
        Object3D(std::vector<geometry<float, 3>> &vertex) : vertex(vertex)
        {

        }

        /** \brief Calcule la sphere englobante de l'objet en utilisant l'algorithme de Ritter
         *
         * \return geometry::Sphere
         */
        geometry::Sphere bsphere() const
        {
            Sphere s = sphereFromDistantPoint();
            growSphere(s);
            return s;
        }

        /** \brief Obtient une face spécifique
         *
         * \param n L'index de la face
         * \return La face correspondant à l'index
         */
        geometry::Triangle<float, 3> face(const unsigned int n) const
        {
            return geometry::Triangle();
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

            geometry::Triangle t{vertex[f1], vertex[f2], vertex[f3]};

            faces.add(t);
        }

        /** \brief Supprime une face de l'objet
         *
         * \param n L'index de la face  à supprimer
         */
        void remove_face(unsigned int n)
        {
            if (n > face.size())
                throw(std::invalid_argument("The index is out of bounds"));

            std::swap(vertex[n], vertex[vertex.size() - 1]);
            vertex.pop_back();
        }
    };
}
