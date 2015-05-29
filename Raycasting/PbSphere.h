#ifndef PB_SPHERE_H
#define PB_SPHERE_H


#include "PbObject.h"
#include "PbPosition3d.h"
#include <cmath>


class PbSphere : public PbObject
{
	public:

        explicit PbSphere(const char *materialfile, PbPosition3d center, float radius = 1.0f)
            : PbObject::PbObject(materialfile, "OBJSPHERE"),
              radius(radius)
        {
            this->center = center;
        }

        explicit PbSphere(const char *materialfile, float x, float y, float z, float radius = 1.0f, bool glass = false)
            : PbObject::PbObject(materialfile, "OBJSPHERE"),
              radius(radius)
        {
            center = PbPosition3d(x, y, z);
        }

        ~PbSphere() {}


		float get_radius() {return radius;}


        PbPosition3d getNormal(PbPosition3d point);
	
        PbPosition3d* intercept(PbPosition3d initialPoint, PbPosition3d rayDirection);

        float getScale_x() {return radius;}
        float getScale_y() {return radius;}
        float getScale_z() {return radius;}

	
	private:

		float radius;
};


#endif // PB_SPHERE_H
