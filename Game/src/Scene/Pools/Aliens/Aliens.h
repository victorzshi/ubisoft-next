#pragma once

#include "Scene/Pools/Pool.h"

class Aliens : public Pool
{
  public:
    const int TOTAL = 10;
    const int HEALTH_POINTS = 10;
    const float WIDTH = 1.0f;
    const float BULLET_COOLDOWN = 0.5f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;
};