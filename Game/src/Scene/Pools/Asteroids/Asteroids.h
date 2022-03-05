#pragma once

#include "Scene/Pools/Pool.h"

class Asteroids : public Pool
{
  public:
    const size_t total = 3;
    const std::string file = "sphere.obj";

    virtual void Init(Scene &scene) override;
};