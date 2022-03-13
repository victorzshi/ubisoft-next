#pragma once

struct Timer
{
    float start;
    float cooldown;
    float stayAlive;

    Timer();

    float Elapsed(float current);
};