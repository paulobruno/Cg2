#ifndef CAMERA_H
#define CAMERA_H


#include "Position3d.h"

#include <cmath>


class Camera
{
    public:

        explicit Camera();
        explicit Camera(Position3d camEye, Position3d camLookAt);
        explicit Camera(Position3d camEye, Position3d camLookAt, Position3d camViewUp);

        explicit Camera(float eye_x, float eye_y, float eye_z,
                          float lookAt_x, float lookAt_y, float lookAt_z);
        explicit Camera(float eye_x, float eye_y, float eye_z,
                          float lookAt_x, float lookAt_y, float lookAt_z,
                          float viewUp_x, float viewUp_y, float viewUp_z);

        virtual ~Camera() {}


        void updateEye(Position3d camEye);
        void updateEye(float x, float y, float z);

        void updateLookAt(Position3d camLookAt);
        void updateLookAt(float x, float y, float z);

        void updateViewUp(Position3d camViewUp);
        void updateViewUp(float x, float y, float z);

        void updateCamera(Position3d camEye, Position3d camLookAt);
        void updateCamera(Position3d camEye, Position3d camLookAt, Position3d camViewUp);
        void updateCamera(float eye_x, float eye_y, float eye_z,
                          float lookAt_x, float lookAt_y, float lookAt_z);
        void updateCamera(float eye_x, float eye_y, float eye_z,
                          float lookAt_x, float lookAt_y, float lookAt_z,
                          float viewUp_x, float viewUp_y, float viewUp_z);


        Position3d getEye() {return eye;}
        Position3d getLookAt() {return lookAt;}
        Position3d getViewUp() {return viewUp;}

        float getEye_x() {return eye.get_x();}
        float getEye_y() {return eye.get_y();}
        float getEye_z() {return eye.get_z();}

        float getLookAt_x() {return lookAt.get_x();}
        float getLookAt_y() {return lookAt.get_y();}
        float getLookAt_z() {return lookAt.get_z();}

        float* getMatrix() {return matrix;}


        Position3d camToWorld(Position3d cameraPoint);
        Position3d worldToCam(Position3d worldPoint);


        Camera& operator= (const Camera &cam);


    private:

        float matrix[16];
        Position3d eye, lookAt, viewUp;

        void createMatrix();
};


#endif // CAMERA_H
