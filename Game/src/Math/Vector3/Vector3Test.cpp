#include "stdafx.h"

#include "Vector3.h"

enum class Test
{
    PASS,
    FAIL
};

class Vector3Test
{
  public:
    static void RunTests()
    {
        Vector3 v = Vector3(1.0f, 2.0f, 3.0f);
        Vector3 w = Vector3(4.0f, 5.0f, 6.0f);

        if (Add(v, w) == Test::FAIL)
        {
            throw "Vector3 add failed...";
        }
        if (CompoundAdd(v, w) == Test::FAIL)
        {
            throw "Vector3 compound add failed...";
        }
        if (Subtract(v, w) == Test::FAIL)
        {
            throw "Vector3 subtract failed...";
        }
        if (CompoundSubtract(v, w) == Test::FAIL)
        {
            throw "Vector3 compound subtract failed...";
        }
        if (Multiply(v) == Test::FAIL)
        {
            throw "Vector3 multiply failed...";
        }
        if (CompoundMultiply(v) == Test::FAIL)
        {
            throw "Vector3 compound multiply failed...";
        }
        if (Divide(v) == Test::FAIL)
        {
            throw "Vector3 divide failed...";
        }
        if (CompoundDivide(v) == Test::FAIL)
        {
            throw "Vector3 compound divide failed...";
        }
        if (Length(v) == Test::FAIL)
        {
            throw "Vector3 length failed...";
        }
        if (Normalize(v) == Test::FAIL)
        {
            throw "Vector3 normalize failed...";
        }
        if (Dot(v, w) == Test::FAIL)
        {
            throw "Vector3 dot product failed...";
        }
        if (Cross(v, w) == Test::FAIL)
        {
            throw "Vector3 cross product failed...";
        }
    }

  private:
    static Test Add(Vector3 v, Vector3 w)
    {
        Vector3 u = v + w;

        return u == Vector3(5.0f, 7.0f, 9.0f) ? Test::PASS : Test::FAIL;
    }

    static Test CompoundAdd(Vector3 v, Vector3 w)
    {
        Vector3 u = v + w;
        u += u;

        return u == Vector3(10.0f, 14.0f, 18.0f) ? Test::PASS : Test::FAIL;
    }

    static Test Subtract(Vector3 v, Vector3 w)
    {
        Vector3 u = v - w;

        return u == Vector3(-3.0f, -3.0f, -3.0f) ? Test::PASS : Test::FAIL;
    }

    static Test CompoundSubtract(Vector3 v, Vector3 w)
    {
        Vector3 u = v - w;
        u -= u;

        return u == Vector3(0.0f, 0.0f, 0.0f) ? Test::PASS : Test::FAIL;
    }

    static Test Multiply(Vector3 v)
    {
        Vector3 u = v * 2.0f;

        return u == Vector3(2.0f, 4.0f, 6.0f) ? Test::PASS : Test::FAIL;
    }

    static Test CompoundMultiply(Vector3 v)
    {
        Vector3 u = v * 2.0f;
        u *= 2.0f;

        return u == Vector3(4.0f, 8.0f, 12.0f) ? Test::PASS : Test::FAIL;
    }

    static Test Divide(Vector3 v)
    {
        Vector3 u = v / 2.0f;

        return u == Vector3(0.5f, 1.0f, 1.5f) ? Test::PASS : Test::FAIL;
    }

    static Test CompoundDivide(Vector3 v)
    {
        Vector3 u = v / 2.0f;
        u /= 2.0f;

        return u == Vector3(0.25f, 0.5f, 0.75f) ? Test::PASS : Test::FAIL;
    }

    static Test Length(Vector3 v)
    {
        float length = v.Length();

        return length == sqrtf(14) ? Test::PASS : Test::FAIL;
    }

    static Test Normalize(Vector3 v)
    {
        float length = v.Length();
        Vector3 u = v.Normalize();

        return u == Vector3(v.x / length, v.y / length, v.z / length) ? Test::PASS : Test::FAIL;
    }

    static Test Dot(Vector3 v, Vector3 w)
    {
        float dot = v.Dot(w);

        return dot == 32.0f ? Test::PASS : Test::FAIL;
    }

    static Test Cross(Vector3 v, Vector3 w)
    {
        Vector3 u = v.Cross(w);

        return u == Vector3(-3.0f, 6.0f, -3.0f) ? Test::PASS : Test::FAIL;
    }
};