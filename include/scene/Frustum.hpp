#pragma once

#include "geometry/Point.hpp"
#include "geometry/Sphere.hpp"
#include "geometry/Plane.hpp"
#include "geometry/LineSegment.hpp"

#include <stdexcept>
#include <iostream>

using namespace geometry;

namespace scene
{
/**
 * @class Frustum
 * @author xavier
 * @date 06/12/17
 * @file Frustum.hpp
 * @brief Représente le champ de vision de la camera
 */
class Frustum
{
private:
    Plane<real> _near; /**< Plan proche */
    Plane<real> _far; /**< Plan lointain */
    Plane<real> _left; /**< Plan de gauche*/
    Plane<real> _right; /**< Plan de droite */
    Plane<real> _top; /**< Plan du haut */
    Plane<real> _bottom; /**< Plan du bas */

public:
    /**
     * @brief Construit un champ de vision a l'aide de ses six plans
     * @param near Le plan proche
     * @param far Le plan lointain
     * @param left Le plan gauche
     * @param right Le plan droit
     * @param top Le plan du haut
     * @param bottom Le plan du bas
     */
    Frustum(const Plane<real> &near, const Plane<real> &far, const Plane<real> &left, const Plane<real> &right, const Plane<real> &top, const Plane<real> &bottom) : 
    _near(near), _far(far), _left(left), _right(right), _top(top), _bottom(bottom)
    {
    }
    
    /**
     * @brief Destructeur
     */
    ~Frustum()
    {
    }
    
    /**
     * @brief Verifie si un point est en dehors du champs de vision
     * @return true si le point est en dehors du champs de vision, false sinon
     */
    bool outside( const Point<float, 3> & p) const
    {
        return _near.isFrontOf(p) || _far.isFrontOf(p) || _left.isFrontOf(p) || 
        _right.isFrontOf(p) || _top.isFrontOf(p) || _bottom.isFrontOf(p);
    }

    /**
     * @brief Verifie si une sphere est en dehors du champs de vision
     * @return true si la sphere est en dehors du champs de vision
     */
    bool outside( const Sphere<real> & s) const
    {
        return s.behind(_near) || s.behind(_far) || s.behind(_left) ||
            s.behind(_right) || s.behind(_top) || s.behind(_bottom);
    }
    
