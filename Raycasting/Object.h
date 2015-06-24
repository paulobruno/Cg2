#ifndef OBJECT_H
#define OBJECT_H


#include "Material.h"
#include "Position3d.h"
#include "Transform.h"
#include "ObjectProperties.h"
#include "ObjectEffects.h"

#include <string>


class Object
{
    public:

        Object();
        Object(Transform transform, Material material, ObjectProperties properties, ObjectEffects effects);
        ~Object();

        std::string getId() {return nullptr;}

        Transform getTransform() {return transform;}

        Material getMaterial() {return material;}

        ObjectProperties getProperties() {return properties;}

        virtual Position3d* interceptedWithRay(Position3d rayOrigin, Position3d rayDirection) = 0;
        virtual Position3d getNormal(Position3d point) = 0;


    protected:

        Transform transform;
        Material material;
        ObjectProperties properties;
        ObjectEffects effects;
        Position3d interceptionPosition;
};


#endif // OBJECT_H
