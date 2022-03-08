#pragma once

struct Vector3;

// 4x4 matrix.
struct Matrix
{
    Matrix();

    float &operator()(int row, int col);

    Matrix operator*(const Matrix &other) const;

    Vector3 operator*(const Vector3 &v) const;

    static Matrix Identity();
    static Matrix Translate(Vector3 &v);
    static Matrix Rotate(Vector3 &v);
    static Matrix Scale(Vector3 &v);

  private:
    float m[16];
};