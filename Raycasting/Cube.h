#ifndef CUBE_H
#define CUBE_H


#include "log.h"
#include "Position3d.h"
#include "Object.h"
#include "Matrix4.h"

#include <QRgb>
#include <QColor>


class Cube : public Object
{
    public:

        Cube();
        Cube(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects);
        ~Cube() {}

        Position3d *interceptedWithRay(Position3d rayOrigin, Position3d rayDirection);
        Position3d getNormal(Position3d point);

        ColorRgba textureColor(QImage texture, Position3d* point);


    private:

        float tx, ty, tz;
        float d_x, d_y, d_z;
        float o_x, o_y, o_z;


        bool checkRayPlusPlaneX();
        bool checkRayPlusPlaneY();
        bool checkRayPlusPlaneZ();

        bool checkRayMinusPlaneX();
        bool checkRayMinusPlaneY();
        bool checkRayMinusPlaneZ();
};


#endif // CUBE_H
