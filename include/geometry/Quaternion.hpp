#pragma once

#include "math/Vector.hpp"
#include "Direction.hpp"

#include <cmath>
#include <iostream>

#define PI 3.14159265358 /**< Valeur approché du nombre PI */
#define RADIAN_COEFFICIENT 180 /**< Coefficient pour transformer les degrés en radiant */
#define deg2rad(x) (((x) / RADIAN_COEFFICIENT) * PI) /**< Convertit les degrés en radiant */

#define QUATERNION_DIMENSION 4 /**< Nombre de membre dans le quaternion */
#define IMAGINARY_PART_DIMENSION 3 /**< Nombre de membre pour la partie imaginaire du quaternion */

/**
 * @namespace geometry
 *
 * Espace de nommage contenant les objets géométriques nécessaire pour la réalisation du moteur
 */
namespace geometry
{
    /**
     * @class Quaternion
     *
     * Objet mathematiques permettant de traiter les rotations complexes
     */
    template <class T>
    class Quaternion
    {
    private:
        math::Vector<T, QUATERNION_DIMENSION> members; /**< Les membres du quaternion  */
    public:

        /** \brief Construit un quaternion à partir de ses membres
         *
         * \param members Les membres du quaternion (reel, im1, im2, im3)
         */
        Quaternion(Vector<T, QUATERNION_DIMENSION> &members) : members(members)
        {

        }

        /** \brief Définit
         *
         * \param rotation l'angle de rotation
         * \param dir La direction vers laquelle doit s'effectuer la rotation
         *
         */
        Quaternion(float rotation, Direction<T, 3> &dir)
        {
            double sinAngle = std::sin(deg2rad(rotation / 2));

            members[0] = std::cos(deg2rad(rotation / 2));
            members[1] = dir[0] * sinAngle;
            members[2] = dir[1] * sinAngle;
            members[3] = dir[2] * sinAngle;
        }

