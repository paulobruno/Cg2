#include "Sphere.h"


#define ZERO_THRESHOLD 0.0001


Sphere::Sphere()
    : Object()
{}


Sphere::Sphere(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects)
    : Object(transform, material, properties, effects)
{}


Position3d* Sphere::interceptedWithRay(Position3d rayOrigin, Position3d rayDirection)
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

    // adjust interception equation
    float a = (d_x * d_x) + (d_y * d_y) + (d_z * d_z);
    float b = 2 * ( (d_x * o_x) + (d_y * o_y) + (d_z * o_z) );
    float c = (o_x * o_x) + (o_y * o_y) + (o_z * o_z) - 1.0f;

    float delta = b*b - (4*a*c);

    if (delta <= 0)
    {
        return NULL;
    }

    // bhaskara
    float t1 = (- b + sqrt(delta)) / (2*a);
    float t2 = (- b - sqrt(delta)) / (2*a);


    if (t1 <= ZERO_THRESHOLD)
    {
        if (t2 <= ZERO_THRESHOLD)
        {
            return NULL;
        }
        else
        {
            // return the interception point in world coordinates
            Position3d localInterception(localRayOrigin + (localRayDirection * t2));

            Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

            Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

            return ( new Position3d(worldInterception) );
        }
    }
    else
    {
        if (t2 <= ZERO_THRESHOLD)
        {
            // return the interception point in world coordinates
            Position3d localInterception(localRayOrigin + (localRayDirection * t1));

            Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

            Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

            return ( new Position3d(worldInterception) );
        }
        else
        {
            if (t1 < t2)
            {
                // return the interception point in world coordinates
                Position3d localInterception(localRayOrigin + (localRayDirection * t1));

                Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

                Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

                return ( new Position3d(worldInterception) );
            }
            else
            {
                // return the interception point in world coordinates
                Position3d localInterception(localRayOrigin + (localRayDirection * t2));

                Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

                Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

                return ( new Position3d(worldInterception) );
            }
        }
    }
}
