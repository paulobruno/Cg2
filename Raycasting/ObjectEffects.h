#ifndef OBJECTEFFECTS_H
#define OBJECTEFFECTS_H


#include "Position3d.h"


class ObjectEffects
{
    public:

        ObjectEffects()
            : motion(false)
            , translate(Position3d(0.0f, 0.0f, 0.0f))
            , rotate(Position3d(0.0f, 0.0f, 0.0f))
        {}

        ObjectEffects(bool motion, Position3d translate, Position3d rotate)
            : motion(motion)
            , translate(translate)
            , rotate(rotate)
        {}

        ~ObjectEffects() {}


        void updateMotion(bool newMotion) {motion = newMotion;}
        void updateTranslate(Position3d newTranslate) {translate = newTranslate;}
        void updateRotate(Position3d newRotate) {rotate = newRotate;}


    private:

        bool motion;
        Position3d translate, rotate;
};

#endif // OBJECTEFFECTS_H
