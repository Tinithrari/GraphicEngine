#pragma once

#include "geometry/Point.hpp"

#include <iostream>

/**
 * @namespace geometry
 *
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur
 */
namespace geometry
{
    /** \brief Un segment de droite
     */
    template<class T, unsigned int N>
    class LineSegment
    {
    private:
        Point<T, N> begin; /**< Le point de depart du segment*/
        Point<T, N> end; /**< Le point d'arrivee du segment*/
    public:
        /** \brief Construit un segment à partir de deux points
         *
         * \param begin Le point de départ du segment
         * \param end Le point d'arrivée du segment
         */
        LineSegment(Point<T, N> begin, Point<T, N> end) : begin(begin), end(end)
        {

        }
        
        /**
         * @brief Constructeur par recopie
         * @param ls
         */
        LineSegment(const LineSegment& ls) : begin(ls.begin), end(ls.end)
        {
            
        }

        /** \brief Accesseur pour le point de départ
         *
         * \return Le point de départ
         */
        Point<T, N> get_begin() const
        {
            return begin;
        }

        /** \brief Accesseur pour le point d'arrivée
         *
         * \return Le point d'arrivée
         */
        Point<T, N> get_end() const
        {
            return end;
        }

        /** \brief Vérifie si le segment contient des données invalides
         *
         * \return true si des données invalides sont présentes, false sinon
         */
        bool is_null() const
        {
            return begin.is_null() || end.is_null();
        }
        
        bool operator==(const LineSegment &ls) const
        {
            return begin == ls.get_begin() && end == ls.get_end();
        }
    };

    template<class T, unsigned int N>
    std::ostream& operator<<(std::ostream& out, const LineSegment<T, N> &ls)
    {
        out << "Begin : " << ls.get_begin() << ", end : " << ls.get_end();
    }
}
