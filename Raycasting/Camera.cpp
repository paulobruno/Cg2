#include "Camera.h"

Camera::Camera()
{
    eye.set_pos(0.0f, 0.0f, -5.0f);
    lookAt.set_pos(0.0f, 0.0f, 0.0f);
    viewUp.set_pos(0.0f, 1.0f, -1.0f);

    this->createMatrix();
}


Camera::Camera(Position3d camEye, Position3d camLookAt)
    : eye(camEye),
      lookAt(camLookAt)
{
    viewUp = camEye;
    viewUp.set_y(viewUp.get_y() + 1.0f);

    this->createMatrix();
}


Camera::Camera(Position3d camEye, Position3d camLookAt, Position3d camViewUp)
    : eye(camEye),
      lookAt(camLookAt),
      viewUp(camViewUp)
{
    this->createMatrix();
}


Camera::Camera(float eye_x, float eye_y, float eye_z,
                     float lookAt_x, float lookAt_y, float lookAt_z)
{
    eye.set_pos(eye_x, eye_y, eye_z);
    lookAt.set_pos(lookAt_x, lookAt_y, lookAt_z);
    viewUp.set_pos(eye_x, eye_y + 1.0f, eye_z);

    this->createMatrix();
}


Camera::Camera(float eye_x, float eye_y, float eye_z,
                     float lookAt_x, float lookAt_y, float lookAt_z,
                     float viewUp_x, float viewUp_y, float viewUp_z)
{
    eye.set_pos(eye_x, eye_y, eye_z);
    lookAt.set_pos(lookAt_x, lookAt_y, lookAt_z);
    viewUp.set_pos(viewUp_x, viewUp_y, viewUp_z);

    this->createMatrix();
}


void Camera::updateEye(Position3d camEye)
{
    eye = camEye;
    this->createMatrix();
}


void Camera::updateEye(float x, float y, float z)
{
    eye.set_pos(x, y, z);
    this->createMatrix();
}


void Camera::updateLookAt(Position3d camLookAt)
{
    lookAt = camLookAt;
    this->createMatrix();
}


void Camera::updateLookAt(float x, float y, float z)
{
    lookAt.set_pos(x, y, z);
    this->createMatrix();
}


void Camera::updateViewUp(Position3d camViewUp)
{
    viewUp = camViewUp;
    this->createMatrix();
}


void Camera::updateViewUp(float x, float y, float z)
{
    viewUp.set_pos(x, y, z);
    this->createMatrix();
}


void Camera::updateCamera(Position3d camEye, Position3d camLookAt)
{
    eye = camEye;
    lookAt = camLookAt;

    viewUp = camEye;
    viewUp.set_y(viewUp.get_y() + 1.0f);

    this->createMatrix();
}


void Camera::updateCamera(Position3d camEye, Position3d camLookAt, Position3d camViewUp)
{
    eye = camEye;
    lookAt = camLookAt;
    viewUp = camViewUp;

    this->createMatrix();
}


void Camera::updateCamera(float eye_x, float eye_y, float eye_z,
                              float lookAt_x, float lookAt_y, float lookAt_z)
{
    eye.set_pos(eye_x, eye_y, eye_z);
    lookAt.set_pos(lookAt_x, lookAt_y, lookAt_z);
    viewUp.set_pos(eye_x, eye_y + 1.0f, eye_z);

    this->createMatrix();
}


void Camera::updateCamera(float eye_x, float eye_y, float eye_z,
                              float lookAt_x, float lookAt_y, float lookAt_z,
                              float viewUp_x, float viewUp_y, float viewUp_z)
{
    eye.set_pos(eye_x, eye_y, eye_z);
    lookAt.set_pos(lookAt_x, lookAt_y, lookAt_z);
    viewUp.set_pos(viewUp_x, viewUp_y, viewUp_z);

    this->createMatrix();
}


Position3d Camera::camToWorld(Position3d cameraPoint)
{
    float x = 0.0f, y = 0.0f, z = 0.0f;

    x = matrix[0]*cameraPoint.get_x()
      + matrix[1]*cameraPoint.get_y()
      + matrix[2]*cameraPoint.get_z()
      + eye.get_x();

    y = matrix[4]*cameraPoint.get_x()
      + matrix[5]*cameraPoint.get_y()
      + matrix[6]*cameraPoint.get_z()
      + eye.get_y();

    z = matrix[8]*cameraPoint.get_x()
      + matrix[9]*cameraPoint.get_y()
      + matrix[10]*cameraPoint.get_z()
      + eye.get_z();

    return Position3d(x, y, z);
}


Position3d Camera::worldToCam(Position3d worldPoint)
{
    float x = 0.0f, y = 0.0f, z = 0.0f;

    x = matrix[0]*worldPoint.get_x()
      + matrix[4]*worldPoint.get_y()
      + matrix[8]*worldPoint.get_z()
      + matrix[12];

    y = matrix[1]*worldPoint.get_x()
      + matrix[5]*worldPoint.get_y()
      + matrix[9]*worldPoint.get_z()
      + matrix[13];

    z = matrix[2]*worldPoint.get_x()
      + matrix[6]*worldPoint.get_y()
      + matrix[10]*worldPoint.get_z()
      + matrix[14];

    return Position3d(x, y, z);
}


void Camera::createMatrix()
{
    Position3d i, j, k, auxVector;

    // vector of z axis
    k = eye - lookAt;
    k.normalize();

    // vector of y axis
    auxVector = viewUp - eye;

    // i = aux x k
    i = auxVector.crossProduct(k);
    i.normalize();

    // vector of x axis, j = k x i
    j = k.crossProduct(i);

    // matrix of transformation
    matrix[0]  = i.get_x();
    matrix[1]  = j.get_x();
    matrix[2]  = k.get_x();
    matrix[3]  = 0.0;

    matrix[4]  = i.get_y();
    matrix[5]  = j.get_y();
    matrix[6]  = k.get_y();
    matrix[7]  = 0.0;

    matrix[8]  = i.get_z();
    matrix[9]  = j.get_z();
    matrix[10] = k.get_z();
    matrix[11] = 0.0;

    matrix[12] = -i.dotProduct(eye);
    matrix[13] = -j.dotProduct(eye);
    matrix[14] = -k.dotProduct(eye);
    matrix[15] = 1.0;
}


Camera& Camera::operator= (const Camera &cam)
{
    if (this != &cam)
    {
        for (int i = 0; i < 16; i++)
            matrix[i] = cam.matrix[i];

        eye = cam.eye;
        lookAt = cam.lookAt;
        viewUp = cam.viewUp;
    }

    return *this;
}
