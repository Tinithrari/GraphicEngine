#pragma once
#include <array>
#include <cmath>
#include <iostream>

#ifndef REAL_TYPE
typedef float real;
#endif

using namespace std;

const unsigned int MIN_ARGS_CROSS = 3;

namespace math
{
  template<class T, unsigned int size>
  class Vector
  {
  protected:
    array<T, size> vec;
  public:
    Vector() 
    {
      if (size == 0)
        throw "Invalid size specified";

      for (int i = 0; i < size; ++i)
        vec[i] = T();
    }
    Vector(const initializer_list<T> &list)
    {
      int i = 0;
      for (const T* element = list.begin(); element != list.end(); ++element, ++i)
      {
        vec[i] = *element;
      }
    }

    Vector(const Vector &v)
    {
      for (int i = 0; i < size; ++i)
        vec[i] = v[i];
    }

    ~Vector() {}
    inline T at(const unsigned int i) const { if (i > size) throw "Index out of the vector"; return vec.at(i); }

    Vector cross(const Vector &v) const
    {
      Vector res;

      if (size < MIN_ARGS_CROSS)
        throw "The vector must have at least three arguments";

      res[0] = (vec[1] * v[2]) - (vec[2] * v[1]);
      res[1] = (vec[2] * v[0]) - (vec[0] * v[2]);
      res[2] = (vec[0] * v[1]) - (vec[1] * v[0]);

      return res;
    }

    bool is_ortho(const Vector &v) const
    {
      return ((*this) * v) == 0;
    }

    bool is_null() const
    {
      for (int i = 0; i < size; ++i)
        if (isnan(vec[i]))
          return true;
      return false;
    }

    bool is_unit() const
    {
      return norm() == 1;
    }

    float norm() const
    {
      float somme = 0;

      for (int i = 0; i < size; ++i)
      {
        somme += (vec[i] * vec[i]);
      }
      return sqrt(somme);
    }

    Vector to_unit() const
    {
      Vector<T, size> v;
      for (int i = 0; i < size; i++)
        v.vec[i] = ((1 / norm()) * (vec[i]));
    }

    T operator[](int i) const
    {
        return vec[i];
    }

    T &operator[](int i)
    {
      return vec[i];
    }

    bool operator==(const Vector &v) const
    {
      for (int i = 0; i < size; ++i)
        if (v[i] != vec[i])
          return false;
      return true;
    }

    bool operator!=(const Vector &v) const
    {
      for (int i = 0; i < size; ++i)
        if (v[i] != vec[i])
          return true;
      return false;
    }

    Vector operator+(const Vector &v) const
    {
      Vector result;

      for (int i = 0; i < size; ++i)
      {
        result[i] = this->at(i) + v[i];
      }

      return result;
    }

    Vector &operator+=(Vector &v)
    {
      for (int i = 0; i < size; ++i)
      {
        vec[i] = vec[i] + v[i];
      }

      return (*this);
    }

    Vector operator-() const
    {
      Vector<T, size> res;

      for (int i = 0; i < size; ++i)
        res[i] = -vec[i];

      return res;
    }

    Vector operator-(const Vector &v) const
    {
      Vector<T, size> res;

      for (int i = 0; i < size; ++i)
        res[i] = vec[i] - v[i];

      return res;
    }

    Vector &operator-=(Vector &v)
    {
      for (int i = 0; i < size; ++i)
        vec[i] = vec[i] - v[i];

      return (*this);
    }

    Vector operator*(float scalar) const
    {
      Vector v;

      for (int i = 0; i < size; ++i)
      {
        v[i] = vec[i] * scalar;
      }

      return v;
    }

    T operator*(Vector &v) const
    {
      T somme;

      for (int i = 0; i < size; ++i)
      {
        somme += vec[i] * v[i];
      }

      return somme;
    }

    friend Vector operator*(float scalar, Vector &v2)
    {
      return v2 * scalar;
    }
  };
  
  template <class T, unsigned int size>
  ostream &operator<<(ostream &s, const Vector<T, size> &v)
  {
    s << "(";
    s << v[0];

    for (int i = 1; i < size; ++i)
      s << ", " << v[i];
    
    s << ")";

    return s;
  }

  template<class T, unsigned int size>
  Vector<T, size> cross(const Vector<T, size> &v1, const Vector<T, size> &v2)
  {
    Vector<T, size> res;

    if (size < MIN_ARGS_CROSS)
      throw "The vector must have at least three arguments";

    res[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    res[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    res[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

    return res;
  }

  template<class T, unsigned int size>
  Vector<T, size> dot(Vector<T, size> &vec, float scalar)
  {
    Vector<T, size> v;

    for (int i = 0; i < size; ++i)
    {
      v[i] = vec[i] * scalar;
    }

    return v;
  }

  template<class T, unsigned int size>
  T dot(Vector<T, size> &vec, Vector<T, size> &v)
  {
    T somme = 0;

    for (int i = 0; i < size; ++i)
    {
      somme += vec[i] * v[i];
    }

    return somme;
  }

  template<class T, unsigned int size>
  Vector<T, size> dot(float scalar, Vector<T, size> &v2)
  {
    return v2 * scalar;
  }

  class Vec2i : public Vector<int, 2>
  {
    using Vector::Vector;
  };
  
  class Vec3i : public Vector<int, 3>
  {
    using Vector::Vector;
  };

  class Vec4i : public Vector<int, 4>
  {
    using Vector::Vector;
  };

  class Vec2r : public Vector<float, 2>
  {
    using Vector::Vector;
  };

  class Vec3r : public Vector<float, 3>
  {
    using Vector::Vector;
  };

  class Vec4r : public Vector<float, 4>
  {
    using Vector::Vector;
  };
}
