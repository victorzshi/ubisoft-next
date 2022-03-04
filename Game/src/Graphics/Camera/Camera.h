#pragma once

#include "Math/Vector3/Vector3.h"

struct Camera
{
    Vector3 position, facing, up;
    float yaw, pitch;

    Camera();
};
