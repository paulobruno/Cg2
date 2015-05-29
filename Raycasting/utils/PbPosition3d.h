#ifndef PB_POSITION_3D_H
#define PB_POSITION_3D_H


#include "../utils/pb_log.h"

#include <cmath>


class PbPosition3d
{
	public:

		explicit PbPosition3d(float x = 0.0f, float y = 0.0f, float z = 0.0f)
			: x(x), y(y), z(z)
		{}
		virtual ~PbPosition3d() {}


		float length() const
		{
			LOGwar("Voce esta considerando que uma posicao representa a direcao de um vetor com inicio na origem");
			return sqrt( (x * x) + (y * y) + (z * z) );
		}

		void normalize()
		{
			LOGwar("Voce esta considerando que uma posicao representa a direcao de um vetor com inicio na origem");
				
			float l = length();

			if ( 0 < l)
			{
				(*this) *= 1 / l;
			}
		}

		// operator @
		PbPosition3d atOperator(const PbPosition3d& p2) const
		{
			return PbPosition3d(x * p2.x, y * p2.y, z * p2.z);
		}	

		// cross product
		PbPosition3d crossProduct(const PbPosition3d& p2)
		{
			LOGwar("Voce esta considerando que uma posicao representa a direcao de um vetor com inicio na origem");
			
			return PbPosition3d( (y * p2.z - p2.y * z), (z * p2.x - p2.z * x), (x * p2.y - p2.x * y));
		}
		
		// dot product
		float dotProduct(const PbPosition3d& p2)
		{
			return ( (x * p2.x) + (y * p2.y) + (z * p2.z) );
		}
		
        // distance between teo points
        float distance(const PbPosition3d& p2)
        {
            return ( sqrt( (x - p2.x)*(x - p2.x) + (y - p2.y)*(y - p2.y) + (z - p2.z)*(z - p2.z) ) );
        }


		float get_x() const {return x;}
		float get_y() const {return y;}
		float get_z() const {return z;}

		void set_x(float newX) {x = newX;}
		void set_y(float newY) {y = newY;}
		void set_z(float newZ) {z = newZ;}
		void set_pos(float newX, float newY, float newZ) {x = newX; y = newY; z = newZ;}


		PbPosition3d operator+ (const PbPosition3d& p2) const
		{
			return PbPosition3d(x + p2.x, y + p2.y, z + p2.z);
		}

		friend PbPosition3d& operator+= (PbPosition3d& p1, const PbPosition3d& p2)
		{
			p1.x += p2.x;
			p1.y += p2.y;
			p1.z += p2.z;

			return p1;
		}

		PbPosition3d operator- (const PbPosition3d& p2) const
		{
			return PbPosition3d(x - p2.x, y - p2.y, z - p2.z);
		}

		friend PbPosition3d& operator-= (PbPosition3d& p1, const PbPosition3d& p2)
		{
			p1.x -= p2.x;
			p1.y -= p2.y;
			p1.z -= p2.z;

			return p1;
		}

		PbPosition3d operator* (float scalar)
		{
			return PbPosition3d(x * scalar, y * scalar, z * scalar);
		}

		PbPosition3d& operator*= (float scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;

			return *this;
		}

		PbPosition3d operator/ (float scalar)
		{
			return PbPosition3d(x / scalar, y / scalar, z / scalar);
		}

		PbPosition3d& operator/= (float scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;

			return *this;
		}

        PbPosition3d& operator= (const PbPosition3d& p2)
		{
			if (this != &p2)
			{
				x = p2.x;
				y = p2.y;
				z = p2.z;
			}

			return *this;
		}

        bool operator!= (const PbPosition3d& p2)
        {
            if (this != &p2)
            {
                if ((x == p2.x) && (y == p2.y) && (z == p2.z))
                {
                    return false;
                }
            }

            return true;
        }

        bool operator== (const PbPosition3d& p2)
        {
            if (this != &p2)
            {
                if ((x == p2.x) && (y == p2.y) && (z == p2.z))
                {
                    return true;
                }
            }

            return false;
        }


	private:

		float x, y, z;
};


#endif // PB_POSITION_3D_H
