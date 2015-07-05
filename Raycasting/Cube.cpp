#include "Cube.h"


#define DELTA 0.001
#define ZERO_THRESHOLD 0.0001
#define MAX_VALUE 9999.0f


Cube::Cube()
    : Object()
{

}


Cube::Cube(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects)
    : Object(transform, material, properties, effects)
{}


Position3d* Cube::interceptedWithRay(Position3d rayOrigin, Position3d rayDirection)
{
    Matrix4 worldToLocalCoordinate = transform.getInverseRotationMatrix() * transform.getInverseScalMatrix();

    Position3d localRayDirection = worldToLocalCoordinate.applyMatrix(rayDirection);

    worldToLocalCoordinate *= transform.getInverseTranslationMatrix();

    Position3d localRayOrigin = worldToLocalCoordinate.applyMatrix(rayOrigin);


    // vector ray direction
    d_x = localRayDirection.get_x();
    d_y = localRayDirection.get_y();
    d_z = localRayDirection.get_z();

    // ray initial point
    o_x = localRayOrigin.get_x();
    o_y = localRayOrigin.get_y();
    o_z = localRayOrigin.get_z();



    //LOG("x: " << d_x << "\ty: " << d_y << "\tz: " << d_z);


    bool hittedX = false;
    bool hittedY = false;
    bool hittedZ = false;


    if (d_x < 0.0f)
    {
        hittedX = checkRayPlusPlaneX();
    }
    else
    {
        hittedX = checkRayMinusPlaneX();
    }

    if (d_y < 0.0f)
    {
        hittedY = checkRayPlusPlaneY();
    }
    else
    {
        hittedY = checkRayMinusPlaneY();
    }

    if (d_z < 0.0f)
    {
        hittedZ = checkRayPlusPlaneZ();
    }
    else
    {
        hittedZ = checkRayMinusPlaneZ();
    }


    float t = MAX_VALUE;

    if (hittedX)
    {
        if (hittedY)
        {
            if (hittedZ)
            {
                t = tx <= ty ? tx : ty;
                t = tz <= t ? tz : t;
            }
            else
            {
                t = tx <= ty ? tx : ty;
            }
        }
        else
        {
            if (hittedZ)
            {
                t = tx <= tz ? tx : tz;
            }
            else
            {
                t = tx;
            }
        }
    }
    else
    {
        if (hittedY)
        {
            if (hittedZ)
            {
                t = ty <= tz ? ty : tz;
            }
            else
            {
                t = ty;
            }
        }
        else
        {
            if (hittedZ)
            {
                t = tz;
            }
            else
            {
                return NULL;
            }
        }
    }


    // return the interception point in world coordinates
    Position3d localInterception(localRayOrigin + (localRayDirection * t));

    Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

    Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

    return ( new Position3d(worldInterception) );
}


bool Cube::checkRayPlusPlaneX()
{
    tx = (1.0f - o_x) / d_x;
    float y1 = o_y + tx*d_y;
    float z1 = o_z + tx*d_z;

    bool checkY = ((y1 > -1.0f - DELTA) && (y1 < 1.0f + DELTA));
    bool checkZ = ((z1 > -1.0f - DELTA) && (z1 < 1.0f + DELTA));

    if (checkY && checkZ)
    {
        return true;
    }

    return false;
}


bool Cube::checkRayPlusPlaneY()
{
    ty = (1.0f - o_y) / d_y;
    float x1 = o_x + ty*d_x;
    float z1 = o_z + ty*d_z;

    bool checkX = ((x1 > -1.0f - DELTA) && (x1 < 1.0f + DELTA));
    bool checkZ = ((z1 > -1.0f - DELTA) && (z1 < 1.0f + DELTA));

    if (checkX && checkZ)
    {
        return true;
    }

    return false;
}


