#pragma once

struct Timer
{
    float start;
    float cooldown;
    float stayAlive;
    float ammo;

    Timer();

    float Elapsed(float current);
};