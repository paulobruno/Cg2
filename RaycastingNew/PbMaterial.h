// 2013, PAULO BRUNO DE SOUSA SERAFIM, Fortaleza - CE, Brasil


#ifndef PB_MATERIAL_H
#define PB_MATERIAL_H


class PbMaterial
{
	public:

        PbMaterial();
        PbMaterial(const char *materialName);

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

        float getTransparency() {return tr;}

        unsigned int getShininess() {return sh;}
        float getNi() {return ni;}


	private:

        float ka[4], kd[4], ks[4], tf[4], ni, tr;
        unsigned int sh;
};


#endif // PB_MATERIAL_H
