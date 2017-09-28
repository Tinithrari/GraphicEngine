#include <ctime>
#include <iostream>

using namespace std;


template<class T, n, m>
Matrix<T, n, m> inverse_determinant(math::Matrix<T, n, m> &matrice)
{
    unsigned int k;
    Matrix<T, n, m> cofacteurs;
    Matrix<T, n, m> transp;

    if (n != m)
        throw "La matrice n'est pas carré";

    transp = matrice.transpose(); 

    srand(time(NULL));
    k = rand() % n;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            cofacteur[i][j] = (((-1) * (i + j + 2)) * transp[i][j]);
        }
    }

    if (determinant != 0)
        throw "Matrice non inversible";
}

template<class T, n, m>
Matrix<T, n, m> inverse_gauss(math::Matrix<T, n, m> &matrice)
{
    if (n != m)
        throw "La matrice n'est pas carré";


}

int main(void)
{
    clock_t clock;
}