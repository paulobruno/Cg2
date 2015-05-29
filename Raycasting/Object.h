#ifndef OBJECT_H
#define OBJECT_H


#include "Material.h"
#include "Position3d.h"
#include "Transform.h"

#include <string>


class Object
{
    public:

        Object();
        ~Object();

        std::string getId() {return nullptr;}

        Position3d getCenter() {return center;}

        Transform getTransform() {return transform;}

        Material getMaterial() {return material;}


    private:

        Position3d center;
        Transform transform;
        Material material;

};


#endif // OBJECT_H
