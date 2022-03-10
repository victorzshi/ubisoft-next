#pragma once

#include "Graphics/Color/Color.h"
#include "Graphics/Mesh/Mesh.h"

enum class Lighting
{
    BRIGHT,
    SHADOW,
    OUTLINE,
};

struct Model
{
    Mesh mesh;
    Color color;
    Lighting lighting;

    Model();

    void ApplyLighting(float dot, Face &face);
};