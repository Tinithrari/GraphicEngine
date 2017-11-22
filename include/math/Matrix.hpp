#pragma once

#include "math/Vector.hpp"

#include <array>
#include <exception>
#include <cmath>
#include <iostream>

using namespace std;

namespace math
{
    /**
     * @class Matrix
     * @author xavier
     * @date 22/11/17
     * @file Matrix.hpp
     * @brief Utilitaire pour la manipulation de matrice
     */
    template<class T, unsigned int n, unsigned int m>
    class Matrix
    {
    private:
        array<array<T, m>, n> mat;

    public:
        /**
         * @brief Construit une matrice nulle
         * @return La matrice nulle de dimension n, m
         */
        Matrix() 
        {
            if (n == 0 || m == 0)
                throw "Incorrect size";
            
            for (int i = 0; i < n; ++i )
            {
                for (int j = 0; j < m; ++j)
                {
                    mat[i][j] = T();
                }
            }
        }
        
        /**
         * @brief Constructeur par recopie
         * @param m2 La matrice a recopier
         * @return Une copie de la matrice m2
         */
        Matrix(const Matrix &m2)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    mat[i][j] = m2[i][j];
                }
            }
        }

        /**
         * @brief Initialise une matrice a l'aide d'un tableau de tableau
         * @return La matrice equivalente au tableau passe en parametre
         */
        Matrix(const initializer_list<initializer_list<T>> &table)
        {
            int i = 0;
            for (const initializer_list<T> *liste = table.begin(); liste != table.end(); ++liste, ++i)
            {
                int j = 0;
                for (const T* element = liste->begin(); element != liste->end(); ++element, ++j)
                {
                    mat[i][j] = *element;
                }
            }
        }

        /**
         * @brief Constructeur avec la structure de la STL
         * @param a le tableau de tableau de la STL
         */
        Matrix(array<array<T, m>, n> &a): mat(a) {}

        /**
         * @brief Destructeur
         */
        ~Matrix() {}
        
        /**
         * @brief Obtient la valeur situé à la coordonnées i, j
         * @param i La coordonnées i de la matrice
         * @param j La coordonnées j de la matrice
         * @return La valeur situé à la coordonnées i, j
         */
        T at(const unsigned int i, const unsigned int j) const
        {
            if (i >= n || j >= m)
                throw ("Index out of the matrix");
            
            return mat[i][j];
        }

        /**
         * @brief Calcule la matrice inverse
         * @return La matrice inverse de la matrice courante
         */
        Matrix<float, n, m> inverse() const
        {

            if (n != m)
                throw "La matrice n'est pas carré";
    
            Matrix<float, n, m> copie;
            Matrix<float, n, m> id(copie.identite());

            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    copie[i][j] = (float) (mat[i][j]);

            int r = -1;
        
            for (int j = 0; j < m; ++j)
            {
                int k = -1;

                // Recherche du maximum
                for (int i = (++r); i < n; ++i)
                {
                    if (k == -1 && copie[i][j] != 0)
                        k = i;
                    else if (k != -1 && abs(copie[i][j]) > abs(copie[k][j]))
                        k = i;
                }

                if (k == -1)
                    throw "Matrix not inversible";

                float mkj = copie[k][j];

                // Division de la ligne k par M(k,j)
                for (int i = 0; i < m; ++i)
                {
                    copie[k][i] /= mkj;
                    id[k][i] /= mkj;
                }
                
                // Echange des lignes si nécessaire
                if (k != r)
                {
                    swap(copie[k], copie[r]);
                    swap(id[k], id[r]);
                }

                // Simplification des autres lignes
                for (int i = 0; i < n; ++i)
                {
                    const float mij = copie[i][j];
                    // Pour éviter un traitement inutile
                    if (i != r)
                    {
                        // Soustraction de la ligne i par la ligne r multiplié par M(i,j)
                        for (int l = 0; l < m; ++l)
                        {
                            copie[i][l] -= (copie[r][l] * mij);
                            id[i][l] -= (id[r][l] * mij);
                        }
                    }
                }
            }
    
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    id[i][j] = ROUND(id[i][j]);

            return id;
        }

        /**
         * @brief Calcule la matrice identite de dimension n, m
         * @return La matrice identite de dimension n, m
         */
        Matrix identite() const
        {
            if (n != m)
                throw "La matrice n'est pas carre";
            Matrix id;
        
            for (int i = 0; i < n; ++i)
            {
                id[i][i] = 1;
            }
        
            return id;
        }

        /**
         * @brief Verifie si la matrice ne contient pas de coordonnées invalides
         * @return true si une des coordonnées est invalide, false sinon
         */
        bool is_null() const
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    if (isnan(mat[i][j]))
                        return true;
                }
            }
            return false;
        }
        
        /**
         * @brief Verifie si la matrice est orthonormée
         * @return True si la matrice est orthonormée, false sinon
         */
        bool is_ortho() const
        {
            Matrix<float, n, m> rev;
            if (n != m)
                throw "The matrix must be squared to check if it's orthogonal";

            rev = inverse();

            return rev == transpose();
        }

        /**
         * @brief Calcule la transpose de la matrice
         * @return La transpose de la matrice courante
         */
        Matrix<T, m ,n> transpose() const
        {
            Matrix<T, m, n> res;

            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    res[i][j] = mat[j][i];
                }
            }

            return res;
        }

        /**
         * @brief Accede à la ligne i de la matrice
         * @param i l'index de la ligne voulu
         * @return La i-eme ligne
         */
        array<T, m> operator[](const int i) const
        {
            return mat[i];
        }

        /**
         * @brief Permet d'obtenir une reference sur la ieme ligne
         * @param i l'index de la ligne
         * @return Une reference sur la ieme ligne
         */
        array<T, m> &operator[](const int i)
        {
            return mat[i];
        }

        /**
         * @brief Additionne deux matrice
         * @param m2 la matrice a additionner a la matrice courante
         * @return La matrice resultant de la matrice courante
         */
        Matrix operator+(const Matrix &m2) const
        {
            Matrix res;

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    res[i][j] = mat[i][j] + m2[i][j];
                }
            }
            return res;
        }

        /**
         * @brief Operateur d'affectation
         * @param a le tableau de tableau a affecter a la matrice
         */
        Matrix &operator =(const array<array<T, m>, n> &a)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    mat[i][j] = a[i][j];
                }
            }
            return *this;
        }

        /**
         * @brief Addition directement une matrice a la matrice courante
         * @param m2 la matrice a ajouter a la matrice courante
         */
        Matrix &operator+=(const Matrix &m2)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    mat[i][j] += m2[i][j];
                }
            }
        }

        /**
         * @brief Multiplie un vecteur a la matrice courante
         * @param v le vecteur a multiplier a la matrice courante
         */
        Matrix<T, n, 1> operator*(const Vector<T, m> &v) const
        {
            Matrix<T, n, 1> res;
             
            for (int i = 0; i < n; ++i)
            {
                res[i][0] = 0;
                for (int j = 0; j < m; ++j)
                {
                    res[i][0] += mat[i][j] * v[j];
                }
            }
            return res;
        }

        /**
         * @brief Multiplication de matrice avec un scalaire
         * @param scalar le scalaire a multiplier a la matrice
         * @return La matrice resultant de la multiplication
         */
        Matrix operator*(const float scalar) const
        {
            Matrix res;

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    res[i][j] = mat[i][j] * scalar;
                }
            }

            return res;
        }

        /**
         * @brief Multiplication de deux matrice non identique
         * @param m2 La matrice a multiplier a la matrice courante
         * @return La matrice resultant de la multiplication
         */
        template<unsigned int o>
        Matrix<T, n, o> operator*(const Matrix<T, m, o> &m2) const
        {
            Matrix res;
            
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < o; ++j)
                {
                    for (int k = 0; k < m; ++k)
                    {
                       res[i][j] += mat[i][k] * m2[k][o];
                    }
                }
            }
            
            return res;
        }

        /**
         * @brief Multiplie directement la matrice courante a un scalaire
         * @param scalar le scalaire a multiplier a la matrice courante
         */
        Matrix operator*=(const float scalar)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    mat[i][j] *= scalar;
                }
            }
        }

        /**
         * @brief Verifie si une matrice est égale a la matrice courante
         * @param m2 la matrice a comparer
         * @return true si les deux matrices sont egales, false sinon
         */
        bool operator==(const Matrix &m2) const
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    if (mat[i][j] != m2[i][j])
                        return false;
                }
            }

            return true;
        }

        /**
         * @brief Compare une matrice d'un autre type avec la matrice courante
         * @param m2 la matrice a comparer
         * @return true si les matrices sont egales, false sinon
         */
        template <class U>
        bool operator==(const Matrix<U, n, m> &m2) const
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    if (mat[i][j] != (T) m2[i][j])
                        return false;
                }
            }

            return true;
        }
    };

    /**
     * @brief Verification de l'egalite entre deux matrices
     * @param m1 Une matrice
     * @param m2 Une matrice
     * @return true si m1=m2, false sinon
     */
    template <class T, class U, unsigned int n, unsigned int m>
    bool operator==(const Matrix<T, n, m> &m1, const Matrix<U, n, m> &m2)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (m1[i][j] != (T) (m2[i][j]))
                    return false;
            }
        }

        return true;
    }

    /**
     * @brief Produit d'une matrice avec un scalaire
     * @param scalar le scalaire a multiplier a la matrice
     * @param matrice La matrice a multiplier
     * @return la matrice resultant de la multplication
     */
    template<class T, unsigned int n, unsigned int m>
    Matrix<T, n, m> &operator*(float scalar, Matrix<T, n, m> &matrice)
    {
        Matrix<T, n, m> res;
        
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                res[i][j] = matrice[i][j] * scalar;
            }
        }
        
        return res;
    }

    /**
     * @brief Operation d'affichage pour la matrice
     * @param out le flux de sortie
     * @param matrice la matrice a afficher
     * @return le flux pour enchainer les affichages
     */
    template<class T, unsigned int n, unsigned int m>
    ostream &operator<<(ostream &out, const Matrix<T, n, m> &matrice)
    {
        for (int i = 0; i < n; ++i)
        {
            cout << "(";
            for (int j = 0; j < m; ++j)
            {
                out << (j != 0 ? ", " : "") << matrice[i][j];
            }
            out << ")";
            if (i != n - 1)
                out << endl;
        }
        return out;
    }

    using Mat44r = Matrix<real, 4, 4>;

    static const Matrix<int, 4, 4> Identity4i({{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}});
    static const Matrix<float, 4, 4> Identity4r({{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}});
}