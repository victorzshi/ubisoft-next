#pragma once

struct Vector3;

// 4x4 matrix.
struct Matrix
{
    float m[16];

    Matrix();

    explicit Matrix(float n);

    float &operator()(int row, int col);

    Matrix operator*(const Matrix &other) const;

    Vector3 operator*(const Vector3 &v) const;

    static Matrix Identity();
    static Matrix Translate(Vector3 v);
    static Matrix RotateX(float theta);
    static Matrix RotateY(float theta);
    static Matrix RotateZ(float theta);
    static Matrix Scale(float x, float y, float z);
    static Matrix Projection(float distancePlane, float aspectRatio, float zNear, float zFar);
    static Matrix PointAt(Vector3 &position, Vector3 &target, Vector3 &up);
    static Matrix QuickInverse(Matrix &m);
};