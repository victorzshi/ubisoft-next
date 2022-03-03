#pragma once

#include <string>
#include <vector>

#include "Graphics/Triangle/Triangle.h"
#include "Math/Vector3/Vector3.h"

struct Mesh
{
    std::vector<Triangle> triangles;

    static Mesh Cube();
};