#ifndef PB_PLANE_H
#define PB_PLANE_H


#include "PbObject.h"
#include "PbPosition3d.h"
#include <cmath>


class PbPlane : public PbObject
{
    friend class PbCube;

	public:

        explicit PbPlane(const char *materialfile, PbPosition3d v1, PbPosition3d v2, PbPosition3d v3);

        ~PbPlane() {}


        //float get_distance() {return distance;}
        //PbPosition3d getDirection() {return direction;}
	

        PbPosition3d getNormal(PbPosition3d point);
        PbPosition3d* intercept(PbPosition3d initialPoint, PbPosition3d rayDirection);
	
	
    protected:

        bool isInPlane(PbPosition3d point);
        float* paramIntercept(PbPosition3d initialPoint, PbPosition3d rayDirection);


	private:

        PbPosition3d points[3];
        PbPosition3d normal;

        float minX, maxX, minY, maxY, minZ, maxZ;

        PbPosition3d center;
        float distToCenter;

        void calculateNormal();
};


#endif // PB_PLANE_H
