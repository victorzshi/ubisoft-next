#pragma once

struct Timer
{
    float start;

    Timer();

    float Elapsed(float current);
};