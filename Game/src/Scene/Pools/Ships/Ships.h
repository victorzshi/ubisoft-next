#pragma once

#include "Scene/Pools/Pool.h"

class Ships : public Pool
{
  public:
    const int TOTAL = 1;
    const float DELTA_VELOCITY = 2.0f;

    virtual void Init(Scene &scene) override;

    virtual void UpdateIds(Scene &scene) override;
};