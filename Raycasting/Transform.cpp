#include "Transform.h"


Transform::Transform()
    : scale(Position3d(1.0f, 1.0f, 1.0f))
    , rotation(Position3d(0.0f, 0.0f, 0.0f))
    , position(Position3d(0.0f, 0.0f, 0.0f))
    , scaleMatrix(Matrix4())
    , rotationMatrix(Matrix4())
    , translationMatrix(Matrix4())
    , inverseScaleMatrix(Matrix4())
    , inverseRotationMatrix(Matrix4())
    , inverseTranslationMatrix(Matrix4())
{
    createScaleMatrixX();
    createRotationMatrix();
    createTranslationMatrixX();

    createInverseScaleMatrixX();
    createInverseRotationMatrix();
    createInverseTranslationMatrixX();
}


Transform::Transform(Position3d scale, Position3d rotation, Position3d position)
    : scale(scale)
    , rotation(rotation)
    , position(position)
    , scaleMatrix(Matrix4())
    , rotationMatrix(Matrix4())
    , translationMatrix(Matrix4())
    , inverseScaleMatrix(Matrix4())
    , inverseRotationMatrix(Matrix4())
    , inverseTranslationMatrix(Matrix4())
{
    createScaleMatrixX();
    createRotationMatrix();
    createTranslationMatrixX();

    createInverseScaleMatrixX();
    createInverseRotationMatrix();
    createInverseTranslationMatrixX();
}


void Transform::createRotationMatrix()
{
    float s_x = sin(rotation.get_x());
    float s_y = sin(rotation.get_y());
    float s_z = sin(rotation.get_z());

    float c_x = cos(rotation.get_x());
    float c_y = cos(rotation.get_y());
    float c_z = cos(rotation.get_z());


    rotationMatrix[0] = c_z * c_y;
    rotationMatrix[1] = ((-s_z) * c_x) + (c_z * s_y * s_x);
    rotationMatrix[2] = (s_z * s_x) + (c_z * s_y * c_x);

    rotationMatrix[4] = s_z * c_y;
    rotationMatrix[5] = (c_z * c_x) + (s_z * s_y * s_x);
    rotationMatrix[6] = (c_z * (-s_x)) + (s_z * s_y * c_x);

    rotationMatrix[8] = -s_y;
    rotationMatrix[9] = c_y * s_x;
    rotationMatrix[10] = c_y * c_x;
}


void Transform::createInverseRotationMatrix()
{
    inverseRotationMatrix = rotationMatrix.transpose();
}


void Transform::createScaleMatrixX()
{
    scaleMatrix[0] = scale.get_x();
    scaleMatrix[5] = scale.get_y();
    scaleMatrix[10] = scale.get_z();
}


void Transform::createInverseScaleMatrixX()
{
    inverseScaleMatrix[0] = 1.0f / scale.get_x();
    inverseScaleMatrix[5] = 1.0f / scale.get_y();
    inverseScaleMatrix[10] = 1.0f / scale.get_z();
}


void Transform::createTranslationMatrixX()
{
    translationMatrix[3] = position.get_x();
    translationMatrix[7] = position.get_y();
    translationMatrix[11] = position.get_z();
}


void Transform::createInverseTranslationMatrixX()
{
    inverseTranslationMatrix[3] = -position.get_x();
    inverseTranslationMatrix[7] = -position.get_y();
    inverseTranslationMatrix[11] = -position.get_z();
}