bool Cube::checkRayPlusPlaneZ()
{
    tz = (1.0f - o_z) / d_z;
    float x1 = o_x + tz*d_x;
    float y1 = o_y + tz*d_y;

    bool checkX = ((x1 > -1.0f - DELTA) && (x1 < 1.0f + DELTA));
    bool checkY = ((y1 > -1.0f - DELTA) && (y1 < 1.0f + DELTA));

    if (checkX && checkY)
    {
        return true;
    }

    return false;
}


bool Cube::checkRayMinusPlaneX()
{
    tx = (-1.0f - o_x) / d_x;
    float y1 = o_y + tx*d_y;
    float z1 = o_z + tx*d_z;

    bool checkY = ((y1 > -1.0f - DELTA) && (y1 < 1.0f + DELTA));
    bool checkZ = ((z1 > -1.0f - DELTA) && (z1 < 1.0f + DELTA));

    if (checkY && checkZ)
    {
        return true;
    }

    return false;
}


bool Cube::checkRayMinusPlaneY()
{
    ty = (-1.0f - o_y) / d_y;
    float x1 = o_x + ty*d_x;
    float z1 = o_z + ty*d_z;

    bool checkX = ((x1 > -1.0f - DELTA) && (x1 < 1.0f + DELTA));
    bool checkZ = ((z1 > -1.0f - DELTA) && (z1 < 1.0f + DELTA));

    if (checkX && checkZ)
    {
        return true;
    }

    return false;
}


bool Cube::checkRayMinusPlaneZ()
{
    tz = (-1.0f - o_z) / d_z;
    float x1 = o_x + tz*d_x;
    float y1 = o_y + tz*d_y;

    bool checkX = ((x1 > -1.0f - DELTA) && (x1 < 1.0f + DELTA));
    bool checkY = ((y1 > -1.0f - DELTA) && (y1 < 1.0f + DELTA));

    if (checkX && checkY)
    {
        return true;
    }

    return false;
}


Position3d Cube::getNormal(Position3d point)
{
    Matrix4 worldToLocalCoordinate = transform.getInverseRotationMatrix()
                                   * transform.getInverseScalMatrix()
                                   * transform.getInverseTranslationMatrix();

    Position3d localPoint = worldToLocalCoordinate.applyMatrix(point);

    Position3d localNormal;


    if ((localPoint.get_x() > -1.0f - ZERO_THRESHOLD) && (localPoint.get_x() < -1.0f + ZERO_THRESHOLD))
    {
        localNormal = Position3d(-1.0f, 0.0f, 0.0f);
    }

    if ((localPoint.get_x() > 1.0f - ZERO_THRESHOLD) && (localPoint.get_x() < 1.0f + ZERO_THRESHOLD))
    {
        localNormal = Position3d(1.0f, 0.0f, 0.0f);
    }

    if ((localPoint.get_y() > -1.0f - ZERO_THRESHOLD) && (localPoint.get_y() < -1.0f + ZERO_THRESHOLD))
    {
        localNormal = Position3d(0.0f, -1.0f, 0.0f);
    }

    if ((localPoint.get_y() > 1.0f - ZERO_THRESHOLD) && (localPoint.get_y() < 1.0f + ZERO_THRESHOLD))
    {
        localNormal = Position3d(0.0f, 1.0f, 0.0f);
    }

    if ((localPoint.get_z() > -1.0f - ZERO_THRESHOLD) && (localPoint.get_z() < -1.0f + ZERO_THRESHOLD))
    {
        localNormal = Position3d(0.0f, 0.0f, -1.0f);
    }

    if ((localPoint.get_z() > 1.0f - ZERO_THRESHOLD) && (localPoint.get_z() < 1.0f + ZERO_THRESHOLD))
    {
        localNormal = Position3d(0.0f, 0.0f, 1.0f);
    }


    // returns direction
    Matrix4 localToWorldCoordinate = transform.getScalMatrix() * transform.getRotationMatrix();

    Position3d worldNormal = localToWorldCoordinate.applyMatrix(localNormal);
    worldNormal.normalize();

    return worldNormal;
}
