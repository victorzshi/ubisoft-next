#pragma once

#include <string>
#include <vector>

#include "Graphics/Face/Face.h"

struct Mesh
{
    std::vector<Face> faces;
    // TODO: Enable/disable backface culling.

    Mesh();

    static Mesh LoadFromObjectFile(std::string file);

    // TODO: Store mesh data statically.
};