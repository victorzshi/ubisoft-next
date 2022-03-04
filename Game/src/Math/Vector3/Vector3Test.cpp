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

        if (u != Vector3(5.0f, 7.0f, 9.0f))
        {
            throw "Vector3 add failed...";
        }
    }

    static void TestCompoundAdd(Vector3& v, Vector3& w)
    {
        Vector3 u = v + w;
        u += u;

        if (u != Vector3(10.0f, 14.0f, 18.0f))
        {
            throw "Vector3 compound add failed...";
        }
    }

    static void TestSubtract(Vector3& v, Vector3& w)
    {
        Vector3 u = v - w;

        if (u != Vector3(-3.0f, -3.0f, -3.0f))
        {
            throw "Vector3 subtract failed...";
        }
    }

    static void TestCompoundSubtract(Vector3& v, Vector3& w)
    {
        Vector3 u = v - w;
        u -= u;

        if (u != Vector3(0.0f, 0.0f, 0.0f))
        {
            throw "Vector3 compound subtract failed...";
        }
    }

    static void TestMultiply(Vector3& v, float& n)
    {
        Vector3 u = v * n;

        if (u != Vector3(2.0f, 4.0f, 6.0f))
        {
            throw "Vector3 multiply failed...";
        }
    }

    static void TestCompoundMultiply(Vector3& v, float& n)
    {
        Vector3 u = v * n;
        u *= n;

        if (u != Vector3(4.0f, 8.0f, 12.0f))
        {
            throw "Vector3 compound multiply failed...";
        }
    }

    static void TestDivide(Vector3& v, float& n)
    {
        Vector3 u = v / n;

        if (u != Vector3(0.5f, 1.0f, 1.5f))
        {
            throw "Vector3 divide failed...";
        }
    }

    static void TestCompoundDivide(Vector3& v, float& n)
    {
        Vector3 u = v / n;
        u /= n;

        if (u != Vector3(0.25f, 0.5f, 0.75f))
        {
            throw "Vector3 compound divide failed...";
        }
    }

    static void TestLength(Vector3& v)
    {
        float length = v.Length();

        if (length != sqrtf(14))
        {
            throw "Vector3 length failed...";
        }
    }

    static void TestNormalize(Vector3& v)
    {
        float length = v.Length();
        Vector3 u = v.Normalize();

        if (u != Vector3(v.x / length, v.y / length, v.z / length))
        {
            throw "Vector3 normalize failed...";
        }
    }

    static void TestDot(Vector3& v, Vector3& w)
    {
        float dot = v.Dot(w);

        if (dot != 32.0f)
        {
            throw "Vector3 dot failed...";
        }
    }

    static void TestCross(Vector3& v, Vector3& w)
    {
        Vector3 u = v.Cross(w);

        if (u != Vector3(-3.0f, 6.0f, -3.0f))
        {
            throw "Vector3 cross failed...";
        }
    }
};