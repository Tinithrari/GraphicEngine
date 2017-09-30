#pragma once

#include <exception>

using namespace std;

namespace math
{
    template<class T, unsigned int n, unsigned int m>
    class Matrix
    {
    private:
        array<array<T, m>, n> mat;
        bool isReversable()
        {
            return false;
        }
    public:
        Matrix() {if (n == 0 || m == 0) throw "Incorrect size";}
        Matrix(Matrix &m2)
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
        T at(unsigned int i, unsigned int j)
        {
            if (i >= n || j >= m)
                throw ("Index out of the matrix");
            
            return mat[i][j];
        }

        Matrix reverse()
        {
            if (! isInversible())
                throw "This matrix is not reversable";

            // TODO
        }

        bool is_null()
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

        Matrix cofacteur()
        {
            Matrix cofac;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; j++)
                {
                    cofac[i][j] = (((-1) * (i + j + 2)) * mat[i][j]);
                }
            }
            return cofac;
        }

        float determinant()
        {
            Matrix cofac = cofacteur();
            float det;

            for (int i = 0; i < m; ++i)
            {
                det += mat[0][i] * cofac[0][i];
            }

            return det;
        }

        bool is_ortho()
        {
            Matrix rev;
            if (n != m)
                throw "The matrix must be squared to check if it's orthogonal";

            rev = reverse();

            return rev == transpose()
        }

        Matrix<T, m ,n> transpose()
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

        T &operator[][](int i, int j)
        {
            return mat[i][j];
        }

        T operator[][](int i, int j) const
        {
            return mat[i][j];
        }

        array<T, m> &operator[](int i)
        {
            return mat[i];
        }

        Matrix operator+(Matrix &m2) const
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

        Matrix &operator+=(Matrix &m2)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    mat[i][j] += m2[i][j];
                }
            }
        }

        Matrix operator*(Vector<T, m> &v)
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

        Matrix operator*(float scalar)
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
        Matrix<T, n, o> operator*(Matrix<T, m, o> &m2)
        {
            Matrix res;
            
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < o; ++j)
                {
                    for (int k = 0; k < m; ++k)
                    {
                       res[i][j] += mat[i][k] * v[k][o];
                    }
                }
            }
            
            return res;
        }

        Matrix operator*=(Vector<T, n> &v)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                        res[i][j] *= v[j];
                }
            }

            return (*this);
        }

        Matrix operator*=(float scalar)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < m; ++j)
                {
                    mat[i][j] *= scalar;
                }
            }
        }

        bool operator==(Matrix &m2)
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
    Matrix<T, n, m> &operator*(float scalar, Matrix<T, n, m> &m)
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
}