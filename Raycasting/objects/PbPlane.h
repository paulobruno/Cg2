#ifndef PB_PLANE_H
#define PB_PLANE_H

#define DELTA 0.0001

#include "../utils/PbPosition3d.h"
#include "../objects/PbObject.h"

#include <cmath>


class PbPlane : public PbObject
{
    friend class PbCube;

	public:

        // v1 = bottom left; v2 = bottom right; v3 = top right
        explicit PbPlane(const char *materialfile, PbPosition3d v1, PbPosition3d v2, PbPosition3d v3);

        ~PbPlane() {}


        //float get_distance() {return distance;}
        //PbPosition3d getDirection() {return direction;}
	

        PbPosition3d getNormal(PbPosition3d point);
        PbPosition3d* intercept(PbPosition3d initialPoint, PbPosition3d rayDirection);

        float getScale_x() {return maxX - DELTA;}
        float getScale_y() {return maxY - DELTA;}
        float getScale_z() {return maxZ - DELTA;}

        char getAxis() {return axis;}

	
    protected:

        bool isInPlane(PbPosition3d point);
        float* paramIntercept(PbPosition3d initialPoint, PbPosition3d rayDirection);


	private:

        PbPosition3d points[3];
        PbPosition3d normal;

        float minX, maxX, minY, maxY, minZ, maxZ;

        float distToCenter;

        char axis;

        void calculateNormal();
};


#endif // PB_PLANE_H
