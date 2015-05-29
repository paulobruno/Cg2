#ifndef OBJECTPROPERTIES_H
#define OBJECTPROPERTIES_H


#include "log.h"
#include <string>


class ObjectProperties
{
    public:

        ObjectProperties();
        ObjectProperties(std::string type, std::string name, std::string texture, std::string bump, bool enabled);
        ~ObjectProperties();

        void setType(std::string newType) {type = newType;}
        void setName(std::string newName) {name = newName;}
        void setTexture(std::string newTexture) {texture = newTexture;}
        void setBump(std::string newBump) {bump = newBump;}
        void setEnabled(bool newEnabled) {enabled = newEnabled;}


    private:

        std::string type, name, texture, bump;
        bool enabled;
};

#endif // OBJECTPROPERTIES_H
