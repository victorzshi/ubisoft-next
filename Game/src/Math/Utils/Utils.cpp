#include "stdafx.h"

#include "Utils.h"

#include <random>

#include "Math/Vector3/Vector3.h"

int Utils::RandomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

float Utils::RandomFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

float Utils::Distance(Vector3 from, Vector3 to)
{
    float x = (from.x - to.x) * (from.x - to.x);
    float y = (from.y - to.y) * (from.y - to.y);
    float z = (from.z - to.z) * (from.z - to.z);
    return sqrtf(x + y + z);
}

float Utils::Angle(Vector3 from, Vector3 to)
{
    // Get positive angle between two vectors
    float angle = 0.0f;
    if (to - from != Vector3())
    {
        float dot = from.Dot(to);
        float magnitude = sqrt(from.LengthSquared() * to.LengthSquared());
        angle = acos(dot / magnitude);
    }

    // Flip angle based on z plane normal
    Vector3 normal = Vector3(0.0f, 0.0f, 1.0f);
    Vector3 cross = from.Cross(to);
    if (normal.Dot(cross) > 0)
    {
        angle = -angle;
    }

    // Convert angle to degrees
    return angle * 180.0f / PI;
}