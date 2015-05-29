#ifndef SPHERECREATOR_H
#define SPHERECREATOR_H


#include "Object.h"
#include "BaseCreator.h"
//#include "Sphere.h"


class SphereCreator : public BaseCreator
{
    public:

        Object* createObject() const
        {
            return NULL;//new Sphere();
        }
};


#endif // SPHERECREATOR_H
