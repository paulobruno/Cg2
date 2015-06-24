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
        Sphere(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects);
        ~Sphere() {}

        Position3d *interceptedWithRay(Position3d rayOrigin, Position3d rayDirection);
        Position3d getNormal(Position3d point) {return point;}
};

#endif // SPHERE_H
