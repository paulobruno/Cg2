#ifndef POSITION3D_H
#define POSITION3D_H


#include "log.h"

#include <cmath>


class Position3d
{
    public:

        explicit Position3d(float x = 0.0f, float y = 0.0f, float z = 0.0f)
            : x(x), y(y), z(z)
        {}
        virtual ~Position3d() {}


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
        Position3d atOperator(const Position3d& p2) const
        {
            return Position3d(x * p2.x, y * p2.y, z * p2.z);
        }

        // cross product
        Position3d crossProduct(const Position3d& p2)
        {
            LOGwar("Voce esta considerando que uma posicao representa a direcao de um vetor com inicio na origem");

            return Position3d( (y * p2.z - p2.y * z), (z * p2.x - p2.z * x), (x * p2.y - p2.x * y));
        }

        // dot product
        float dotProduct(const Position3d& p2)
        {
            return ( (x * p2.x) + (y * p2.y) + (z * p2.z) );
        }

        // distance between two points
        float distance(const Position3d& p2)
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


        Position3d operator+ (const Position3d& p2) const
        {
            return Position3d(x + p2.x, y + p2.y, z + p2.z);
        }

        friend Position3d& operator+= (Position3d& p1, const Position3d& p2)
        {
            p1.x += p2.x;
            p1.y += p2.y;
            p1.z += p2.z;

            return p1;
        }

        Position3d operator- (const Position3d& p2) const
        {
            return Position3d(x - p2.x, y - p2.y, z - p2.z);
        }

        friend Position3d& operator-= (Position3d& p1, const Position3d& p2)
        {
            p1.x -= p2.x;
            p1.y -= p2.y;
            p1.z -= p2.z;

            return p1;
        }

        Position3d operator* (float scalar)
        {
            return Position3d(x * scalar, y * scalar, z * scalar);
        }

        Position3d& operator*= (float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;

            return *this;
        }

        Position3d operator/ (float scalar)
        {
            return Position3d(x / scalar, y / scalar, z / scalar);
        }

        Position3d& operator/= (float scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;

            return *this;
        }

        Position3d& operator= (const Position3d& p2)
        {
            if (this != &p2)
            {
                x = p2.x;
                y = p2.y;
                z = p2.z;
            }

            return *this;
        }

        bool operator!= (const Position3d& p2)
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

        bool operator== (const Position3d& p2)
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


#endif // POSITION3D_H
