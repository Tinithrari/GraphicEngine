#pragma once

#include "math/Vector.hpp"

#include "geometry/Direction.hpp"
#include "geometry/Quaternion.hpp"
#include "geometry/Transformation.hpp"
#include "geometry/LineSegment.hpp"

#include "scene/Frustum.hpp"

constexpr real nearPlaneDistance = -1;

using namespace math;
using namespace geometry;

namespace scene
{
    /**
     * @class Camera
     * @author xavier
     * @date 09/12/17
     * @file Camera.hpp
     * @brief Camera d'une scene 3D
     */
    class Camera
    {
    private:
        size_t              _width;
        size_t              _height;
        size_t              _moveSpeed;
        size_t              _rotSpeed;
        size_t              _zoomSpeed;
        Vec3r               _position;
        Direction<real, 3>  _orientation;
        Vec3r               _actualMoveSpeed;
        Quaternion<real>    _actualRotSpeed;
        Vec3r               _actualZoomSpeed;
        real                _distanceProj;
        real                _focalLength;
        Frustum             _fieldOfView;
        
        Frustum generateFrustum()
        {
            real aspectRatio = _width / _height;
            Plane<real> near(Point<real, 3>(_orientation * _distanceProj + _position), 
                                            Direction<real, 3>(_orientation));
                                            
            Plane<real> far(Point<real, 3>(_orientation * (_distanceProj + _focalLength) + _position ), 
                                            Direction<real, 3>(-_orientation));
            
            Plane<real> left(Point<real, 3>{(-_distanceProj)/_focalLength + _position[0], _position[1], far.GetP()[2] / 2}, 
                                            Direction<real, 3>{_focalLength * _orientation[0], _orientation[1], _orientation[2]});
                                            
            Plane<real> right(Point<real, 3>{(_distanceProj)/_focalLength + _position[0], _position[1], far.GetP()[2] / 2}, 
                                            Direction<real, 3>{-_focalLength * _orientation[0], _orientation[1], _orientation[2]});
            
            Plane<real> top(Point<real, 3>{_position[0], ((aspectRatio * _distanceProj) / _focalLength) + _position[1], far.GetP()[2] / 2}, 
                                            Direction<real, 3>{_orientation[0], -_focalLength * _orientation[1], _orientation[2]});
                                            
            Plane<real> bottom(Point<real, 3>{_position[0], ((-aspectRatio * _distanceProj) / _focalLength), far.GetP()[2] / 2}, 
                                            Direction<real, 3>{_orientation[0], _focalLength * _orientation[1], _orientation[2]});
                                            
            return Frustum(near, far, left, right, top, bottom);
        }
    public:
        
        /**
         * @brief 
         */
        Camera(size_t width, size_t height, real distanceProj, Direction<real, 3> &orientation) : 
        _width(width), 
        _height(height),
        _distanceProj(distanceProj),
        _orientation(orientation),
        _focalLength(1)
        {
            _fieldOfView = generateFrustum();
        }
        
        /**
         * @brief 
         */
        ~Camera()
        {
        }
        
        /**
         * @brief 
         * @param d
         */
        void move(const Direction<real, 3> &d)
        {
            _actualMoveSpeed[0] = d[0] * _moveSpeed;
            _actualMoveSpeed[1] = d[1] * _moveSpeed;
            _actualMoveSpeed[2] = d[2] * _moveSpeed;
        }

        /**
         * @brief 
         * @param q
         */
        void turn(const Quaternion<real> &q)
        {
            _actualRotSpeed = Quaternion<real>(_rotSpeed, Direction<real>(_orientation));
        }
        
        /**
         * @brief 
         */
        void zoom_in()
        {
            _actualZoomSpeed = _zoomSpeed;
        }
        
        /**
         * @brief 
         */
        void zoom_out()
        {
            _actualZoomSpeed = -_zoomSpeed;
        }
        
        /**
         * @brief 
         */
        void stop_move()
        {
            _actualMoveSpeed[0] = 0;
            _actualMoveSpeed[1] = 0;
            _actualMoveSpeed[2] = 0;
        }
        
        /**
         * @brief 
         */
        void stop_turn()
        {
            _actualRotSpeed = Quaternion<real>();
        }
        
        /**
         * @brief 
         */
        void stop_zoom()
        {
            _actualZoomSpeed = 0;
        }
        
        /**
         * @brief 
         * @return 
         */
        Transformation<real> getTransform() const
        {
            Transformation<real> t = Transformation<real>::createTranslation(_position[0], _position[1], _position[2]);
            return t.concat(Transformation<real>(0, _orientation));
        }
        
        /**
         * @brief 
         * @param s
         * @return 
         */
        bool outsideFrustum(const Sphere<real> &s) const
        {
            return _fieldOfView.outside(s);
        }
        
        /**
         * @brief 
         * @param t
         * @return 
         */
        bool sees(const Triangle<real> &t) const
        {
            return ! _fieldOfView.outside(t.get_p0()) || ! _fieldOfView.outside(t.get_p1())
                    || ! _fieldOfView.outside(t.get_p2());
        }
        
        /**
         * @brief 
         * @param ls
         * @return
         */
        LineSegment<real, 3> visible_part(const LineSegment<real, 3> &ls) const
        {
            return _fieldOfView.inter(ls);
        }
        
        /**
         * @brief 
         */
        void update()
        {
            _position += _actualMoveSpeed;
            _orientation = _actualRotSpeed.rotate(_orientation);
            _focalLength += _actualZoomSpeed;
        }
    };

}

