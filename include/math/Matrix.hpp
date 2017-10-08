#pragma once

#include "math/Vector.hpp"

#include <array>
#include <exception>
#include <cmath>
#include <iostream>

using namespace std;

namespace math
{
    template<class T, unsigned int n, unsigned int m>
    class Matrix
    {
    private:
        array<array<T, m>, n> mat;
        /*
        bool isReversable() const
        {
            return false;
        }
        */
    public:
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

        Matrix(array<array<T, m>, n> &a): mat(a) {}

        ~Matrix() {}
        T at(const unsigned int i, const unsigned int j) const
        {
            if (i >= n || j >= m)
                throw ("Index out of the matrix");
            
            return mat[i][j];
        }

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

        bool is_ortho() const
        {
            Matrix<float, n, m> rev;
            if (n != m)
                throw "The matrix must be squared to check if it's orthogonal";

            rev = inverse();

            return rev == transpose();
        }

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

        array<T, m> operator[](const int i) const
        {
            return mat[i];
        }

        array<T, m> &operator[](const int i)
        {
            return mat[i];
        }

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