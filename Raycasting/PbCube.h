#ifndef PB_CUBE_H
#define PB_CUBE_H


#include "PbObject.h"
#include "PbPosition3d.h"
#include "PbPlane.h"

#include <cmath>
#include <vector>


class PbCube : public PbObject
{
	public:

        explicit PbCube(const char *materialfile, PbPlane p1, PbPlane p2, PbPlane p3, PbPlane p4, PbPlane p5, PbPlane p6);

        ~PbCube() {}


        PbPosition3d getNormal(PbPosition3d point);
	
        PbPosition3d* intercept(PbPosition3d initialPoint, PbPosition3d rayDirection);
	
	
	private:
		
        std::vector<PbPlane> faces;
};


#endif // PB_CUBE_H
