#pragma once

#include "Scene/Pools/Pool.h"

class Asteroids : public Pool
{
  public:
    virtual void Init(Scene& scene) override;
};