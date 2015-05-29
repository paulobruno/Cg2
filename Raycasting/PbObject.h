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
              mat(PbMaterial(materialFile)),
              filemat(materialFile),
              mirror(false),
              glass(false),
              nWorld(0.0f),
              nObject(0.0f)
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

        void setMirror() {glass = false; mirror = true;}
        void setGlass(float nSup, float nObj) {mirror = false; glass = true; nWorld = nSup; nObject = nObj;}

        bool isMirror() {return mirror;}
        bool isGlass() {return glass;}
        bool getEtaWorld() {return nWorld;}
        bool getEtaObject() {return nObject;}

        std::string filemat;

    protected:

        bool mirror, glass;
        float nWorld, nObject;

        //PbPosition3d center;
        PbMaterial mat;
        //PbObjType objType;
};


#endif //  PB_OBJECT_H
