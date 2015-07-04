#ifndef CUBE_H
#define CUBE_H


#include "log.h"
#include "Position3d.h"
#include "Object.h"
#include "Matrix4.h"


class Cube : public Object
{
    public:

        Cube();
        Cube(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects);
        ~Cube() {}

        Position3d *interceptedWithRay(Position3d rayOrigin, Position3d rayDirection);
        Position3d getNormal(Position3d point);
};


#endif // CUBE_H
