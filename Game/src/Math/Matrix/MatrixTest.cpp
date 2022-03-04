#include "stdafx.h"

#include "Matrix.h"

#include "Math/Vector3/Vector3.h"

class MatrixTest
{
  public:
    static void RunTests()
    {
        Matrix a = Matrix(2.0f);
        Matrix b = Matrix(3.0f);
        Vector3 v = Vector3(3.0f, 3.0f, 3.0f);
        float n = sqrtf(2.0f);

        TestInitialization();
        TestMultiplyMatrix(a, b);
        TestMultiplyVector(a, v);
        TestTranslate(v);
        TestRotateX(n);
        TestRotateY(n);
        TestRotateZ(n);
        TestScale(n);
    }

  private:
    static void TestInitialization()
    {
        Matrix c = Matrix();

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                if (c(row, col) != 0.0f)
                {
                    throw "Matrix initialization failed...";
                }
            }
        }
    }
    static void TestMultiplyMatrix(Matrix &a, Matrix &b)
    {
        Matrix c = a * b;

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                if (c(row, col) != 24.0f)
                {
                    throw "Matrix multiply matrix failed...";
                }
            }
        }
    }

    static void TestMultiplyVector(Matrix &a, Vector3 &v)
    {
        Vector3 u = a * v;

        if (u != Vector3(20.0f, 20.0f, 20.0f) || u.w != 20.0f)
        {
            throw "Matrix multiply vector failed...";
        }
    }

    static void TestTranslate(Vector3 &v)
    {
        Matrix m = Matrix::Translate(v);

        float valX = v.x;
        float valY = v.y;
        float valZ = v.z;

        bool row0 = m(0, 0) != 1.0f || m(0, 1) != 0.0f || m(0, 2) != 0.0f || m(0, 3) != 0.0f;
        bool row1 = m(1, 0) != 0.0f || m(1, 1) != 1.0f || m(1, 2) != 0.0f || m(1, 3) != 0.0f;
        bool row2 = m(2, 0) != 0.0f || m(2, 1) != 0.0f || m(2, 2) != 1.0f || m(2, 3) != 0.0f;
        bool row3 = m(3, 0) != valX || m(3, 1) != valY || m(3, 2) != valZ || m(3, 3) != 1.0f;

        if (row0 || row1 || row2 || row3)
        {
            throw "Matrix translate failed...";
        }
    }

    static void TestRotateX(float& n)
    {
        Matrix m = Matrix::RotateX(n);

        float valA = cosf(n);
        float valB = sinf(n);
        float valC = -sinf(n);
        float valD = cosf(n);

        bool row0 = m(0, 0) != 1.0f || m(0, 1) != 0.0f || m(0, 2) != 0.0f || m(0, 3) != 0.0f;
        bool row1 = m(1, 0) != 0.0f || m(1, 1) != valA || m(1, 2) != valB || m(1, 3) != 0.0f;
        bool row2 = m(2, 0) != 0.0f || m(2, 1) != valC || m(2, 2) != valD || m(2, 3) != 0.0f;
        bool row3 = m(3, 0) != 0.0f || m(3, 1) != 0.0f || m(3, 2) != 0.0f || m(3, 3) != 1.0f;

        if (row0 || row1 || row2 || row3)
        {
            throw "Matrix rotate X failed...";
        }
    }

    static void TestRotateY(float &n)
    {
        Matrix m = Matrix::RotateY(n);

        float valA = cosf(n);
        float valB = -sinf(n);
        float valC = sinf(n);
        float valD = cosf(n);

        bool row0 = m(0, 0) != valA || m(0, 1) != 0.0f || m(0, 2) != valB || m(0, 3) != 0.0f;
        bool row1 = m(1, 0) != 0.0f || m(1, 1) != 1.0f || m(1, 2) != 0.0f || m(1, 3) != 0.0f;
        bool row2 = m(2, 0) != valC || m(2, 1) != 0.0f || m(2, 2) != valD || m(2, 3) != 0.0f;
        bool row3 = m(3, 0) != 0.0f || m(3, 1) != 0.0f || m(3, 2) != 0.0f || m(3, 3) != 1.0f;

        if (row0 || row1 || row2 || row3)
        {
            throw "Matrix rotate Y failed...";
        }
    }

    static void TestRotateZ(float &n)
    {
        Matrix m = Matrix::RotateZ(n);

        float valA = cosf(n);
        float valB = sinf(n);
        float valC = -sinf(n);
        float valD = cosf(n);

        bool row0 = m(0, 0) != valA || m(0, 1) != valB || m(0, 2) != 0.0f || m(0, 3) != 0.0f;
        bool row1 = m(1, 0) != valC || m(1, 1) != valD || m(1, 2) != 0.0f || m(1, 3) != 0.0f;
        bool row2 = m(2, 0) != 0.0f || m(2, 1) != 0.0f || m(2, 2) != 1.0f || m(2, 3) != 0.0f;
        bool row3 = m(3, 0) != 0.0f || m(3, 1) != 0.0f || m(3, 2) != 0.0f || m(3, 3) != 1.0f;

        if (row0 || row1 || row2 || row3)
        {
            throw "Matrix rotate Z failed...";
        }
    }

    static void TestScale(float &n)
    {
        Matrix m = Matrix::Scale(n * 1, n * 2, n * 3);

        float valX = n * 1;
        float valY = n * 2;
        float valZ = n * 3;

        bool row0 = m(0, 0) != valX || m(0, 1) != 0.0f || m(0, 2) != 0.0f || m(0, 3) != 0.0f;
        bool row1 = m(1, 0) != 0.0f || m(1, 1) != valY || m(1, 2) != 0.0f || m(1, 3) != 0.0f;
        bool row2 = m(2, 0) != 0.0f || m(2, 1) != 0.0f || m(2, 2) != valZ || m(2, 3) != 0.0f;
        bool row3 = m(3, 0) != 0.0f || m(3, 1) != 0.0f || m(3, 2) != 0.0f || m(3, 3) != 1.0f;

        if (row0 || row1 || row2 || row3)
        {
            throw "Matrix scale failed...";
        }
    }
};