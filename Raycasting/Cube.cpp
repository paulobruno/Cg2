#include "Cube.h"


#define ZERO_THRESHOLD 0.0001


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
    float d_x = localRayDirection.get_x();
    float d_y = localRayDirection.get_y();
    float d_z = localRayDirection.get_z();

    // ray initial point
    float o_x = localRayOrigin.get_x();
    float o_y = localRayOrigin.get_y();
    float o_z = localRayOrigin.get_z();


    float t = 0.0f;


    if ((d_x > 0.0f - ZERO_THRESHOLD) && (d_x < 0.0f + ZERO_THRESHOLD))
    {
        if ((d_y > 0.0f - ZERO_THRESHOLD) && (d_y < 0.0f + ZERO_THRESHOLD))
        {
            if (dz < 0.0f)
            {
                t = (1.0f - o_z) / d_z;
            }
            else
            {
                t = (-1.0f - o_z) / d_z;
            }
        }
        else if (dy < 0.0f)
        {
            if ((d_z > 0.0f - ZERO_THRESHOLD) && (d_z < 0.0f + ZERO_THRESHOLD))
            {
                t = (1.0f - o_y) / d_y;
            }
            else if (dz < 0.0f)
            {
                float t1 = (1.0f - o_y) / d_y;
                float t2 = (1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
            else
            {
                float t1 = (1.0f - o_y) / d_y;
                float t2 = (-1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
        }
        else
        {
            if ((d_z > 0.0f - ZERO_THRESHOLD) && (d_z < 0.0f + ZERO_THRESHOLD))
            {
                t = (1.0f - o_y) / d_y;
            }
            else if (dz < 0.0f)
            {
                float t1 = (-1.0f - o_y) / d_y;
                float t2 = (1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
            else
            {
                float t1 = (-1.0f - o_y) / d_y;
                float t2 = (-1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
        }
    }
    else if (d_x < 0.0f)
    {
        if ((d_y > 0.0f - ZERO_THRESHOLD) && (d_y < 0.0f + ZERO_THRESHOLD))
        {
            if (dz < 0.0f)
            {
                t = (1.0f - o_z) / d_z;
            }
            else
            {
                t = (-1.0f - o_z) / d_z;
            }
        }
        else if (dy < 0.0f)
        {
            if ((d_z > 0.0f - ZERO_THRESHOLD) && (d_z < 0.0f + ZERO_THRESHOLD))
            {
                t = (1.0f - o_z) / d_z;
            }
            else if (dz < 0.0f)
            {
                float t1 = (1.0f - o_y) / d_y;
                float t2 = (1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
            else
            {
                float t1 = (1.0f - o_y) / d_y;
                float t2 = (-1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
        }
        else
        {
            if ((d_z > 0.0f - ZERO_THRESHOLD) && (d_z < 0.0f + ZERO_THRESHOLD))
            {
                t = (1.0f - o_z) / d_z;
            }
            if (dz < 0.0f)
            {
                float t1 = (-1.0f - o_y) / d_y;
                float t2 = (1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
            else
            {
                float t1 = (-1.0f - o_y) / d_y;
                float t2 = (-1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
        }
    }
    else
    {
        if ((d_y > 0.0f - ZERO_THRESHOLD) && (d_y < 0.0f + ZERO_THRESHOLD))
        {
            if (dz < 0.0f)
            {
                t = (1.0f - o_z) / d_z;
            }
            else
            {
                t = (-1.0f - o_z) / d_z;
            }
        }
        else if (dy < 0.0f)
        {
            if (dz < 0.0f)
            {
                float t1 = (1.0f - o_y) / d_y;
                float t2 = (1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
            else
            {
                float t1 = (1.0f - o_y) / d_y;
                float t2 = (-1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
        }
        else
        {
            if (dz < 0.0f)
            {
                float t1 = (-1.0f - o_y) / d_y;
                float t2 = (1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
            else
            {
                float t1 = (-1.0f - o_y) / d_y;
                float t2 = (-1.0f - o_z) / d_z;

                t = t1 <= t2 ? t1 : t2;
            }
        }
    }
}


Position3d Cube::getNormal(Position3d point)
{
    Matrix4 worldToLocalCoordinate = transform.getInverseRotationMatrix()
                                   * transform.getInverseScalMatrix()
                                   * transform.getInverseTranslationMatrix();

    worldToLocalCoordinate *= transform.getInverseTranslationMatrix();

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


    Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

    Position3d worldNormal = localToWorldCoordinate.applyMatrix(localNormal);
    worldNormal.normalize();


    return worldNormal;
}
