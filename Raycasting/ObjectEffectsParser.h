#ifndef OBJECTEFFECTSPARSER_H
#define OBJECTEFFECTSPARSER_H


#include "log.h"
#include "tinyxml2.h"
#include "ObjectEffects.h"
#include "Position3d.h"


class ObjectEffectsParser
{
    public:

        ObjectEffectsParser() {}
        ~ObjectEffectsParser() {}

        ObjectEffectsParser(const ObjectEffectsParser& other)
            : effects(other.effects)
        {}

        ObjectEffectsParser& operator= (const ObjectEffectsParser& other)
        {
            if (this != &other)
            {
                effects = other.effects;
            }

            return *this;
        }


        ObjectEffects parse(tinyxml2::XMLNode* objectEffectsNode);


    private:

        ObjectEffects effects;


        void parseEffectsMotion(tinyxml2::XMLElement* effectsElement);
        void parseEffectsTranslate(tinyxml2::XMLElement* effectsElement);
        void parseEffectsRotate(tinyxml2::XMLElement* effectsElement);
};


#endif // OBJECTEFFECTSPARSER_H
