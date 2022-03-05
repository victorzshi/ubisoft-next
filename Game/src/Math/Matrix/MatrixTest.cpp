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
        TestScale(v);
    }

  private:
    static void TestInitialization()
    {
        Matrix m = Matrix();

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                assert(m(row, col) == 0.0f);
            }
        }
    }
    static void TestMultiplyMatrix(Matrix &a, Matrix &b)
    {
        Matrix m = a * b;

        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                assert(m(row, col) == 24.0f);
            }
        }
    }

    static void TestMultiplyVector(Matrix &a, Vector3 &v)
    {
        Vector3 u = a * v;

        assert(u == Vector3(20.0f, 20.0f, 20.0f));
        assert(u.w == 20.0f);
    }

    static void TestTranslate(Vector3 &v)
    {
        Matrix m = Matrix::Translate(v);

        assert(m(0, 0) == 1.0f);
        assert(m(0, 1) == 0.0f);
        assert(m(0, 2) == 0.0f);
        assert(m(0, 3) == 0.0f);
        assert(m(1, 0) == 0.0f);
        assert(m(1, 1) == 1.0f);
        assert(m(1, 2) == 0.0f);
        assert(m(1, 3) == 0.0f);
        assert(m(2, 0) == 0.0f);
        assert(m(2, 1) == 0.0f);
        assert(m(2, 2) == 1.0f);
        assert(m(2, 3) == 0.0f);
        assert(m(3, 0) == v.x);
        assert(m(3, 1) == v.y);
        assert(m(3, 2) == v.z);
        assert(m(3, 3) == 1.0f);
    }

    static void TestRotateX(float &n)
    {
        Matrix m = Matrix::RotateX(n);

        assert(m(0, 0) == 1.0f);
        assert(m(0, 1) == 0.0f);
        assert(m(0, 2) == 0.0f);
        assert(m(0, 3) == 0.0f);
        assert(m(1, 0) == 0.0f);
        assert(m(1, 1) == cosf(n));
        assert(m(1, 2) == sinf(n));
        assert(m(1, 3) == 0.0f);
        assert(m(2, 0) == 0.0f);
        assert(m(2, 1) == -sinf(n));
        assert(m(2, 2) == cosf(n));
        assert(m(2, 3) == 0.0f);
        assert(m(3, 0) == 0.0f);
        assert(m(3, 1) == 0.0f);
        assert(m(3, 2) == 0.0f);
        assert(m(3, 3) == 1.0f);
    }

    static void TestRotateY(float &n)
    {
        Matrix m = Matrix::RotateY(n);

        assert(m(0, 0) == cosf(n));
        assert(m(0, 1) == 0.0f);
        assert(m(0, 2) == -sinf(n));
        assert(m(0, 3) == 0.0f);
        assert(m(1, 0) == 0.0f);
        assert(m(1, 1) == 1.0f);
        assert(m(1, 2) == 0.0f);
        assert(m(1, 3) == 0.0f);
        assert(m(2, 0) == sinf(n));
        assert(m(2, 1) == 0.0f);
        assert(m(2, 2) == cosf(n));
        assert(m(2, 3) == 0.0f);
        assert(m(3, 0) == 0.0f);
        assert(m(3, 1) == 0.0f);
        assert(m(3, 2) == 0.0f);
        assert(m(3, 3) == 1.0f);
    }

    static void TestRotateZ(float &n)
    {
        Matrix m = Matrix::RotateZ(n);

        assert(m(0, 0) == cosf(n));
        assert(m(0, 1) == sinf(n));
        assert(m(0, 2) == 0.0f);
        assert(m(0, 3) == 0.0f);
        assert(m(1, 0) == -sinf(n));
        assert(m(1, 1) == cosf(n));
        assert(m(1, 2) == 0.0f);
        assert(m(1, 3) == 0.0f);
        assert(m(2, 0) == 0.0f);
        assert(m(2, 1) == 0.0f);
        assert(m(2, 2) == 1.0f);
        assert(m(2, 3) == 0.0f);
        assert(m(3, 0) == 0.0f);
        assert(m(3, 1) == 0.0f);
        assert(m(3, 2) == 0.0f);
        assert(m(3, 3) == 1.0f);
    }

    static void TestScale(Vector3& v)
    {
        Matrix m = Matrix::Scale(v);

        assert(m(0, 0) == v.x);
        assert(m(0, 1) == 0.0f);
        assert(m(0, 2) == 0.0f);
        assert(m(0, 3) == 0.0f);
        assert(m(1, 0) == 0.0f);
        assert(m(1, 1) == v.y);
        assert(m(1, 2) == 0.0f);
        assert(m(1, 3) == 0.0f);
        assert(m(2, 0) == 0.0f);
        assert(m(2, 1) == 0.0f);
        assert(m(2, 2) == v.z);
        assert(m(2, 3) == 0.0f);
        assert(m(3, 0) == 0.0f);
        assert(m(3, 1) == 0.0f);
        assert(m(3, 2) == 0.0f);
        assert(m(3, 3) == 1.0f);
    }
};