#include "PbCube.h"

PbCube::PbCube(const char *materialfile, PbPlane p1, PbPlane p2, PbPlane p3, PbPlane p4, PbPlane p5, PbPlane p6)
    : PbObject::PbObject(materialfile)
{
    faces.reserve(6);
	
	faces.push_back(p1);
	faces.push_back(p2);
	faces.push_back(p3);
	faces.push_back(p4);
	faces.push_back(p5);
	faces.push_back(p6);
}


PbPosition3d PbCube::getNormal(PbPosition3d point)
{
    if (faces[0].isInPlane(point))
    {
        return faces[0].getNormal(point);
    }
    else if (faces[1].isInPlane(point))
    {
        return faces[1].getNormal(point);
    }
    else if (faces[2].isInPlane(point))
    {
        return faces[2].getNormal(point);
    }
    else if (faces[3].isInPlane(point))
    {
        return faces[3].getNormal(point);
    }
    else if (faces[4].isInPlane(point))
    {
        return faces[4].getNormal(point);
    }
    else
    {
        return faces[5].getNormal(point);
    }
}
	
PbPosition3d* PbCube::intercept(PbPosition3d initialPoint, PbPosition3d rayDirection)
{
    float* t = faces[0].paramIntercept(initialPoint, rayDirection);

    for (unsigned int i = 1; i < 6; ++i)
    {
        if (t)
        {
            float* t_aux = faces[i].paramIntercept(initialPoint, rayDirection);

            if (t_aux)
            {
                if (*t_aux < *t)
                {
                    t = t_aux;
                }
            }
        }
        else
        {
            t = faces[i].paramIntercept(initialPoint, rayDirection);
        }
    }


    if (t)
    {
        return (new PbPosition3d(initialPoint + (rayDirection * (*t))));
    }


    return NULL;
}
