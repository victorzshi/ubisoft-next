#include "stdafx.h"

#include "Matrix.h"

#include "Math/Vector3/Vector3.h"

Matrix::Matrix()
{
    for (int i = 0; i < 16; i++)
    {
        m[i] = 0.0f;
    }
}

Matrix::Matrix(float n)
{
    for (int i = 0; i < 16; i++)
    {
        m[i] = n;
    }
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

Matrix Matrix::Translate(Vector3 v)
{
    Matrix matrix = Matrix::Identity();
    matrix(3, 0) = v.x;
    matrix(3, 1) = v.y;
    matrix(3, 2) = v.z;
    return matrix;
}

Matrix Matrix::RotateX(float theta)
{
    Matrix matrix = Matrix::Identity();
    matrix(1, 1) = cosf(theta);
    matrix(1, 2) = sinf(theta);
    matrix(2, 1) = -sinf(theta);
    matrix(2, 2) = cosf(theta);
    return matrix;
}

Matrix Matrix::RotateY(float theta)
{
    Matrix matrix = Matrix::Identity();
    matrix(0, 0) = cosf(theta);
    matrix(0, 2) = -sinf(theta);
    matrix(2, 0) = sinf(theta);
    matrix(2, 2) = cosf(theta);
    return matrix;
}

Matrix Matrix::RotateZ(float theta)
{
    Matrix matrix = Matrix::Identity();
    matrix(0, 0) = cosf(theta);
    matrix(0, 1) = sinf(theta);
    matrix(1, 0) = -sinf(theta);
    matrix(1, 1) = cosf(theta);
    return matrix;
}

Matrix Matrix::Scale(float x, float y, float z)
{
    Matrix matrix = Matrix::Identity();
    matrix(0, 0) = x;
    matrix(1, 1) = y;
    matrix(2, 2) = z;
    return matrix;
}

Matrix Matrix::Projection(float distancePlane, float aspectRatio, float zNear, float zFar)
{
    Matrix matrix;
    matrix(0, 0) = distancePlane / aspectRatio;
    matrix(1, 1) = distancePlane;
    matrix(2, 2) = zFar / (zFar - zNear);
    matrix(2, 3) = -((zNear * zFar) / (zFar - zNear));
    matrix(3, 2) = 1.0f;
    return matrix;
}

Matrix Matrix::PointAt(Vector3 &position, Vector3 &target, Vector3 &up)
{
    Vector3 newForward = (target - position).Normalize();

    Vector3 a = newForward * (up.Dot(newForward));
    Vector3 newUp = (up - a).Normalize();

    Vector3 newRight = up.Cross(newForward);

    Matrix matrix;
    matrix(0, 0) = newRight.x;
    matrix(0, 1) = newRight.y;
    matrix(0, 2) = newRight.z;
    matrix(0, 3) = 0.0f;
    matrix(1, 0) = newUp.x;
    matrix(1, 1) = newUp.y;
    matrix(1, 2) = newUp.z;
    matrix(1, 3) = 0.0f;
    matrix(2, 0) = newForward.x;
    matrix(2, 1) = newForward.y;
    matrix(2, 2) = newForward.z;
    matrix(2, 3) = 0.0f;
    matrix(3, 0) = position.x;
    matrix(3, 1) = position.y;
    matrix(3, 2) = position.z;
    matrix(3, 3) = 1.0f;
    return matrix;
}

Matrix Matrix::QuickInverse(Matrix &m)
{
    Matrix matrix;
    matrix(0, 0) = m(0, 0);
    matrix(0, 1) = m(1, 0);
    matrix(0, 2) = m(2, 0);
    matrix(0, 3) = 0.0f;
    matrix(1, 0) = m(0, 1);
    matrix(1, 1) = m(1, 1);
    matrix(1, 2) = m(2, 1);
    matrix(1, 3) = 0.0f;
    matrix(2, 0) = m(0, 2);
    matrix(2, 1) = m(1, 2);
    matrix(2, 2) = m(2, 2);
    matrix(2, 3) = 0.0f;
    matrix(3, 0) = -(m(3, 0) * matrix(0, 0) + m(3, 1) * matrix(1, 0) + m(3, 2) * matrix(2, 0));
    matrix(3, 1) = -(m(3, 0) * matrix(0, 1) + m(3, 1) * matrix(1, 1) + m(3, 2) * matrix(2, 1));
    matrix(3, 2) = -(m(3, 0) * matrix(0, 2) + m(3, 1) * matrix(1, 2) + m(3, 2) * matrix(2, 2));
    matrix(3, 3) = 1.0f;
    return matrix;
}