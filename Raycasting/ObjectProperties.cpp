#include "ObjectProperties.h"


ObjectProperties::ObjectProperties()
{
    type = "";
    name = "";
    texture = "";
    bump = "";

    enabled =false;
}


ObjectProperties::ObjectProperties(std::string type, std::string name, std::string texture, std::string bump, bool enabled)
    : type(type)
    , name(name)
    , texture(texture)
    , bump(bump)
    , enabled(enabled)
{}


ObjectProperties::~ObjectProperties()
{}

