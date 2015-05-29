#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "Position3d.h"


class Transform
{
    public:

        Transform()
            :
              scale(Position3d(1.0f, 1.0f, 1.0f)),
              rotation(Position3d(0.0f, 0.0f, 0.0f)),
              translation(Position3d(0.0f, 0.0f, 0.0f))
        {}
        Transform(Position3d scale, Position3d rotation, Position3d translation)
            :
              scale(scale),
              rotation(rotation),
              translation(translation)
        {}
        ~Transform() {}


        void setScale(Position3d s) {scale = s;}
        void setRotation(Position3d r) {rotation = r;}
        void setTranslation(Position3d t) {translation = t;}

        Position3d getScale() {return scale;}
        Position3d getRotation() {return rotation;}
        Position3d getTranslation() {return translation;}


    private:

        Position3d scale, rotation, translation;
};


#endif // TRANSFORM_H
