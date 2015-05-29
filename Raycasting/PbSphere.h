#ifndef PB_SPHERE_H
#define PB_SPHERE_H


#include "PbObject.h"
#include "PbPosition3d.h"
#include <cmath>


class PbSphere : public PbObject
{
	public:

        explicit PbSphere(const char *materialfile, PbPosition3d center, float radius = 1.0f)
            : PbObject::PbObject(materialfile),
              center(center),
              radius(radius)
        {}

        explicit PbSphere(const char *materialfile, float x, float y, float z, float radius = 1.0f)
            : PbObject::PbObject(materialfile),
              center(PbPosition3d(x, y, z)),
              radius(radius)
        {}

        ~PbSphere() {}


		float get_radius() {return radius;}


        PbPosition3d getNormal(PbPosition3d point);
	
        PbPosition3d* intercept(PbPosition3d initialPoint, PbPosition3d rayDirection);
	
	
	private:

        PbPosition3d center;
		float radius;
};


#endif // PB_SPHERE_H
