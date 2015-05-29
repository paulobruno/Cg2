#ifndef SPHERE_H
#define SPHERE_H


#include "log.h"
#include "Position3d.h"
#include "Object.h"


class Sphere : public Object
{
    public:

        Sphere();

        bool interceptedWithRay(Position3d rayOrigin, Position3d rayDirection);
};

#endif // SPHERE_H
