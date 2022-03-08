#pragma once

#include "Math/Vector3/Vector3.h"

struct Face
{
    int vertices;
    Vector3 vertex[4];
    float r, g, b;

    Face();

    void Render();
};