#include "Matrix4.h"


Matrix4::Matrix4()
{
    matrix[0] = 1.0f;
    matrix[1] = 0.0f;
    matrix[2] = 0.0f;
    matrix[3] = 0.0f;

    matrix[4] = 0.0f;
    matrix[5] = 1.0f;
    matrix[6] = 0.0f;
    matrix[7] = 0.0f;

    matrix[8] = 0.0f;
    matrix[9] = 0.0f;
    matrix[10] = 1.0f;
    matrix[11] = 0.0f;

    matrix[12] = 0.0f;
    matrix[13] = 0.0f;
    matrix[14] = 0.0f;
    matrix[15] = 1.0f;
}


Matrix4::Matrix4(float* m)
{
    for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
    {
        matrix[i] = *(m+i);
    }
}


Matrix4 Matrix4::transpose()
{
    float m[16];

    for (unsigned int i = 0; i < MATRIX4_SIZE; ++i)
    {
        for (unsigned int j = i/4; j < MATRIX4_SIZE; j += 4)
        {
            m[i] = matrix[j];
            ++i;
        }
        --i;
    }

    return Matrix4(m);
}


Position3d Matrix4::applyMatrix(Position3d point)
{
    float x = matrix[0]*point.get_x() + matrix[1]*point.get_y() + matrix[2]*point.get_z();
    float y = matrix[4]*point.get_x() + matrix[5]*point.get_y() + matrix[6]*point.get_z();
    float z = matrix[8]*point.get_x() + matrix[9]*point.get_y() + matrix[10]*point.get_z();

    return Position3d(x, y, z);
}


Matrix4 Matrix4::operator* (const Matrix4& m2) const
{
    float m[16];

    m[0] = matrix[0]*m2.matrix[0] + matrix[1]*m2.matrix[4] + matrix[2]*m2.matrix[8] + matrix[3]*m2.matrix[12];
    m[1] = matrix[0]*m2.matrix[1] + matrix[1]*m2.matrix[5] + matrix[2]*m2.matrix[9] + matrix[3]*m2.matrix[13];
    m[2] = matrix[0]*m2.matrix[2] + matrix[1]*m2.matrix[6] + matrix[2]*m2.matrix[10] + matrix[3]*m2.matrix[14];
    m[3] = matrix[0]*m2.matrix[3] + matrix[1]*m2.matrix[7] + matrix[2]*m2.matrix[11] + matrix[3]*m2.matrix[15];

    m[4] = matrix[4]*m2.matrix[0] + matrix[5]*m2.matrix[4] + matrix[6]*m2.matrix[8] + matrix[7]*m2.matrix[12];
    m[5] = matrix[4]*m2.matrix[1] + matrix[5]*m2.matrix[5] + matrix[6]*m2.matrix[9] + matrix[7]*m2.matrix[13];
    m[6] = matrix[4]*m2.matrix[2] + matrix[5]*m2.matrix[6] + matrix[6]*m2.matrix[10] + matrix[7]*m2.matrix[14];
    m[7] = matrix[4]*m2.matrix[3] + matrix[5]*m2.matrix[7] + matrix[6]*m2.matrix[11] + matrix[7]*m2.matrix[15];

    m[8] = matrix[8]*m2.matrix[0] + matrix[9]*m2.matrix[4] + matrix[10]*m2.matrix[8] + matrix[11]*m2.matrix[12];
    m[9] = matrix[8]*m2.matrix[1] + matrix[9]*m2.matrix[5] + matrix[10]*m2.matrix[9] + matrix[11]*m2.matrix[13];
    m[10] = matrix[8]*m2.matrix[2] + matrix[9]*m2.matrix[6] + matrix[10]*m2.matrix[10] + matrix[11]*m2.matrix[14];
    m[11] = matrix[8]*m2.matrix[3] + matrix[9]*m2.matrix[7] + matrix[10]*m2.matrix[11] + matrix[11]*m2.matrix[15];

    m[12] = matrix[12]*m2.matrix[0] + matrix[13]*m2.matrix[4] + matrix[14]*m2.matrix[8] + matrix[15]*m2.matrix[12];
    m[13] = matrix[12]*m2.matrix[1] + matrix[13]*m2.matrix[5] + matrix[14]*m2.matrix[9] + matrix[15]*m2.matrix[13];
    m[14] = matrix[12]*m2.matrix[2] + matrix[13]*m2.matrix[6] + matrix[14]*m2.matrix[10] + matrix[15]*m2.matrix[14];
    m[15] = matrix[12]*m2.matrix[3] + matrix[13]*m2.matrix[7] + matrix[14]*m2.matrix[11] + matrix[15]*m2.matrix[15];

    return Matrix4(m);
}
