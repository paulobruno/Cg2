#ifndef EFFECTS_H
#define EFFECTS_H


class Effects
{
    public:

        Effects();
        Effects(float radius, float focalLenght, float depthOfField);
        ~Effects();


    private:

        float radius = 0.0f, focalLength = 0.0f, depthOfField = 0.0f;
};

#endif // EFFECTS_H
