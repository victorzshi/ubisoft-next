#pragma once

#include "Scene/Pools/Pool.h"

class Asteroids : public Pool
{
  public:
    // const int TOTAL = 10;
    const int TOTAL = 0;
    const int HEALTH = 20;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;
};