#include "ObjectFactory.h"


bool ObjectFactory::registerType(std::string typeId, BaseCreator* creator)
{
    std::map<std::string, BaseCreator*>::iterator it = creators.find(typeId);

    if (it != creators.end())
    {
        delete creator;
        return false;
    }

    creators[typeId] = creator;

    return true;
}


Object* ObjectFactory::create(std::string typeId)
{
    std::map<std::string, BaseCreator*>::iterator it = creators.find(typeId);

    if (it == creators.end())
    {
        LOGerr("Could not find type " << typeId);
        return NULL;
    }

    BaseCreator* creator = (*it).second;

    return creator->createObject();
}