        /** \brief Calcul le conjugué du quaternion
         *
         * \return Le conjugué du quaternion
         *
         */
        Quaternion conjugate() const
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(members[0], -members[1], -members[2], -members[3]));
        }

        /** \brief Calcule la norme du quaternion
         *
         * \return La norme du quaternion
         */
        float norm() const
        {
            return members.norm();
        }

        /** \brief Permet d'accéder à la partie imaginaire du quaternion
         *
         * \return La partie imaginaire du quaternion
         */
        math::Vector<T, IMAGINARY_PART_DIMENSION> im() const
        {
            Vector<T, IMAGINARY_PART_DIMENSION> imag(members[1], members[2], members[3]);
        }

        /** \brief Calcul l'inverse du quaternion
         *
         * \return L'inverse du quaternion
         */
        Quaternion inverse() const
        {
            float theNorm = norm();
            return conjugate() / (theNorm * theNorm);
        }

        /** \brief Retourne la partie réelle du quaternion
         *
         * \return La partie réelle du quaternion
         */
        T re() const
        {
            return members[0];
        }

        math::Vector<T, QUATERNION_DIMENSION> getMembers()
        {
            return members;
        }

        /** \brief Retourne une copie normalisé du quaternion
         *
         * \return Une copie du quaternion normalisé
         */
        Quaternion to_norm() const
        {
            return Quaternion(members.to_unit());
        }

        /** \brief Additione un scalaire au quaternion
         *
         * \param scalar Le scalaire a ajouter au quaternion
         * \return Le quaternion resultant de l'operation
         */
        Quaternion operator+ (T scalar) const
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(members[0] + scalar,
                                                                    members[1],
                                                                    members[2],
                                                                    members[3]));
        }

        /** \brief Addition de deux quaternion
         *
         * \param q Le quaternion a additioner au quaternion courant
         * \return  Le quaternion résultant du quaternion courant
         */
        Quaternion operator+ (Quaternion &q) const
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(members[0] + q.members[0],
                                                                    members[1] + q.members[1],
                                                                    members[2] + q.members[2],
                                                                    members[3] + q.members[3]));
        }

        /** \brief Soustrait un scalaire au quaternion
         *
         * \param scalar Le scalaire a asoustraire au quaternion
         * \return Le quaternion resultant de l'operation
         */
        Quaternion operator- (T scalar) const
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(members[0] - scalar,
                                                                    members[1],
                                                                    members[2],
                                                                    members[3]));
        }

        /** \brief Soustraction de deux quaternion
         *
         * \param q Le quaternion a soustraire au quaternion courant
         * \return  Le quaternion résultant de la soustraction
         */
        Quaternion operator- (Quaternion &q) const
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(members[0] - q.members[0],
                                                                    members[1] - q.members[1],
                                                                    members[2] - q.members[2],
                                                                    members[3] - q.members[3]));
        }

        /** \brief Négation d'un quaternion
         *
         * \return La négation du quaternion
         */
        Quaternion operator- () const
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(-members[0], -members[1], -members[2], -members[3]));
        }

        /** \brief Multiplication d'un quaternion avec un scalaire
         *
         * \param scalar le scalaire a multiplier
         * \return Le quaternion resultant de l'operation
         */
        Quaternion operator* (T scalar) const
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(members[0] * scalar,
                                                                    members[1] * scalar,
                                                                    members[2] * scalar,
                                                                    members[3] * scalar));
        }

        /** \brief Multiplication de deux quaternion
         *
         * \param q Le quaternion a multiplier
         * \return Le quaternion resultant de l'operation
         */
        Quaternion operator* (Quaternion& q) const
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(members[0] * q.members[0] - members[1] * q.members[1] - members[2] * q.members[2] - members[3] * q.members[3],
                                                                    members[0] * q.members[1] + members[1] * q.members[0] + members[2] * q.members[3] + members[3] * q.members[2],
                                                                    members[0] * q.members[2] - members[1] * q.members[3] + members[2] * q.members[0] + members[3] * q.members[1],
                                                                    members[0] * q.members[3] + members[1] * q.members[2] - members[2] * q.members[1] + members[3] * q.members[0]));
        }


        /** \brief Division d'un quaternion avec un scalaire
         *
         * \param scalar le scalaire a diviser
         * \return  Le quaternion resultant de l'operation
         */
        Quaterion operator/ (T scalar)
        {
            return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(members[0] / scalar,
                                                                    members[1] / scalar,
                                                                    members[2] / scalar,
                                                                    members[3] / scalar));
        }

        /** \brief Additione un scalaire au quaternion
         *
         * \param scalar Le scalaire a ajouter au quaternion
         * \return Le quaternion resultant de l'operation
         */
        Quaternion& operator+= (T scalar)
        {
            members[0] += scalar;

            return *this;
        }

        /** \brief Addition de deux quaternion
         *
         * \param q Le quaternion a additioner au quaternion courant
         * \return  Le quaternion résultant du quaternion courant
         */
        Quaternion& operator+= (Quaternion &q)
        {
            members[0] += q.members[0];
            members[1] += q.members[1];
            members[2] += q.members[2];
            members[3] += q.members[3];

            return *this;
        }

        /** \brief Soustrait un scalaire au quaternion
         *
         * \param scalar Le scalaire a asoustraire au quaternion
         * \return Le quaternion resultant de l'operation
         */
        Quaternion& operator-= (T scalar)
        {
            members[0] -= scalar;

            return *this;
        }

        /** \brief Soustraction de deux quaternion
         *
         * \param q Le quaternion a soustraire au quaternion courant
         * \return  Le quaternion résultant de la soustraction
         */
        Quaternion& operator-= (Quaternion &q)
        {
            members[0] -= q.members[0];
            members[1] -= q.members[1];
            members[2] -= q.members[2];
            members[3] -= q.members[3];

            return *this;
        }

        /** \brief Multiplication d'un quaternion avec un scalaire
         *
         * \param scalar le scalaire a multiplier
         * \return Le quaternion resultant de l'operation
         */
        Quaternion& operator*= (T scalar)
        {
            members[0] *= scalar;
            members[1] *= scalar;
            members[2] *= scalar;
            members[3] *= scalar;

            return *this;
        }

        /** \brief Multiplication de deux quaternion
         *
         * \param q Le quaternion a multiplier
         * \return Le quaternion resultant de l'operation
         */
        Quaternion& operator*= (Quaternion& q)
        {
            math::Vector<T, QUATERNION_DIMENSION> newMembers(members[0] * q.members[0] - members[1] * q.members[1] - members[2] * q.members[2] - members[3] * q.members[3],
                                                             members[0] * q.members[1] + members[1] * q.members[0] + members[2] * q.members[3] + members[3] * q.members[2],
                                                             members[0] * q.members[2] - members[1] * q.members[3] + members[2] * q.members[0] + members[3] * q.members[1],
                                                             members[0] * q.members[3] + members[1] * q.members[2] - members[2] * q.members[1] + members[3] * q.members[0]);

            members = newMembers;
            return *this;
        }

        friend Quaternion operator+(T scalar, Quaternion<T> &q);
        friend Quaternion operator-(T scalar, Quaternion<T> &q);
        friend std::ostream& operator<<(std::ostream &out, Quaternion<T> &q);
    };

    template <class T>
    Quaternion operator+(T scalar, Quaternion<T> &q)
    {
        return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(q.members[0] + scalar,
                                                                q.members[1],
                                                                q.members[2],
                                                                q.members[3]));
    }

    template<class T>
    Quaternion operator-(T scalar, Quaternion<T> &q)
    {
        return Quaternion(math::Vector<T, QUATERNION_DIMENSION>(q.members[0] - scalar,
                                                                q.members[1],
                                                                q.members[2],
                                                                q.members[3]));
    }

    template<class T>
    std::ostream& operator<< (std::ostream &out, Quaternion<T> &q)
    {
        out << "Quaternion(" << q.members[0] << ", " << q.members[1] << ", " << q.members[2] << ", " << q.members[3] << ")";
        return out;
    }
}
