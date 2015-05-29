#ifndef PBTRANSFORM_H
#define PBTRANSFORM_H


#include "PbPosition3d.h"


class PbTransform
{
    public:

        PbTransform()
            :
              scale(PbPosition3d(1.0f, 1.0f, 1.0f)),
              rotation(PbPosition3d(0.0f, 0.0f, 0.0f)),
              translation(PbPosition3d(0.0f, 0.0f, 0.0f))
        {}
        PbTransform(PbPosition3d scale, PbPosition3d rotation, PbPosition3d translation)
            :
              scale(scale),
              rotation(rotation),
              translation(translation)
        {}
        ~PbTransform();


        void setScale(PbPosition3d s) {scale = s;}
        void setRotation(PbPosition3d r) {rotation = r;}
        void setTranslation(PbPosition3d t) {translation = t;}

        PbPosition3d getScale() {return scale;}
        PbPosition3d getRotation() {return rotation;}
        PbPosition3d getTranslation() {return translation;}


    private:

        PbPosition3d scale, rotation, translation;

};

#endif // PBTRANSFORM_H
