#pragma once

#include "Scene/Pools/Pool.h"

class Asteroids : public Pool
{
  public:
    const int TOTAL = 10;
    const int HEALTH = 20;
    const float WIDTH = 1.0f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;
};