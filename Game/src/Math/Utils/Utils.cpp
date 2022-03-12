#include "stdafx.h"

#include "Utils.h"

#include <limits>
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

float Utils::MaxFloat()
{
    return std::numeric_limits<float>::infinity();
}

float Utils::Lerp(float a, float b, float t)
{
    return (a * (1.0f - t)) + (b * t);
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

Vector3 Utils::RandomUnitCircleVector()
{
    Vector3 random;
    Vector3 origin = Vector3(0.0f, 0.0f, 0.0f);

    bool isValid = false;
    while (!isValid)
    {
        // Generate random vector within unit square
        float x = RandomFloat(-1.0f, 1.0f);
        float y = RandomFloat(-1.0f, 1.0f);
        random = Vector3(x, y, 0.0f);

        // Check if the vector is inside unit circle
        if (Distance(random, origin) <= 1.0f)
        {
            isValid = true;
        }
    }

    return random.Normalize();
}