    /**
     * @brief Retourne l'intersection du segment avec le champ de vision
     * @return l'intersection du segment avec le champ de vision
     */
    LineSegment<real, 3> inter( const LineSegment<real, 3> & l) const
    {
        if (! outside(l.get_begin()) && ! outside(l.get_end()))
        {
            return l;
        }
        else 
        {
            Point<real, 3> intersection1;
            Point<real, 3> intersection2;
            
            if (_near.intersectCoef(l) >= 0)
            {
                intersection1 = _near.intersec(l);
                
                if (! outside(l.get_begin()))
                {
                    intersection2 = l.get_begin();
                }
                else if (! outside(l.get_end()))
                {
                    intersection2 = l.get_end();
                }
                else
                {
                    if (_far.intersectCoef(l) >= 0)
                    {
                        intersection2 = _far.intersec(l);
                    }
                    else if (_top.intersectCoef(l) >= 0)
                    {
                        intersection2 = _top.intersec(l);
                    }
                    else if (_bottom.intersectCoef(l) >= 0)
                    {
                        intersection2 = _bottom.intersec(l);
                    }
                    else if (_left.intersectCoef(l) >= 0)
                    {
                        intersection2 = _left.intersec(l);
                    }
                    else
                    {
                        intersection2 = _right.intersec(l);
                    }
                }
                std::cout << intersection1 << std::endl;
                return LineSegment<real, 3>(intersection1, intersection2);
            }
            else if (_far.intersectCoef(l) >= 0)
            {
                intersection1 = _far.intersec(l);
                
                if (! outside(l.get_begin()))
                {
                    intersection2 = l.get_begin();
                }
                else if (! outside(l.get_end()))
                {
                    intersection2 = l.get_end();
                }
                else
                {
                    if (_near.intersectCoef(l) >= 0)
                    {
                        intersection2 = _near.intersec(l);
                    }
                    else if (_top.intersectCoef(l) >= 0)
                    {
                        intersection2 = _top.intersec(l);
                    }
                    else if (_bottom.intersectCoef(l) >= 0)
                    {
                        intersection2 = _bottom.intersec(l);
                    }
                    else if (_left.intersectCoef(l) >= 0)
                    {
                        intersection2 = _left.intersec(l);
                    }
                    else
                    {
                        intersection2 = _right.intersec(l);
                    }
                }
                
                return LineSegment<real, 3>(intersection1, intersection2);
            }
            else if (_top.intersectCoef(l) >= 0)
            {
                intersection1 = _top.intersec(l);
                
                if (! outside(l.get_begin()))
                {
                    intersection2 = l.get_begin();
                }
                else if (! outside(l.get_end()))
                {
                    intersection2 = l.get_end();
                }
                else
                {
                    if (_far.intersectCoef(l) >= 0)
                    {
                        intersection2 = _far.intersec(l);
                    }
                    else if (_near.intersectCoef(l) >= 0)
                    {
                        intersection2 = _top.intersec(l);
                    }
                    else if (_bottom.intersectCoef(l) >= 0)
                    {
                        intersection2 = _bottom.intersec(l);
                    }
                    else if (_left.intersectCoef(l) >= 0)
                    {
                        intersection2 = _left.intersec(l);
                    }
                    else
                    {
                        intersection2 = _right.intersec(l);
                    }
                }
                
                return LineSegment<real, 3>(intersection1, intersection2);
            }
            else if (_bottom.intersectCoef(l) >= 0)
            {
                intersection1 = _bottom.intersec(l);
                
                if (! outside(l.get_begin()))
                {
                    intersection2 = l.get_begin();
                }
                else if (! outside(l.get_end()))
                {
                    intersection2 = l.get_end();
                }
                else
                {
                    if (_far.intersectCoef(l) >= 0)
                    {
                        intersection2 = _far.intersec(l);
                    }
                    else if (_top.intersectCoef(l) >= 0)
                    {
                        intersection2 = _top.intersec(l);
                    }
                    else if (_near.intersectCoef(l) >= 0)
                    {
                        intersection2 = _bottom.intersec(l);
                    }
                    else if (_left.intersectCoef(l) >= 0)
                    {
                        intersection2 = _left.intersec(l);
                    }
                    else
                    {
                        intersection2 = _right.intersec(l);
                    }
                }
                
                return LineSegment<real, 3>(intersection1, intersection2);
            }
            else if (_left.intersectCoef(l) >= 0)
            {
                intersection1 = _left.intersec(l);
                
                if (! outside(l.get_begin()))
                {
                    intersection2 = l.get_begin();
                }
                else if (! outside(l.get_end()))
                {
                    intersection2 = l.get_end();
                }
                else
                {
                    if (_far.intersectCoef(l) >= 0)
                    {
                        intersection2 = _far.intersec(l);
                    }
                    else if (_top.intersectCoef(l) >= 0)
                    {
                        intersection2 = _top.intersec(l);
                    }
                    else if (_bottom.intersectCoef(l) >= 0)
                    {
                        intersection2 = _bottom.intersec(l);
                    }
                    else if (_near.intersectCoef(l) >= 0)
                    {
                        intersection2 = _left.intersec(l);
                    }
                    else
                    {
                        intersection2 = _right.intersec(l);
                    }
                }
                
                return LineSegment<real, 3>(intersection1, intersection2);
            }
            else if (_right.intersectCoef(l) != 0)
            {
                intersection1 = _right.intersec(l);
                
                if (! outside(l.get_begin()))
                {
                    intersection2 = l.get_begin();
                }
                else if (! outside(l.get_end()))
                {
                    intersection2 = l.get_end();
                }
                else
                {
                    if (_far.intersectCoef(l) != 0)
                    {
                        intersection2 = _far.intersec(l);
                    }
                    else if (_top.intersectCoef(l) != 0)
                    {
                        intersection2 = _top.intersec(l);
                    }
                    else if (_bottom.intersectCoef(l) != 0)
                    {
                        intersection2 = _bottom.intersec(l);
                    }
                    else if (_left.intersectCoef(l) != 0)
                    {
                        intersection2 = _left.intersec(l);
                    }
                    else
                    {
                        intersection2 = _near.intersec(l);
                    }
                }
                
                return LineSegment<real, 3>(intersection1, intersection2);
            }
            
            throw(std::invalid_argument("No intersection"));
        }
    }
    
    friend std::ostream& operator<<(std::ostream &out, Frustum &f)
    {
        out << "Near : " << f._near << ", far : " << f._far << ", left : " << f._left << ", right : " << f._right << ", top : " << f._top << ", bottom : " << f._bottom;
        return out;
    }
};
}

