#pragma once

#include "Scene/Pools/Pool.h"

class Asteroids : public Pool
{
  public:
    const int total = 3;
    const std::string file = "sphere.obj";

    virtual void Init(Scene &scene) override;
};