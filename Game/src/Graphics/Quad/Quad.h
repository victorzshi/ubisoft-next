#pragma once

#include "Math/Vector3/Vector3.h"

struct Quad
{
    Vector3 point[4];

    Quad();

    void Render();
};