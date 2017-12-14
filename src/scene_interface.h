// scene_interface.h
//
// by Tiago de Lima <tiago.delima.univ-artois.fr>
// on 13 nov 2017
//
// Defines Scene interface.

#ifndef _SCENE_INTERFACE_H
#define _SCENE_INTERFACE_H

#include "libmatrix.h"

class SceneInterface
{
    public:

        virtual void draw() const = 0;

        virtual void press_up() = 0;
        virtual void press_down() = 0;
        virtual void press_left() = 0;
        virtual void press_right() = 0;
        virtual void press_space() = 0;
        virtual void press_w() = 0;
        virtual void press_s() = 0;
        virtual void press_a() = 0;
        virtual void press_d() = 0;
        virtual void press_q() = 0;
        virtual void press_e() = 0;
        virtual void press_z() = 0;
        virtual void press_x() = 0;

        virtual void release_updown() = 0;
        virtual void release_leftright() = 0;
        virtual void release_space() = 0;
        virtual void release_ws() = 0;
        virtual void release_ad() = 0;
        virtual void release_qe() = 0;
        virtual void release_zx() = 0;

        virtual void update() = 0;
};

#endif // _SCENE_INTERFACE_H
