#pragma once

#include "Math/Vector3/Vector3.h"

struct Triangle
{
    Vector3 point[3];

    Triangle();

    void Render();
};