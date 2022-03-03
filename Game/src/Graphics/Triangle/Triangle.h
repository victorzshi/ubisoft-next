#pragma once

#include "Math/Vector3/Vector3.h"

struct Triangle
{
    Vector3 point[3];

    Triangle();

    Triangle(Vector3 p1, Vector3 p2, Vector3 p3);

    void Render();
};