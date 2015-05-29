#ifndef PB_CYLINDER_H
#define PB_CYLINDER_H


#include "PbObject.h"
#include "PbPosition3d.h"
#include <cmath>



class PbCylinder : public PbObject
{
	public:

        explicit PbCylinder(const char *materialfile, PbPosition3d center, float yMin, float yMax, float radius = 1.0f)
            : PbObject::PbObject(materialfile, "OBJCYLINDER"),
              radius(radius),
              yMin(yMin),
              yMax(yMax)
        {
            this->center = center;
        }

        explicit PbCylinder(const char *materialfile, float x, float y, float z, float yMin, float yMax, float radius = 1.0f)
            : PbObject::PbObject(materialfile, "OBJCYLINDER"),
              radius(radius),
              yMin(yMin),
              yMax(yMax)
        {
            center = PbPosition3d(x, y, z);
        }

        ~PbCylinder() {}


		float get_radius() {return radius;}


        PbPosition3d getNormal(PbPosition3d point);
	
        PbPosition3d* intercept(PbPosition3d initialPoint, PbPosition3d rayDirection);

        float getScale_x() {return radius;}
        float getScale_y() {return radius;}
        float getScale_z() {return radius;}
	
	
	private:

        float radius, yMin, yMax;
        float tInf, tSup, tCyl;

        float* interceptInf(PbPosition3d initialPoint, PbPosition3d rayDirection);
        float* interceptSup(PbPosition3d initialPoint, PbPosition3d rayDirection);
        float* interceptCyl(PbPosition3d initialPoint, PbPosition3d rayDirection);
};


#endif // PB_CYLINDER_H

