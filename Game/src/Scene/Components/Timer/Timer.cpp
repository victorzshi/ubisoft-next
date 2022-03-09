#include "stdafx.h"

#include "Timer.h"

Timer::Timer() : previous(0.0f)
{
}

float Timer::Elapsed(float current)
{
    return current - previous;
}