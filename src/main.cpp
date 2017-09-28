#include "Vector.hpp"

#include <iostream>

using namespace std;

template <class T, unsigned int size>
void displayVector(const math::Vector<T, size> &v)
{
  cout << "(" << v[0];
  for (int i = 1; i < size; i++)
  {
    cout << ", " << v[i];
  }

  cout << ")" << endl;
}

int main(void)
{
  math::Vector<int, 3> vec1;

  vec1[0] = 1;
  vec1[1] = 2;
  vec1[2] = 3;

  displayVector(vec1);
}
