#ifndef PB_POSITION_4D_H
#define PB_POSITION_4D_H


#include <cmath>


class PbPosition4d
{
	public:

		explicit PbPosition4d(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1) // default is a point
			: x(x), y(y), z(z), w(w)
		{}
		virtual ~PbPosition4d() {}


		float length()
		{
			if (w)
			{
				LOGwar("Ponto nao possui tamanho. Retornando 0..");
				return 0;
			}
			else
			{
				return sqrt( (x * x) + (y * y) + (z * z) );
			}
		}

		void normalize()
		{
			if (w)
			{
				LOGwar("Nao eh possivel normalizar um ponto.\nNenhuma alteracao realizada");
			}
			else
			{
				float l = length();

				if ( 0 < l)
				{
					(*this) *= 1 / l;
				}
			}
		}

		// operator @
		PbPosition4d atOperator(const PbPosition4d& p2) const
		{
			return PbPosition4d(x * p2.x, y * p2.y, z * p2.z);
		}	

		// cross product
		PbPosition4d crossProduct(const PbPosition4d& p2)
		{
			if (w)
			{
				LOGerr("Nao eh possivel realizar produto vetorial entre pontos, retornando (0.0, 0.0, 0.0, 1");
				
				return PbPosition4d( 0.0f, 0.0f, 0.0f, 1);
			}
			else
			{
				return PbPosition4d( (y * p2.z - p2.y * z), (z * p2.x - p2.z * x), (x * p2.y - p2.x * y), 0);
			}
		}
		
		// dot product
		float dotProduct(const PbPosition4d& p2)
		{
			return ( (x * p2.x) + (y * p2.y) + (z * p2.z) );
		}
		

		// getters and setters
		
		float getX() const {return x;}
		float getY() const {return y;}
		float getZ() const {return z;}
		unsigned int getW() const {return w;}

		void setX(float newX) {x = newX;}
		void setY(float newY) {y = newY;}
		void setZ(float newZ) {z = newZ;}
		void setW(unsigned int newW) {w = newW;}
		void setPos(float newX, float newY, float newZ, unsigned int newW = 1) {x = newX; y = newY; z = newZ; w = newW;}


		// operators

		PbPosition4d operator+ (const PbPosition4d& v2) const
		{
			return PbPosition4d(x + v2.x, y + v2.y, z + v2.z);
		}

		friend PbPosition4d& operator+= (PbPosition4d& v1, const PbPosition4d& v2)
		{
			v1.x += v2.x;
			v1.y += v2.y;
			v1.z += v2.z;

			return v1;
		}

		PbPosition4d operator- (const PbPosition4d& v2) const
		{
			return PbPosition4d(x - v2.x, y - v2.y, z - v2.z);
		}

		friend PbPosition4d& operator-= (PbPosition4d& v1, const PbPosition4d& v2)
		{
			v1.x -= v2.x;
			v1.y -= v2.y;
			v1.z -= v2.z;

			return v1;
		}

		PbPosition4d operator* (float scalar)
		{
			return PbPosition4d(x * scalar, y * scalar, z * scalar);
		}

		PbPosition4d& operator*= (float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		PbPosition4d operator/ (float scalar)
		{
			return PbPosition4d(x / scalar, y / scalar, z / scalar);
		}

		PbPosition4d& operator/= (float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;

			return *this;
		}

		PbPosition4d& operator= (const PbPosition4d &v2)
		{
			if (this != &v2)
			{
				x = v2.x;
				y = v2.y;
				z = v2.z;
				w = v2.w;
			}

			return *this;
		}


	private:

		float x, y, z;	// x, y and z coordinates; 
		unsigned int w;	// w = 1 for point or w = 0 for vector 
};


#endif // PB_POSITION_4D_H
