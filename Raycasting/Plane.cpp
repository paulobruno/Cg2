#include "Plane.h"


#define ZERO_THRESHOLD 0.0001


Plane::Plane()
    : Object()
{

}


Plane::Plane(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects)
    : Object(transform, material, properties, effects)
{}


Position3d* Plane::interceptedWithRay(Position3d rayOrigin, Position3d rayDirection)
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
    float a = (d_x * d_x) + (d_z * d_z);
    float b = 2 * ( (d_x * o_x) + (d_z * o_z) );
    float c = (o_x * o_x) + (o_z * o_z) - 1.0f;

    float delta = b*b - (4*a*c);

    if (delta <= 0)
    {
        return NULL;
    }

    // bhaskara
    float t1 = (- b + sqrt(delta)) / (2*a);
    float t2 = (- b - sqrt(delta)) / (2*a);

    return NULL;
}


Position3d Plane::getNormal(Position3d point)
{
    Matrix4 worldToLocalCoordinate = transform.getInverseRotationMatrix()
                                   * transform.getInverseScalMatrix()
                                   * transform.getInverseTranslationMatrix();

    Position3d localPoint = worldToLocalCoordinate.applyMatrix(point);

    Position3d localNormal;

    // superfície lateral
    localNormal = Position3d(localPoint.get_x(), 0.0f, localPoint.get_z());


    Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

    Position3d worldNormal = localToWorldCoordinate.applyMatrix(localNormal);
    worldNormal.normalize();


    return worldNormal;
}
