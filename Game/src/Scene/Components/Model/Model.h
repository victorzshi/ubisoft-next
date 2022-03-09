#pragma once

#include <string>
#include <vector>

#include "Graphics/Face/Face.h"
#include "Graphics/Mesh/Mesh.h"

enum class Color
{
    WHITE,
    GREY,
    BLACK,
    RED,
    YELLOW,
    BLUE,
    ORANGE,
    GREEN,
    PURPLE,
};

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

    void SetColor(float dot, Face &face);
};