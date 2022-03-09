#pragma once

struct Timer
{
    float previous;

    Timer();

    float Elapsed(float current);
};