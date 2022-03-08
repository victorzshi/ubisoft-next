#pragma once

#include "Graphics/Color/Color.h"
#include "Math/Vector3/Vector3.h"

struct Face
{
    int vertices;
    Vector3 vertex[4];
    Color color;

    Face();

    void Render();
};