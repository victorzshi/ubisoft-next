#pragma once

#include "Scene/Pools/Pool.h"

class Asteroids : public Pool
{
  public:
    const int total = 10;
    const std::string file = "monkey.obj";

    virtual void Init(Scene &scene) override;
};