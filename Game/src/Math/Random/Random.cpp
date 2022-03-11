#include "stdafx.h"

#include "Random.h"

#include <random>

#include "Math/Vector3/Vector3.h"

int Random::GetInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

float Random::GetFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

float Random::Distance(Vector3 a, Vector3 b)
{
    float x = (a.x - b.x) * (a.x - b.x);
    float y = (a.y - b.y) * (a.y - b.y);
    float z = (a.z - b.z) * (a.z - b.z);
    return sqrtf(x + y + z);
}