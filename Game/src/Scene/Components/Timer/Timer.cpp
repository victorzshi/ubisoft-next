#include "stdafx.h"

#include "Timer.h"

Timer::Timer() : start(0.0f)
{
}

float Timer::Elapsed(float current)
{
    return current - start;
}