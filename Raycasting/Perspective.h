#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H


class Perspective
{
    public:

        Perspective();
        Perspective(float fieldOfView, float near, float far, unsigned int width, unsigned int height);
        ~Perspective();


    private:

        float fieldOfView = 45.0f, near = 0.01f, far = 120000.0f;
        unsigned int width = 640, height = 480;
};


#endif // PERSPECTIVE_H
