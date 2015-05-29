#ifndef EFFECTSPARSER_H
#define EFFECTSPARSER_H


#include "log.h"
#include "tinyxml2.h"
#include "Effects.h"


class EffectsParser
{
    public:

        EffectsParser() {}
        ~EffectsParser() {}

        EffectsParser(const EffectsParser& other)
            : effects(other.effects)
        {}

        EffectsParser& operator= (const EffectsParser& other)
        {
            if (this != &other)
            {
                effects = other.effects;
            }

            return *this;
        }


        Effects parse(tinyxml2::XMLNode* parent);


    private:

        Effects effects;
};


#endif // EFFECTSPARSER_H
