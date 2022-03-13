#pragma once

#include "Scene/Pools/Pool.h"

class Ships : public Pool
{
  public:
    const int TOTAL = 1;
    const int HEALTH = 100;
    const float WIDTH = 1.0f;
    const float DELTA_ACCELERATION = 3.0f;
    const float MAX_VELOCITY = 5.0f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;
};