#include "stdafx.h"

#include "Matrix.h"

#include "Math/Vector3/Vector3.h"

Matrix::Matrix() : m{0.0f}
{
}

float &Matrix::operator()(int row, int col)
{
    return m[row + 4 * col];
}

Matrix Matrix::operator*(const Matrix &other) const
{
    Matrix matrix;
    for (int i = 0; i < 16; i++)
    {
        int row = (int)floor(i / 4);
        int col = i % 4;

        matrix(row, col) = m[row + 0] * other.m[col * 4 + 0] + m[row + 4] * other.m[col * 4 + 1] +
                           m[row + 8] * other.m[col * 4 + 2] + m[row + 12] * other.m[col * 4 + 3];
    }
    return matrix;
}

Vector3 Matrix::operator*(const Vector3 &v) const
{
    Vector3 u;
    u.x = m[0] * v.x + m[1] * v.y + m[2] * v.z + m[3] * v.w;
    u.y = m[4] * v.x + m[5] * v.y + m[6] * v.z + m[7] * v.w;
    u.z = m[8] * v.x + m[9] * v.y + m[10] * v.z + m[11] * v.w;
    u.w = m[12] * v.x + m[13] * v.y + m[14] * v.z + m[15] * v.w;
    return u;
}

Matrix Matrix::Identity()
{
    Matrix matrix;
    matrix(0, 0) = 1.0f;
    matrix(1, 1) = 1.0f;
    matrix(2, 2) = 1.0f;
    matrix(3, 3) = 1.0f;
    return matrix;
}

Matrix Matrix::Translate(Vector3 &v)
{
    Matrix matrix = Matrix::Identity();
    matrix(3, 0) = v.x;
    matrix(3, 1) = v.y;
    matrix(3, 2) = v.z;
    return matrix;
}

Matrix Matrix::Rotate(Vector3 &v)
{
    float x = v.x * (PI / 180.0f);
    float y = v.y * (PI / 180.0f);
    float z = v.z * (PI / 180.0f);
    float cX = cosf(x);
    float cY = cosf(y);
    float cZ = cosf(z);
    float sX = sinf(x);
    float sY = sinf(y);
    float sZ = sinf(z);

    Matrix matrix;
    matrix(0, 0) = cY * cZ;
    matrix(0, 1) = -cY * sZ;
    matrix(0, 2) = sY;
    matrix(0, 3) = 0.0f;
    matrix(1, 0) = (sX * sY * cZ) + (cX * sZ);
    matrix(1, 1) = -(sX * sY * sZ) + (cX * cZ);
    matrix(1, 2) = -sX * cY;
    matrix(1, 3) = 0.0f;
    matrix(2, 0) = -(cX * sY * cZ) + (sX * sZ);
    matrix(2, 1) = (cX * sY * sZ) + (sX * cZ);
    matrix(2, 2) = cX * cY;
    matrix(2, 3) = 0.0f;
    matrix(3, 0) = 0.0f;
    matrix(3, 1) = 0.0f;
    matrix(3, 2) = 0.0f;
    matrix(3, 3) = 1.0f;
    return matrix;
}

Matrix Matrix::Scale(Vector3 &v)
{
    Matrix matrix = Matrix::Identity();
    matrix(0, 0) = v.x;
    matrix(1, 1) = v.y;
    matrix(2, 2) = v.z;
    return matrix;
}