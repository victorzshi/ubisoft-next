#pragma once

#include <string>
#include <vector>

#include "Graphics/Color/Color.h"
#include "Graphics/Mesh/Mesh.h"

enum class Light
{
    BRIGHT,
    SHADOW,
    OUTLINE,
};

struct Model
{
    Mesh mesh;
    Color color;
    Light light;

    Model();

    void SetFaceColor(float dot, Face &face);
};