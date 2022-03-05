#pragma once

#include <string>
#include <vector>

#include "Graphics/Triangle/Triangle.h"

struct Mesh
{
    std::vector<Triangle> triangles;

    Mesh();

    static Mesh LoadFromObjectFile(std::string file);
};