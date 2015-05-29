#include "PbPlane.h"

#define DELTA 0.0001


PbPlane::PbPlane(const char *materialfile, PbPosition3d v1, PbPosition3d v2, PbPosition3d v3)
    : PbObject::PbObject(materialfile)
{
    points[0] = v1;
    points[1] = v2;
    points[2] = v3;

    minX = -DELTA + fmin(points[0].get_x(), fmin(points[1].get_x(), points[2].get_x()));
    maxX =  DELTA + fmax(points[0].get_x(), fmax(points[1].get_x(), points[2].get_x()));
    minY = -DELTA + fmin(points[0].get_y(), fmin(points[1].get_y(), points[2].get_y()));
    maxY =  DELTA + fmax(points[0].get_y(), fmax(points[1].get_y(), points[2].get_y()));
    minZ = -DELTA + fmin(points[0].get_z(), fmin(points[1].get_z(), points[2].get_z()));
    maxZ =  DELTA + fmax(points[0].get_z(), fmax(points[1].get_z(), points[2].get_z()));

    calculateNormal();


    center = (points[0] + points[2]) / 2.0f;

    distToCenter = normal.dotProduct(center);
}


PbPosition3d PbPlane::getNormal(PbPosition3d point)
{
    //if () verificar se pont faz parte do plano
        return normal;
}


PbPosition3d* PbPlane::intercept(PbPosition3d initialPoint, PbPosition3d rayDirection)
{
    float b = rayDirection.dotProduct(normal);
	
    if (!b)
	{
		return NULL;
	}


    float a = distToCenter - initialPoint.dotProduct(normal);

    float t = a/b;

    if (t < 0)
    {
        return NULL;
    }

    PbPosition3d *inters = new PbPosition3d(initialPoint + (rayDirection * t));


        if ( (inters->get_x() < minX) ||
             (inters->get_x() > maxX) ||
             (inters->get_y() < minY) ||
             (inters->get_y() > maxY) ||
             (inters->get_z() < minZ) ||
             (inters->get_z() > maxZ)
             )
        {
            //LOG("x: " << inters->get_x() << " y:" << inters->get_y() << " z: " << inters->get_z());

            return NULL;

        }


    return inters;
}


void PbPlane::calculateNormal()
{
    normal = (points[2] - points[0]).crossProduct((points[1] - points[0]));
    normal.normalize();
}


bool PbPlane::isInPlane(PbPosition3d point)
{
    if ( (point.get_x() < minX) ||
         (point.get_x() > maxX) ||
         (point.get_y() < minY) ||
         (point.get_y() > maxY) ||
         (point.get_z() < minZ) ||
         (point.get_z() > maxZ)
         )
    {
        return false;
    }

    return true;
}


float* PbPlane::paramIntercept(PbPosition3d initialPoint, PbPosition3d rayDirection)
{
    float b = rayDirection.dotProduct(normal);

    if (!b)
    {
        return NULL;
    }


    //float a = center.distance(PbPosition3d(0.0f, 0.0f, 0.0f)) - initialPoint.dotProduct(normal);
    float a = distToCenter - initialPoint.dotProduct(normal);

    float t = a/b;

    if (t < 0)
    {
        return NULL;
    }

    PbPosition3d *inters = new PbPosition3d(initialPoint + (rayDirection * t));

    //LOG("a: " << a << " b:" << b << " d: " << d << '\n');

    if (isInPlane(*inters))
    {
        return &t;
    }

    return NULL;
}
