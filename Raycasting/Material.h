#ifndef MATERIAL_H
#define MATERIAL_H


#include "ColorRgba.h"


class Material
{
    public:

        Material();
        Material(ColorRgba matKa, ColorRgba matKd, ColorRgba matKs, float matNi = 1.0f, unsigned int matSh = 0);
        Material(const char *materialName);

        void loadMaterial(const char *materialName);

        float* getKa() {return ka;}
        float* getKd() {return kd;}
        float* getKs() {return ks;}
        float* getTf() {return tf;}

        float getKaR() {return ka[0];}
        float getKaG() {return ka[1];}
        float getKaB() {return ka[2];}
        float getKaA() {return ka[3];}

        float getKdR() {return kd[0];}
        float getKdG() {return kd[1];}
        float getKdB() {return kd[2];}
        float getKdA() {return kd[3];}

        float getKsR() {return ks[0];}
        float getKsG() {return ks[1];}
        float getKsB() {return ks[2];}
        float getKsA() {return ks[3];}

        float getTfR() {return tf[0];}
        float getTfG() {return tf[1];}
        float getTfB() {return tf[2];}
        float getTfA() {return tf[3];}

        float getTransparency() {return transparency;}

        unsigned int getShininess() {return sh;}
        float getNi() {return ni;}


        void updateKa(ColorRgba matKa)
        {
            ka[0] = matKa.getRed();
            ka[1] = matKa.getGreen();
            ka[2] = matKa.getBlue();
            ka[3] = matKa.getAlpha();
        }

        void updateKd(ColorRgba matKd)
        {
            kd[0] = matKd.getRed();
            kd[1] = matKd.getGreen();
            kd[2] = matKd.getBlue();
            kd[3] = matKd.getAlpha();
        }

        void updateKs(ColorRgba matKs)
        {
            ks[0] = matKs.getRed();
            ks[1] = matKs.getGreen();
            ks[2] = matKs.getBlue();
            ks[3] = matKs.getAlpha();
        }

        void updateShininess(float newShininess) {sh = newShininess;}
        void updateReflection(float newReflection) {reflection = newReflection;}
        void updateGlossyReflection(float newGlossyReflection) {glossyReflection = newGlossyReflection;}
        void updateRefraction(float newRefraction) {refraction = newRefraction;}
        void updateGlossyRefraction(float newGlossyRefraction) {glossyRefraction = newGlossyRefraction;}


    private:

        float ka[4], kd[4], ks[4], tf[4];
        unsigned int sh = 0;
        float ni, transparency, reflection, glossyReflection, refraction, glossyRefraction;
};


#endif // MATERIAL_H
