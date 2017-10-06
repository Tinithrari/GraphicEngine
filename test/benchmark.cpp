#include "math/Matrix.hpp"

#include <ctime>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

template<class T, unsigned int n>
math::Matrix<T, n, n> identite()
{
    math::Matrix<T, n, n> id;

    for (int i = 0; i < n; ++i)
    {
        id[i][i] = 1;
    }

    return id;
}

template<class T, unsigned int n, unsigned int m>
math::Matrix<T, n, m> inverse_gauss(const math::Matrix<T, n, m> &matrice)
{
    if (n != m)
        throw "La matrice n'est pas carré";

    math::Matrix<T, n, n> id = identite<T, n>();
    math::Matrix<T, n, m> copie = matrice;
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

template <class T, unsigned int n, unsigned int m>
array<array<T, m>, n> affect(const T (&tab)[n][m])
{
    array<array<T, m>, n> ar;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            ar[i][j] = tab[i][j];

    return ar;
}

int main(void)
{
   // clock_t clock;
   math::Matrix<float, 3, 3> m1;
   math::Matrix<float, 3, 3> resAttendu;
   array<array<float, 3>, 3> a1 = affect((float[3][3]){{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}});
   array<array<float, 3>, 3> a2 = affect((float[3][3]){{0.75, 0.5, 0.25}, {0.5, 1, 0.5}, {0.25, 0.5, 0.75}});

   m1 = a1;
   resAttendu = a2;

   math::Matrix<float, 3, 3> res = inverse_gauss(m1);

   if (! (res == resAttendu))
    cout << res;
}