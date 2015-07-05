#include "Cylinder.h"


#define DELTA_Y 0.001
#define ZERO_THRESHOLD 0.0001


Cylinder::Cylinder()
    : Object()
{

}


Cylinder::Cylinder(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects)
    : Object(transform, material, properties, effects)
{}


Position3d* Cylinder::interceptedWithRay(Position3d rayOrigin, Position3d rayDirection)
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


    float y1 = o_y + t1*d_y;
    float y2 = o_y + t2*d_y;


    bool check1 = ((y1 > -1.0f - DELTA_Y) && (y1 < 1.0f + DELTA_Y));
    bool check2 = ((y2 > -1.0f - DELTA_Y) && (y2 < 1.0f + DELTA_Y));


    float tCyl = 0.0f;

    // intersects the middle of the cylinder
    if (check1 && check2)
    {
        // holds the minor
        tCyl = t1 <= t2 ? t1 : t2;

        // return the interception point in world coordinates
        Position3d localInterception(localRayOrigin + (localRayDirection * tCyl));

        Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

        Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

        return ( new Position3d(worldInterception) );
    }
    else
    {
        float tBase = (-1.0f - o_y) / d_y;
        float tTop = (1.0f - o_y) / d_y;

        if ((y1 > -1.0f - DELTA_Y) && (y2 > -1.0f - DELTA_Y))
        {
            if (check1)
            {
                // holds the minor
                tCyl = t1 <= tTop ? t1 : tTop;

                // return the interception point in world coordinates
                Position3d localInterception(localRayOrigin + (localRayDirection * tCyl));

                Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

                Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

                return ( new Position3d(worldInterception) );
            }
            else if (check2)
            {
                // holds the minor
                tCyl = t2 <= tTop ? t2 : tTop;

                // return the interception point in world coordinates
                Position3d localInterception(localRayOrigin + (localRayDirection * tCyl));

                Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

                Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

                return ( new Position3d(worldInterception) );
            }
            else
            {
                return NULL;
            }
        }
        else if ((y1 < 1.0f + DELTA_Y) && (y2 < 1.0f + DELTA_Y))
        {
            if (check1)
            {
                // holds the minor
                tCyl = t1 <= tBase ? t1 : tBase;

                // return the interception point in world coordinates
                Position3d localInterception(localRayOrigin + (localRayDirection * tCyl));

                Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

                Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

                return ( new Position3d(worldInterception) );
            }
            else if (check2)
            {
                // holds the minor
                tCyl = t2 <= tBase ? t2 : tBase;

                // return the interception point in world coordinates
                Position3d localInterception(localRayOrigin + (localRayDirection * tCyl));

                Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

                Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

                return ( new Position3d(worldInterception) );
            }
            else
            {
                return NULL;
            }
        }
        else
        {
            // holds the minor
            tCyl = tBase <= tTop ? tBase : tTop;

            // return the interception point in world coordinates
            Position3d localInterception(localRayOrigin + (localRayDirection * tCyl));

            Matrix4 localToWorldCoordinate = transform.getTranslationMatrix() * transform.getScalMatrix() * transform.getRotationMatrix();

            Position3d worldInterception = localToWorldCoordinate.applyMatrix(localInterception);

            return ( new Position3d(worldInterception) );
        }
    }
}


Position3d Cylinder::getNormal(Position3d point)
{
    Matrix4 worldToLocalCoordinate = transform.getInverseRotationMatrix()
                                   * transform.getInverseScalMatrix()
                                   * transform.getInverseTranslationMatrix();

    Position3d localPoint = worldToLocalCoordinate.applyMatrix(point);

    Position3d localNormal;


    // plano superior
    if ((localPoint.get_y() >= -1.0f - DELTA_Y) &&
        (localPoint.get_y() <=  1.0f + DELTA_Y))
    {
        localNormal = Position3d(0.0f, 1.0f, 0.0f);
    }

    // plano inferior
    if ((localPoint.get_y() >= -1.0f - DELTA_Y) &&
        (localPoint.get_y() <=  1.0f + DELTA_Y))
    {
        localNormal = Position3d(0.0f, -1.0f, 0.0f);
    }

    // superfície lateral
    localNormal = Position3d(localPoint.get_x(), 0.0f, localPoint.get_z());


    // returns direction
    Matrix4 localToWorldCoordinate = transform.getScalMatrix() * transform.getRotationMatrix();

    Position3d worldNormal = localToWorldCoordinate.applyMatrix(localNormal);
    worldNormal.normalize();


    return worldNormal;
}
