#pragma once

#include <string>
#include <vector>

#include "Graphics/Triangle/Triangle.h"

struct Mesh
{
    std::vector<Triangle> triangles;
    // TODO: Enable/disable backface culling.
    // TODO: Support quads.

    Mesh();

    static Mesh LoadFromObjectFile(std::string file);

    // TODO: Store mesh data statically.
};