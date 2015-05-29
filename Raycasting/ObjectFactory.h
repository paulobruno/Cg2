#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H


#include "BaseCreator.h"
#include "log.h"

#include <string>
#include <map>


class ObjectFactory
{
    public:

        bool registerType(std::string typeId, BaseCreator* creator);

        Object* create(std::string typeId);


    private:

        std::map<std::string, BaseCreator*> creators;
};

#endif // OBJECTFACTORY_H
