#ifndef BASECREATOR_H
#define BASECREATOR_H


#include "Object.h"


class BaseCreator
{
    public:

        BaseCreator() {}

        virtual Object* createObject() const = 0;
        virtual ~BaseCreator() {}
};


#endif // BASECREATOR_H
