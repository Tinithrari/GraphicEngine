#include "math/Vector.hpp"

#include <iostream>

using namespace std;

int main(void)
{
  math::Vector<int, 3> vec1;

  vec1[0] = 1;
  vec1[1] = 2;
  vec1[2] = 3;

  cout << vec1 << endl;
}
