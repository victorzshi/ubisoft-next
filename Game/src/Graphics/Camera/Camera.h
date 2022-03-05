#pragma once

#include "Math/Vector3/Vector3.h"

struct Camera
{
    Vector3 position, rotation, facing, up;

    Camera();
};
