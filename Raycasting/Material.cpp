#include "Material.h"


#include <string>
#include <fstream>


Material::Material()
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
    tr = 1.0f;
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
    tr = 1.0f;

    this->loadMaterial(materialName);
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
            tr = d;
        }
        else
        {
            getline(fin, trash);
        }
    }
}
