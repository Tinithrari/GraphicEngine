#pragma once

#include "math/Vector.hpp"

#include <array>
#include <exception>
#include <iostream>

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
    public:
        Matrix() {if (n == 0 || m == 0) throw "Incorrect size";}
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
            Matrix m2;
            if (! isReversable())
                throw "This matrix is not reversable";

            // TODO
            return m2;
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

        Matrix cofacteur() const
        {
            Matrix cofac;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; j++)
                {
                    cofac[i][j] = ((pow((-1), (i + j + 2))) * mat[i][j]);
                }
            }
            return cofac;
        }

        float determinant() const
        {
            Matrix cofac = cofacteur();
            float det;

            for (int i = 0; i < m; ++i)
            {
                det += mat[0][i] * cofac[0][i];
            }

            return det;
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
}