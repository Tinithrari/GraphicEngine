#pragma once

#include "geometry/Quaternion.hpp"
#include "geometry/Direction.hpp"
#include "geometry/Sphere.hpp"

#include "scene_interface.h" // Base class: SceneInterface
#include "gui.h"
#include "gui_interface.h"
#include "scene/Camera.hpp"
#include "scene/Object3D.hpp"

#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;
using namespace scene;
using namespace geometry;
using namespace gui;

namespace scene
{

class Scene : public SceneInterface
{
private:
    Gui* _gui;
    Camera* _camera;
    vector<Object3D> _objectList;
    Direction<real, 3> _move;
    Direction<real, 3> _axe;
public:
    Scene(Gui * gui, vector<Object3D>& objectList) : _objectList(objectList){
        if (gui == nullptr)
            throw(invalid_argument("Gui musn't be null"));
        _gui = gui;
        _camera = new Camera(_gui->get_win_width(), _gui->get_win_height(), 1, Direction<real, 3>{0, 0, -1});
    }
    virtual ~Scene() {
        delete _camera;
        delete _gui;
    }

    void addObject(Object3D &o)
    {
        _objectList.push_back(o);
    }

    virtual
    void draw() const;
    virtual
    void press_a();
    virtual
    void press_d();
    virtual
    void press_down();
    virtual
    void press_e();
    virtual
    void press_left();
    virtual
    void press_q();
    virtual
    void press_right();
    virtual
    void press_s();
    virtual
    void press_space();
    virtual
    void press_up();
    virtual
    void press_w();
    virtual
    void press_x();
    virtual
    void press_z();
    virtual
    void release_ad();
    virtual
    void release_leftright();
    virtual
    void release_qe();
    virtual
    void release_space();
    virtual
    void release_updown();
    virtual
    void release_ws();
    virtual
    void release_zx();
    virtual
    void update();

};

}
void scene::Scene::draw() const
{
    vector<int> deleted;
    
    // Suppression des objets invisibles
    for (int i = 0; i < _objectList.size(); ++i)
    {
        Sphere<real> bounding = _objectList[i].bsphere();
        if (_camera->outsideFrustum(bounding))
            deleted.push_back(i);
    }
    
    if (deleted.size() == _objectList.size())
        return;
    
    vector<LineSegment<real, 3>> ligne;
    for (int i = 0; i < _objectList.size(); ++i)
    {
        if (std::find(deleted.begin(), deleted.end(), i) == deleted.end())
            continue;
        
        for (int j = 0; j < _objectList[i].num_faces(); ++j)
        {
            Triangle<real> face = _objectList[i].face(j);
            if (!_camera->sees(face))
                continue;
                
            LineSegment<real, 3> p0p1(face.get_p0(), face.get_p1());
            LineSegment<real, 3> p0p2(face.get_p0(), face.get_p2());
            LineSegment<real, 3> p1p2(face.get_p1(), face.get_p2());

            try {
                ligne.push_back(_camera->visible_part(p0p1));
            } catch (invalid_argument &e) {
                
            }
            
            try {
                ligne.push_back(_camera->visible_part(p0p2));
            } catch (invalid_argument &e) {
                
            }
            
            try {
                ligne.push_back(_camera->visible_part(p1p2));
            } catch (invalid_argument &e) {
                
            }
        }
    }
    
    if (ligne.size() == 0)
        return;
    
    for (int i = 0; i < ligne.size(); ++i)
    {
        LineSegment<real, 2> proj(
            Point<real, 2>{(- _camera->GetFocalLength() / ligne[i].get_begin()[2]) * ligne[i].get_begin()[0],
            (- _camera->GetFocalLength() / ligne[i].get_begin()[2]) * ligne[i].get_begin()[1]},
            Point<real, 2>{(- _camera->GetFocalLength() / ligne[i].get_end()[2]) * ligne[i].get_end()[0],
            (- _camera->GetFocalLength() / ligne[i].get_end()[2]) * ligne[i].get_end()[1]}
        );
        _gui->render_line(proj.get_begin(), proj.get_end(), white);
    }
}

void scene::Scene::press_a()
{
    _camera->zoom_in();
}

void scene::Scene::press_d()
{
    const Direction<real, 3>& orientation = _camera->GetOrientation();
    _move[0] += orientation[2];
    _move[1] += orientation[1]; 
    _move[2] += orientation[0];
}

void scene::Scene::press_down()
{
    Quaternion<real> q(-2, Direction<real, 3>{1, 0, 0});
    _camera->turn(q);
}

void scene::Scene::press_e()
{
    _camera->zoom_out();
}

void scene::Scene::press_left()
{
    Quaternion<real> q(-2, Direction<real, 3>{0, 1, 0});
    _camera->turn(q);
}

void scene::Scene::press_q()
{
    const Direction<real, 3>& orientation = _camera->GetOrientation();
    Direction<real, 3> perp{-orientation[2], orientation[1], orientation[0]};
    _camera->move(perp);
}

void scene::Scene::press_right()
{
    Quaternion<real> q(2, Direction<real, 3>{0, 1, 0});
    _camera->turn(q);
}

void scene::Scene::press_s()
{
    _move += -_camera->GetOrientation();
}

void scene::Scene::press_space()
{
    _move += Direction<real, 3>{0, 1, 0};
}

void scene::Scene::press_up()
{
    Quaternion<real> q(2, Direction<real, 3>{1, 0, 0});
    _camera->turn(q);
}

void scene::Scene::press_w()
{
    throw(runtime_error("Not implemented"));
}

void scene::Scene::press_x()
{
    _move += Direction<real, 3>{0, -1, 0};
}

void scene::Scene::press_z()
{
    _move += _camera->GetOrientation();
}

void scene::Scene::release_ad()
{
    _move[0] = 0;
    _move[2] = 0;
}

void scene::Scene::release_leftright()
{
    _axe[1] = 0;
}

void scene::Scene::release_qe()
{
    _camera->stop_zoom();
}

void scene::Scene::release_space()
{
    _move[1] = 0;
}

void scene::Scene::release_updown()
{
    _axe[0] = 0;
}

void scene::Scene::release_ws()
{
    _move = Direction<real, 3>();
}

void scene::Scene::release_zx()
{
}

void scene::Scene::update()
{
    _camera->move(_move.to_unit());
    _camera->update();
}
