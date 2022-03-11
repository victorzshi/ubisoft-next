#pragma once

#include "Scene/Pools/Pool.h"

class Asteroids : public Pool
{
  public:
    const int TOTAL = 0;
    const int HEALTH_POINTS = 10;
    const float WIDTH = 1.0f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;
};