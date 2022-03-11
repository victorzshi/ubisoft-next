#include "stdafx.h"

#include "Transform.h"

Transform::Transform()
    : position(Vector3()), rotation(Vector3()), scaling(Vector3(1.0f, 1.0f, 1.0f)), up(Vector3(0.0f, -1.0f, 0.0f))
{
}