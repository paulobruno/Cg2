#ifndef PB_OBJECT_H
#define PB_OBJECT_H


#include "PbPosition3d.h"
#include "PbMaterial.h"
/*
enum PbObjType
{
    SPHERE = 0,
    PLANE = 1
};
*/

class PbObject
{
	public:

        explicit PbObject(/*PbPosition3d center, */const char *materialFile/*, PbObjType objType*/)
            : //center(center),
              mat(PbMaterial(materialFile))
              //objType(objType)
        {}
		virtual ~PbObject() {}
		
		virtual PbPosition3d* intercept(PbPosition3d initialPoint, PbPosition3d ray) = 0;

        /*PbPosition3d getCenter() {return center;}
        float get_x() {return center.get_x();}
        float get_y() {return center.get_y();}
        float get_z() {return center.get_z();}*/

       virtual PbPosition3d getNormal(PbPosition3d point) = 0;
        PbMaterial getMaterial() {return mat;}
        //PbObjType getType() {return objType;}


    protected:

        //PbPosition3d center;
        PbMaterial mat;
        //PbObjType objType;
};


#endif //  PB_OBJECT_H
