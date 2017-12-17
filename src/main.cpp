#include "Scene.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace scene;
using namespace geometry;
using namespace math;
using namespace gui;

Object3D readGeoFile(const string & name)
{
    std::ifstream file;
    file.open(name);
    if (! file) {
        cerr << "Fail when opening the file" << endl;
        exit(1);
    }
    int nb;
    if (file.good())
        file >> nb;
    if (file.fail()) {
        cerr << "Fail when reading the file" << endl;
        exit(1);
    }
    vector<Point<real, 3>> points;
    for (int i = 0; i < nb; ++i) {

        real x, y, z;
        if (file.good())
            file >> x;
        if (file.good())
            file >> y;
        if (file.good())
            file >> z;
        points.push_back(Point<real, 3> {x, y, z});
    }
    Object3D o(points);

    if (file.good())
        file >> nb;
    for (int i = 0; i < nb; ++i) {
        real x, y, z;
        if (file.good()) {
            if (file.good())
                file >> x;
            if (file.good())
                file >> y;
            if (file.good())
                file >> z;
        }
        o.add_face(x, y, z);
    }

    file.close();
    return o;
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        cerr << "Usage : " << *argv << " <file 1> ... <file n>" << endl;
        exit(1);
    }
    vector<Object3D> o;
    for (int i = 1; i < argc; ++i)
        o.push_back(readGeoFile(string(argv[i])));

    Gui gui;
    Scene *scene = new Scene(&gui, o);
    try {
        gui.start();
        gui.main_loop(scene);
        gui.stop();
    } catch (exception &e) {
        cerr << "Exception : " << e.what() << endl;
    }
    delete scene;
}
