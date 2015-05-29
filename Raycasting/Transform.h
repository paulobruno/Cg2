#ifndef TRANSFORM_H
#define TRANSFORM_H


#include "Position3d.h"
#include "Matrix4.h"

#include <cmath>


class Transform
{
    public:

        Transform();
        Transform(Position3d scale, Position3d rotation, Position3d position);
        ~Transform() {}


        void setScale(Position3d s) {scale = s; createScaleMatrixX(); createInverseScaleMatrixX();}
        void setRotation(Position3d r) {rotation = r; createRotationMatrix(); createInverseRotationMatrix();}
        void setPosition(Position3d p) {position = p; createTranslationMatrixX(); createInverseTranslationMatrixX();}

        Position3d getScale() {return scale;}
        Position3d getRotation() {return rotation;}
        Position3d getPosition() {return position;}

        Matrix4 getScalMatrix() {return scaleMatrix;}
        Matrix4 getRotationMatrix() {return rotationMatrix;}
        Matrix4 getTranslationMatrix() {return translationMatrix;}

        Matrix4 getInverseScalMatrix() {return inverseScaleMatrix;}
        Matrix4 getInverseRotationMatrix() {return inverseRotationMatrix;}
        Matrix4 getInverseTranslationMatrix() {return inverseTranslationMatrix;}


    private:

        Position3d scale, rotation, position;
        Matrix4 scaleMatrix, rotationMatrix, translationMatrix;
        Matrix4 inverseScaleMatrix, inverseRotationMatrix, inverseTranslationMatrix;


        void createRotationMatrix();
        void createScaleMatrixX();
        void createTranslationMatrixX();

        void createInverseRotationMatrix();
        void createInverseScaleMatrixX();
        void createInverseTranslationMatrixX();
};


#endif // TRANSFORM_H
