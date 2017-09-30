#include <ctime>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;
using namespace math;

template<class T, unsigned int n, unsigned int m>
Matrix<T, n, m> inverse_determinant(const math::Matrix<T, n, m> &matrice)
{
    Matrix<T, n, m> cofacteurs;
    Matrix<T, n, m> transp;
    T determinant;

    if (n != m)
        throw "La matrice n'est pas carré";

    transp = matrice.transpose(); 
    cofacteurs = transp.cofacteur();
    determinant = matrice.determinant();

    if (determinant != 0)
        throw "Matrice non inversible";

    return cofacteurs * (1/determinant);
}

template<class T, unsigned int n>
Matrix<T, n, n> identite(n)
{
    Matrix<T, n, n> id;

    for (int i = 0; i < n; ++i)
    {
        id[i][i] = 1;
    }

    return id;
}

template<class T, unsigned int n, unsigned int m>
Matrix<T, n, m> inverse_gauss(const math::Matrix<T, n, m> &matrice)
{
    if (n != m)
        throw "La matrice n'est pas carré";

    Matrix<T, n, n> id = identite(n);
    Matrix<T, n, m> copie = matrice;
    int pivot = 0;

    for (int j = 0; j < m; ++j, ++pivot)
    {
        int max = -1;
        float diviseur;
        for (int i = pivot; i < n; ++i)
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
            identite[max][i] *= diviseur;
        }

        if (pivot != max)
        {
            swap(copie[pivot], copie[max]);
            swap(identite[pivot], identite[max]);
        }

        for (int i = 0; i < n; i++)
        {
            if (i == pivot)
                continue;

            for (int k = 0; k < m; ++k)
            {
                copie[i][k] -= (copie[pivot][k] * copie[i][j]);
                identite[i][k] -= (identite[pivot][k] * identite[i][j]);
            }
        }
    }

    return identite;
}

int main(void)
{
   // clock_t clock;
   math::Matrix<float, 3, 3> m1({{2, -1, 0}, {-1, 2, -1}, {0, -1, 2}});
   math::Matrix<float, 3, 3> resAttendu({{0.75, 0.5, 0.25}, {0.5, 1, 0.5}, {0.25, 0.5, 0.75}});

   math::Matrix<float, 3, 3> res = m1.reverse();

   assert(res == resAttendu);
}