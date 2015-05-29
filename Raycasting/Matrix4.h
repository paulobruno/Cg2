#ifndef MATRIX4_H
#define MATRIX4_H

#include "log.h"
#include "Position3d.h"

#define MATRIX4_SIZE 16


class Matrix4
{
    public:

        explicit Matrix4();
        explicit Matrix4(float* m);
        virtual ~Matrix4() {}


        Matrix4 transpose();

        Position3d applyMatrix(Position3d point);


        Matrix4 operator+ (const Matrix4& m2) const
        {
            float m[16];

            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                m[i] = matrix[i] + m2.matrix[i];
            }

            return Matrix4(m);
        }


        friend Matrix4& operator+= (Matrix4& m1, const Matrix4& m2)
        {
            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                m1.matrix[i] += m2.matrix[i];
            }

            return m1;
        }


        Matrix4 operator- (const Matrix4& m2) const
        {
            float m[16];

            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                m[i] = matrix[i] - m2.matrix[i];
            }

            return Matrix4(m);
        }


        friend Matrix4& operator-= (Matrix4& m1, const Matrix4& m2)
        {
            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                m1.matrix[i] -= m2.matrix[i];
            }

            return m1;
        }


        Matrix4 operator* (const Matrix4& m2) const;

        friend Matrix4& operator*= (Matrix4& m1, const Matrix4& m2)
        {
            m1 = m1 * m2;

            return m1;
        }


        Matrix4 operator* (float scalar)
        {
            float m[16];

            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                m[i] = matrix[i] * scalar;
            }

            return Matrix4(m);
        }


        Matrix4& operator*= (float scalar)
        {
            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                matrix[i] *= scalar;
            }

            return *this;
        }


        Matrix4 operator/ (float scalar)
        {
            float m[16];

            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                m[i] = matrix[i] / scalar;
            }

            return Matrix4(m);
        }


        Matrix4& operator/= (float scalar)
        {
            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                matrix[i] /= scalar;
            }

            return *this;
        }


        Matrix4& operator= (const Matrix4& m2)
        {
            if (this != &m2)
            {
                for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
                {
                    matrix[i] = m2.matrix[i];
                }
            }

            return *this;
        }


        float& operator[] (const int index)
        {
            if (index > (MATRIX4_SIZE-1))
            {
                LOGerr("Index out of bounds. Returning first element");

                return matrix[0];
            }

            return matrix[index];
        }


        bool operator!= (const Matrix4& m2)
        {
            if (this != &m2)
            {
                for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
                {
                    if (matrix[i] != m2.matrix[i])
                    {
                        return true;
                    }
                }
            }

            return false;
        }


        bool operator== (const Matrix4& m2)
        {
            if (this != &m2)
            {
                for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
                {
                    if (matrix[i] != m2.matrix[i])
                    {
                        return false;
                    }
                }
            }

            return true;
        }


        void setMatrix(float* newMatrix)
        {
            for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
            {
                matrix[i] = *(newMatrix+i);
            }
        }

        float* getMatrix() {return matrix;}


    private:

        float matrix[MATRIX4_SIZE];
};


#endif // MATRIX4_H
