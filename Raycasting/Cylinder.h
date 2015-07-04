#ifndef CYLINDER_H
#define CYLINDER_H


#include "log.h"
#include "Position3d.h"
#include "Object.h"
#include "Matrix4.h"


class Cylinder : public Object
{
    public:

        Cylinder();
        Cylinder(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects);
        ~Cylinder() {}

        Position3d *interceptedWithRay(Position3d rayOrigin, Position3d rayDirection);
        Position3d getNormal(Position3d point);
};


#endif // CYLINDER_H
