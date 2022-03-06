#pragma once

#include <string>
#include <vector>

#include "Graphics/Quad/Quad.h"
#include "Graphics/Triangle/Triangle.h"

struct Mesh
{
    std::vector<Triangle> triangles;
    std::vector<Quad> quads;
    // TODO: Enable/disable backface culling.

    Mesh();

    static Mesh LoadFromObjectFile(std::string file);

    // TODO: Store mesh data statically.
};