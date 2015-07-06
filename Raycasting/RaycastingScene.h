#ifndef RAYCASTINGSCENE_H
#define RAYCASTINGSCENE_H


#include "ImageHandlerQt.h"
#include "Scene.h"
#include "ColorRgba.h"
#include "Position3d.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cube.h"

#include <cmath>


class RaycastingScene : public Scene
{
    public:

        RaycastingScene();

        void render();


    private:

        ImageHandlerQt image;
        Sphere sphere;
        Cylinder cylinder;
        Cube cube;


        ColorRgba calculateColor(Position3d startPoint, Position3d interceptionPoint, Object* object, unsigned int depth);

        ColorRgba sendRay(Position3d startPoint, Position3d worldRayDirection, Object* sender, unsigned int depth);
};


#endif // RAYCASTINGSCENE_H
