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
        TestRotate(v);
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

    static void TestRotate(Vector3 &v)
    {
        Matrix mX = Matrix::Rotate(Vector3(v.x, 0.0f, 0.0f));
        Matrix mY = Matrix::Rotate(Vector3(0.0f, v.y, 0.0f));
        Matrix mZ = Matrix::Rotate(Vector3(0.0f, 0.0f, v.z));

        float x = v.x * (PI / 180.0f);
        float y = v.y * (PI / 180.0f);
        float z = v.z * (PI / 180.0f);

        assert(mX(0, 0) == 1.0f);
        assert(mX(0, 1) == 0.0f);
        assert(mX(0, 2) == 0.0f);
        assert(mX(0, 3) == 0.0f);
        assert(mX(1, 0) == 0.0f);
        assert(mX(1, 1) == cosf(x));
        assert(mX(1, 2) == -sinf(x));
        assert(mX(1, 3) == 0.0f);
        assert(mX(2, 0) == 0.0f);
        assert(mX(2, 1) == sinf(x));
        assert(mX(2, 2) == cosf(x));
        assert(mX(2, 3) == 0.0f);
        assert(mX(3, 0) == 0.0f);
        assert(mX(3, 1) == 0.0f);
        assert(mX(3, 2) == 0.0f);
        assert(mX(3, 3) == 1.0f);

        assert(mY(0, 0) == cosf(y));
        assert(mY(0, 1) == 0.0f);
        assert(mY(0, 2) == sinf(y));
        assert(mY(0, 3) == 0.0f);
        assert(mY(1, 0) == 0.0f);
        assert(mY(1, 1) == 1.0f);
        assert(mY(1, 2) == 0.0f);
        assert(mY(1, 3) == 0.0f);
        assert(mY(2, 0) == -sinf(y));
        assert(mY(2, 1) == 0.0f);
        assert(mY(2, 2) == cosf(y));
        assert(mY(2, 3) == 0.0f);
        assert(mY(3, 0) == 0.0f);
        assert(mY(3, 1) == 0.0f);
        assert(mY(3, 2) == 0.0f);
        assert(mY(3, 3) == 1.0f);

        assert(mZ(0, 0) == cosf(z));
        assert(mZ(0, 1) == -sinf(z));
        assert(mZ(0, 2) == 0.0f);
        assert(mZ(0, 3) == 0.0f);
        assert(mZ(1, 0) == sinf(z));
        assert(mZ(1, 1) == cosf(z));
        assert(mZ(1, 2) == 0.0f);
        assert(mZ(1, 3) == 0.0f);
        assert(mZ(2, 0) == 0.0f);
        assert(mZ(2, 1) == 0.0f);
        assert(mZ(2, 2) == 1.0f);
        assert(mZ(2, 3) == 0.0f);
        assert(mZ(3, 0) == 0.0f);
        assert(mZ(3, 1) == 0.0f);
        assert(mZ(3, 2) == 0.0f);
        assert(mZ(3, 3) == 1.0f);
    }

    static void TestScale(Vector3 &v)
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