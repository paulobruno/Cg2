#ifndef RAYCASTINGSCENE_H
#define RAYCASTINGSCENE_H


#include "ImageHandlerQt.h"
#include "Scene.h"
#include "ColorRgba.h"
#include "Position3d.h"
#include "Sphere.h"

#include <cmath>


class RaycastingScene : public Scene
{
    public:

        RaycastingScene();

        void render();


    private:

        Sphere sphere;
        ImageHandlerQt image;


        ColorRgba calculateColor(Position3d position);

        Position3d interceptObjectWithRay(Position3d origin, Position3d direction);
};


#endif // RAYCASTINGSCENE_H
