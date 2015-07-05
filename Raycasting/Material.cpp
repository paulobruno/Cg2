#include "Material.h"


#include <string>
#include <fstream>
#include <iostream>


Material::Material()
{/*
    ka[0] = 0.2f;
    ka[1] = 0.2f;
    ka[2] = 0.2f;
    ka[3] = 1.0f;

    kd[0] = 0.8f;
    kd[1] = 0.8f;
    kd[2] = 0.8f;
    kd[3] = 1.0f;

    ks[0] = 1.0f;
    ks[1] = 1.0f;
    ks[2] = 1.0f;
    ks[3] = 1.0f;

    sh = 0.0f;
    ni = 1.0f;
    transparency = 1.0f;
    */

    ka[0] = 0.25f;
    ka[1] = 0.25f;
    ka[2] = 0.25f;
    ka[3] = 1.0f;

    kd[0] = 0.4f;
    kd[1] = 0.4f;
    kd[2] = 0.4f;
    kd[3] = 1.0f;

    ks[0] = 0.77f;
    ks[1] = 0.77f;
    ks[2] = 0.77f;
    ks[3] = 1.0f;

    sh = 51.0f;
    ni = 1.0f;
    transparency = 0.3f;
}


Material::Material(const char *materialName)
{
    ka[0] = 0.2f;
    ka[1] = 0.2f;
    ka[2] = 0.2f;
    ka[3] = 1.0f;

    kd[0] = 0.8f;
    kd[1] = 0.8f;
    kd[2] = 0.8f;
    kd[3] = 1.0f;

    ks[0] = 1.0f;
    ks[1] = 1.0f;
    ks[2] = 1.0f;
    ks[3] = 1.0f;

    sh = 0.0f;
    ni = 1.0f;
    transparency = 1.0f;

    this->loadMaterial(materialName);
}


Material::Material(ColorRgba matKa, ColorRgba matKd, ColorRgba matKs, float matNi, unsigned int matSh)
    : ni(matNi)
    , transparency(1.0f)
    , sh(matSh)
{
    ka[0] = matKa.getRed();
    ka[1] = matKa.getGreen();
    ka[2] = matKa.getBlue();
    ka[3] = matKa.getAlpha();

    kd[0] = matKd.getRed();
    kd[1] = matKd.getGreen();
    kd[2] = matKd.getBlue();
    kd[3] = matKd.getAlpha();

    ks[0] = matKs.getRed();
    ks[1] = matKs.getGreen();
    ks[2] = matKs.getBlue();
    ks[3] = matKs.getAlpha();
}


void Material::loadMaterial(const char *materialName)
{
    float r, g, b, d, x;
    std::string type, trash;

    std::ifstream fin;
    fin.open(materialName, std::ifstream::in);

    while (fin >> type)
    {
        if (type == "Ka")
        {
            fin >> r >> g >> b;

            ka[0] = r;
            ka[1] = g;
            ka[2] = b;
        }
        else if (type == "Kd")
        {
            fin >> r >> g >> b;

            kd[0] = r;
            kd[1] = g;
            kd[2] = b;
        }
        else if (type == "Ks")
        {
            fin >> r >> g >> b;

            ks[0] = r;
            ks[1] = g;
            ks[2] = b;
        }
        else if (type == "Tf")
        {
            fin >> r >> g >> b;

            tf[0] = r;
            tf[1] = g;
            tf[2] = b;
        }
        else if (type == "Ns")
        {
            fin >> x;
            sh = x;
        }
        else if (type == "Ni")
        {
            fin >> x;
            ni = x;
        }
        else if (type == "d" || type == "Tr")
        {
            fin >> d;
            transparency = d;
        }
        else
        {
            getline(fin, trash);
        }
    }
}
