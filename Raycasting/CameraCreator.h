#ifndef CAMERACREATOR_H
#define CAMERACREATOR_H


#include "BaseCreator.h"
#include "Object.h"
#include "Camera.h"


class CameraCreator : public BaseCreator
{
    public:

        Object* createObject() const
        {
            return new Camera();
        }
};


#endif // CAMERACREATOR_H
