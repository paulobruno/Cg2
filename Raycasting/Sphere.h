#ifndef SPHERE_H
#define SPHERE_H


#include "log.h"
#include "Position3d.h"
#include "Object.h"
#include "Matrix4.h"


class Sphere : public Object
{
    public:

        Sphere();

        Position3d *interceptedWithRay(Position3d rayOrigin, Position3d rayDirection);
};

#endif // SPHERE_H
