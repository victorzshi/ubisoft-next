#include "stdafx.h"

#include "Vector3.h"

class Vector3Test
{
  public:
    static void RunTests()
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);
        Vector3 w = Vector3(4.0f, 5.0f, 6.0f);
        float n = 2.0f;

        TestAdd(v, w);
        TestCompoundAdd(v, w);
        TestSubtract(v, w);
        TestCompoundSubtract(v, w);
        TestMultiply(v, n);
        TestCompoundMultiply(v, n);
        TestDivide(v, n);
        TestCompoundDivide(v, n);
        TestLength(v);
        TestNormalize(v);
        TestDot(v, w);
        TestCross(v, w);
    }

  private:
    static void TestAdd(Vector3& v, Vector3& w)
    {
        Vector3 u = v + w;

        assert(u == Vector3(5.0f, 7.0f, 9.0f));
    }

    static void TestCompoundAdd(Vector3& v, Vector3& w)
    {
        Vector3 u = v + w;
        u += u;

        assert(u == Vector3(10.0f, 14.0f, 18.0f));
    }

    static void TestSubtract(Vector3& v, Vector3& w)
    {
        Vector3 u = v - w;

        assert(u == Vector3(-3.0f, -3.0f, -3.0f));
    }

    static void TestCompoundSubtract(Vector3& v, Vector3& w)
    {
        Vector3 u = v - w;
        u -= u;

        assert(u == Vector3(0.0f, 0.0f, 0.0f));
    }

    static void TestMultiply(Vector3& v, float& n)
    {
        Vector3 u = v * n;

        assert(u == Vector3(2.0f, 4.0f, 6.0f));
    }

    static void TestCompoundMultiply(Vector3& v, float& n)
    {
        Vector3 u = v * n;
        u *= n;

        assert(u == Vector3(4.0f, 8.0f, 12.0f));
    }

    static void TestDivide(Vector3& v, float& n)
    {
        Vector3 u = v / n;

        assert(u == Vector3(0.5f, 1.0f, 1.5f));
    }

    static void TestCompoundDivide(Vector3& v, float& n)
    {
        Vector3 u = v / n;
        u /= n;

        assert(u == Vector3(0.25f, 0.5f, 0.75f));
    }

    static void TestLength(Vector3& v)
    {
        float length = v.Length();

        assert(length == sqrtf(14));
    }

    static void TestNormalize(Vector3& v)
    {
        float length = v.Length();
        Vector3 u = v.Normalize();

        assert(u == Vector3(v.x / length, v.y / length, v.z / length));
    }

    static void TestDot(Vector3& v, Vector3& w)
    {
        float dot = v.Dot(w);

        assert(dot == 32.0f);
    }

    static void TestCross(Vector3& v, Vector3& w)
    {
        Vector3 u = v.Cross(w);

        assert(u == Vector3(-3.0f, 6.0f, -3.0f));
    }
};