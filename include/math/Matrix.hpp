#pragma once

#include "math/Vector.hpp"

#include <array>
#include <exception>
#include <iostream>

#ifndef REAL_TYPE
typedef float real;
#endif

using namespace std;

namespace math
{
    template<class T, unsigned int n, unsigned int m>
    class Matrix
    {
    private:
        array<array<T, m>, n> mat;
        bool isReversable() const
        {
            return false;
        }

        Matrix<T, n, n> identite()
        {
            math::Matrix<T, n, n> id;
        
            for (int i = 0; i < n; ++i)
            {
                id[i][i] = 1;
            }
        
            return id;
        }
    public:
        Matrix() 
        {
            if (n == 0 || m == 0)
                throw "Incorrect size";
            
            for (int i = 0; i < n; i++ )
            {
                for (int j = 0; j < m; j++)
                {
                    mat[i][j] = NAN;
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

        Matrix reverse() const
        {

            if (n != m)
            throw "La matrice n'est pas carré";
    
            Matrix<T, n, n> id = identite();
            Matrix<T, n, m> copie = *this;
            int pivot = -1;
        
            for (int j = 0; j < m; ++j)
            {
                int max = -1;
                float diviseur;
                for (int i = (pivot++) + 1; i < n; ++i)
                {
                    if (copie[i][j] != 0 && abs(copie[i][j]) > abs(copie[j][max]))
                        max = j;
                }
        
                if (max == -1)
                    throw "Matrix not reversable";
        
                diviseur = (float) (1 / copie[max][j]);
                for (int i = 0; i < m; ++i)
                {
                    copie[max][i] *= diviseur;
                    id[max][i] *= diviseur;
                }
                
                swap(copie[pivot], copie[max]);
                swap(id[pivot], id[max]);
        
                for (int i = 0; i < n; i++)
                {
                    if (i == pivot)
                        continue;
        
                    T multCopie = copie[i][j];
        
                    for (int k = 0; k < m; ++k)
                    {
                        copie[i][k] -= (copie[pivot][k] * multCopie);
                        id[i][k] -= (id[pivot][k] * multCopie);
                    }
                }
            }
    
            return id;
        }

        bool is_null() const
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    if (isNan(mat[i][j]))
                        return true;
                }
            }
            return false;
        }

        bool is_ortho() const
        {
            Matrix rev;
            if (n != m)
                throw "The matrix must be squared to check if it's orthogonal";

            rev = reverse();

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

        Matrix operator*(const Vector<T, m> &v) const
        {
            Matrix res;

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                        res[i][j] = mat[i][j] * v[j];
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

        Matrix operator*=(const Vector<T, n> &v)
        {
            Matrix res;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                        res[i][j] *= v[j];
                }
            }

            return (*this);
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
    };

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
            out << ")" << endl;
        }
        return out;
    }

    class Mat44r : Matrix<float, 4, 4>
    {};

    static const Matrix<int, 4, 4> Identity4i({{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}});
    static const Matrix<float, 4, 4> Identity4r({{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}});
}