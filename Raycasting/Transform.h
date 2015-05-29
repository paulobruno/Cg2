#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "Position3d.h"


class Transform
{
    public:

        Transform()
            : scale(Position3d(1.0f, 1.0f, 1.0f))
            , rotation(Position3d(0.0f, 0.0f, 0.0f))
            , position(Position3d(0.0f, 0.0f, 0.0f))
        {}
        Transform(Position3d scale, Position3d rotation, Position3d position)
            : scale(scale)
            , rotation(rotation)
            , position(position)
        {}
        ~Transform() {}


        void setScale(Position3d s) {scale = s;}
        void setRotation(Position3d r) {rotation = r;}
        void setPosition(Position3d p) {position = p;}

        Position3d getScale() {return scale;}
        Position3d getRotation() {return rotation;}
        Position3d getPosition() {return position;}

        float* getTransformationMatrix();
        float* getInverseTransformationMatrix();


    private:

        Position3d scale, rotation, position;
};


#endif // TRANSFORM_H
