#pragma once
#include <array>
#include <cmath>
#include <iostream>
#define ROUND(x) (round((x) * 100) / 100)

using real = float;


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
    /**
     * @brief Constructeur par défaut
     * @return Le vecteur nul
     */
    Vector()
    {
      if (size == 0)
        throw "Invalid size specified";

      for (int i = 0; i < size; ++i)
        vec[i] = T();
    }
    
    /**
     * @brief Construit un vecteur avec une liste de coordonnées
     * @param list La liste des coordonnées que doit comporter le vecteur
     * @return Le vecteur initialisé avec les coordonnées spécifiées
     */
    Vector(const initializer_list<T> &list)
    {
      int i = 0;
      for (const T* element = list.begin(); element != list.end(); ++element, ++i)
      {
        vec[i] = *element;
      }
    }

    /**
     * @brief COnstructeur par recopie
     * @param v Le vecteur à recopier
     * @return Une copie du vecteur passé en paramètre
     */
    Vector(const Vector &v)
    {
      for (int i = 0; i < size; ++i)
        vec[i] = v[i];
    }

    /**
     * @brief Destructeur
     */
    ~Vector() {}
    
    /**
     * @brief Accède à la coordonnées i
     * @param i l'index de la coordonnée
     * @return La valeur de la coordonnée à l'index i
     */
    inline T at(const unsigned int i) const { if (i > size) throw "Index out of the vector"; return vec.at(i); }

    /**
     * @brief Produit vectoriel
     * @param v Le vecteur à multiplier au vecteur courant
     * @return Le vecteur résultant du produit
     */
    Vector cross(const Vector &v) const
    {
      Vector res;

      if (size < MIN_ARGS_CROSS)
        throw "The vector must have at least three arguments";

      res[0] = ROUND((vec[1] * v[2]) - (vec[2] * v[1]));
      res[1] = ROUND((vec[2] * v[0]) - (vec[0] * v[2]));
      res[2] = ROUND((vec[0] * v[1]) - (vec[1] * v[0]));

      return res;
    }

    /**
     * @brief Vérifie si le vecteur est orthogonal à un autre
     * @param v Le vecteur avec lequel on souhaite effectuer la verification
     * @return true si le vecteur courant est orthongonal avec le vecteur v, false sinon
     */
    bool is_ortho(const Vector &v) const
    {
      return ((*this) * v) == 0;
    }

    /**
     * @brief Vérifie si le vecteur comporte une valeur non valide
     * @return  true si le vecteur comporte une valeur non valide, false sinon
     */
    bool is_null() const
    {
      for (int i = 0; i < size; ++i)
        if (isnan(vec[i]))
          return true;
      return false;
    }

    /**
     * @brief Verifie si le vecteur est unitaire
     * @return true si le vecteur est unitaire, false sinon
     */
    bool is_unit() const
    {
      return norm() == 1;
    }

    /**
     * @brief Calcule la norme du vecteur
     * @return La norme du vecteur
     */
    float norm() const
    {
      float somme = dot(*this, *this);
      return sqrt(somme);
    }

    /**
     * @brief Créer un vecteur unitaire equivalent au vecteur courant
     * @return Le vecteur courant convertit en vecteur unitaire
     */
    Vector to_unit() const
    {
      Vector<T, size> v;
      for (int i = 0; i < size; i++)
        v.vec[i] = ROUND((1 / norm()) * (vec[i]));
    }

    /**
     * @brief Accesseur pour la composante constante i du vecteur
     * @param i l'index de la coordonnée du vecteur
     * @return La référence constante de la composante i du vecteur
     */
    const T &operator[](int i) const
    {
        return vec[i];
    }

    T &operator[](int i)
    {
      return vec[i];
    }

    /**
     * @brief Verifie l'egalite du vecteur courant avec un autre vecteur
     * @param v le vecteur avec lequel effectué la comparaison
     * @return true si les deux vecteurs sont égaux, false sinon
     */
    bool operator==(const Vector &v) const
    {
      for (int i = 0; i < size; ++i)
        if (v[i] != vec[i])
          return false;
      return true;
    }

    /**
     * @brief Verifie l'inegalite du vecteur courant avec un autre vecteur
     * @param v le vecteur avec lequel effectue la comparaison
     * @return true si les deux vecteurs sont inegaux, false sinon
     */
    bool operator!=(const Vector &v) const
    {
      for (int i = 0; i < size; ++i)
        if (v[i] != vec[i])
          return true;
      return false;
    }

    /**
     * @brief Additionne le vecteur courant avec un autre vecteur
     * @param v Le vecteur avec lequel effectuer la comparaison
     * @return Le vecteur résultant de l'addition
     */
    Vector operator+(const Vector &v) const
    {
      Vector result;

      for (int i = 0; i < size; ++i)
      {
        result[i] = ROUND(this->at(i) + v[i]);
      }

      return result;
    }

    /**
     * @brief Additione un autre vecteur à celui-ci
     * @param v Le vecteur a additionner au vecteur courant
     */
    Vector &operator+=(const Vector &v)
    {
      for (int i = 0; i < size; ++i)
      {
        vec[i] = ROUND(vec[i] + v[i]);
      }

      return (*this);
    }

    /**
     * @brief Calcule la negation du vecteur courant
     * @return La negation du vecteur courant
     */
    Vector operator-() const
    {
      Vector<T, size> res;

      for (int i = 0; i < size; ++i)
        res[i] = -vec[i];

      return res;
    }

    /**
     * @brief Soustrait un vecteur au vecteur courant
     * @param v Le vecteur a soustraire au vecteur courant
     * @return Le vecteur resultant de la soustraction
     */
    Vector operator-(const Vector &v) const
    {
      Vector<T, size> res;

      for (int i = 0; i < size; ++i)
        res[i] =  ROUND(vec[i] - v[i]);

      return res;
    }

    /**
     * @brief Soustrait directement un vecteur au vecteur courant
     * @param v Le vecteur a soustraire au vecteur courant
     */
    Vector &operator-=(const Vector &v)
    {
      for (int i = 0; i < size; ++i)
        vec[i] = ROUND(vec[i] - v[i]);

      return (*this);
    }

    /**
     * @brief Produit du vecteur courant avec un scalaire
     * @param scalar Le scalaire a multiplier au vecteur courant
     * @return Le vecteur resultant du produit
     */
    Vector operator*(const float scalar) const
    {
      Vector v;

      for (int i = 0; i < size; ++i)
      {
        v[i] = ROUND(vec[i] * scalar);
      }

      return v;
    }

    /**
     * @brief Produit scalaire du vecteur courant avec un autre vecteur
     * @param v Le vecteur a multiplier au vecteur courant
     * @return Le resultat du produit scalaire
     */
    T operator*(const Vector &v) const
    {
      T somme;

      for (int i = 0; i < size; ++i)
      {
        somme += ROUND(vec[i] * v[i]);
      }

      return somme;
    }

    /**
     * @see operator*(float scalar) 
     */
    friend Vector operator*(float scalar, Vector &v2)
    {
      return ROUND(v2 * scalar);
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

    res[0] = ROUND((v1[1] * v2[2]) - (v1[2] * v2[1]));
    res[1] = ROUND((v1[2] * v2[0]) - (v1[0] * v2[2]));
    res[2] = ROUND((v1[0] * v2[1]) - (v1[1] * v2[0]));

    return res;
  }

  template<class T, unsigned int size>
  Vector<T, size> dot(Vector<T, size> &vec, float scalar)
  {
    Vector<T, size> v;

    for (int i = 0; i < size; ++i)
    {
      v[i] = ROUND(vec[i] * scalar);
    }

    return v;
  }

  template<class T, unsigned int size>
  T dot(const Vector<T, size> &vec, const Vector<T, size> &v)
  {
    T somme = 0;

    for (int i = 0; i < size; ++i)
    {
      somme += ROUND(vec[i] * v[i]);
    }

    return somme;
  }

  template<class T, unsigned int size>
  Vector<T, size> dot(float scalar, Vector<T, size> &v2)
  {
    return v2 * scalar;
  }

  using Vec2i = Vector<int, 2>;
  using Vec3i = Vector<int, 3>;
  using Vec4i = Vector<int, 4>;
  using Vec2r = Vector<real, 2>;
  using Vec3r = Vector<real, 3>;
  using Vec4r = Vector<real, 4>;
}
