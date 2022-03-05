#include "stdafx.h"

#include "Random.h"

#include <random>

float Random::GetFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}