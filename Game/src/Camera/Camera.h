#pragma once

#include "Math/Vector3/Vector3.h"

struct Camera
{
    Vector3 position = Vector3();
    Vector3 facing = Vector3();
    Vector3 up = Vector3();
    float yaw = 0.0f;
    float pitch = 0.0f;
};
