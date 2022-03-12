#pragma once

#include "Scene/Pools/Pool.h"

class Planets : public Pool
{
  public:
    // TODO: Add camera clipping.
    const int TOTAL = 4;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;
};