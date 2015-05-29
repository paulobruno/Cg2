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


    protected:

        Transform transform;
        Material material;
        ObjectProperties properties;
        ObjectEffects effects;
        Position3d interceptionPosition;
};


#endif // OBJECT_H
