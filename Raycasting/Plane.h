#ifndef PLANE_H
#define PLANE_H


#include "log.h"
#include "Position3d.h"
#include "Object.h"
#include "Matrix4.h"


class Plane : public Object
{
    public:

        Plane();
        Plane(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects);
        ~Plane() {}

        Position3d *interceptedWithRay(Position3d rayOrigin, Position3d rayDirection);
        Position3d getNormal(Position3d point);
};


#endif // PLANE_H
