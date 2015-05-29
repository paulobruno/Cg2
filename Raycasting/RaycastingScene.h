#ifndef RAYCASTINGSCENE_H
#define RAYCASTINGSCENE_H


#include "ImageHandlerQt.h"
#include "Scene.h"
#include "ColorRgba.h"
#include "Position3d.h"

#include <cmath>


class RaycastingScene : public Scene
{
    public:

        RaycastingScene();

        void render();


    private:

        ImageHandlerQt image;


        ColorRgba calculateColor(Object object, Position3d position);

        Position3d interceptObjectWithRay(Position3d origin, Position3d direction);
};


#endif // RAYCASTINGSCENE_H
