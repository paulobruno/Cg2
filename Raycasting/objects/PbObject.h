#ifndef PB_OBJECT_H
#define PB_OBJECT_H


#include "../utils/PbPosition3d.h"
#include "../objects/PbMaterial.h"


class PbObject
{
	public:

        explicit PbObject(/*PbPosition3d center, */const char *materialFile/*, PbObjType objType*/, std::string id)
            : //center(center),
              mat(PbMaterial(materialFile)),
              mirror(false),
              glass(false),
              objId(id)
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
        PbPosition3d getCenter() {return center;}

        virtual float getScale_x() = 0;
        virtual float getScale_y() = 0;
        virtual float getScale_z() = 0;


        void setMirror() {glass = false; mirror = true;}
        void setGlass() {mirror = true; glass = true; /*mat = PbMaterial("Black.mtl");*//* nWorld = nSup; nObject = nObj;*/}

        bool isMirror() {return mirror;}
        bool isGlass() {return glass;}

        std::string getId() {return objId;}

        virtual char getAxis() {return '\0';}


    protected:

        std::string objId;
        bool mirror, glass;
        //float nWorld, nObject;

        PbPosition3d center;
        PbMaterial mat;
        //PbObjType objType;
};


#endif //  PB_OBJECT_H
