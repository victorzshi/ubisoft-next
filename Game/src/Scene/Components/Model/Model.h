#pragma once

#include <string>
#include <vector>

#include "Graphics/Color/Color.h"
#include "Graphics/Mesh/Mesh.h"
#include "Graphics/Light/Light.h"

struct Model
{
    Mesh mesh;
    Color color;
    Light light;

    Model();
};