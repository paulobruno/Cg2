#ifndef PBOBJECT_H
#define PBOBJECT_H


#include "PbMaterial.h"
#include "PbPosition3d.h"
#include "PbTransform.h"
#include "PbFace.h"
#include "PbVertex.h"

#include <string>
#include <fstream>
#include <vector>
#include <list>

#ifdef __APPLE__
    #include "gl.h"
#else
    #include "GL/gl.h"
#endif

class PbObject
{
    public:

        PbObject();
        ~PbObject();

        std::string getId() {return nullptr;}

        PbPosition3d getCenter() {return center;}

        PbTransform getTransform() {return transform;}

        PbMaterial getMaterial() {return material;}



        void loadObject(std::string objName);
        void draw();


    private:

        PbPosition3d center;
        PbTransform transform;
        PbMaterial material;

        std::vector<PbVertex> vertexVector;
        std::list<PbFace> faceList;
};


#endif // PBOBJECT_H
