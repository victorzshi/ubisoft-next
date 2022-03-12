#pragma once

#include "Scene/Pools/Pool.h"

class Stars : public Pool
{
  public:
    const int TOTAL = 5000;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;
};