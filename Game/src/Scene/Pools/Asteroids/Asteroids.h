#pragma once

#include "Scene/Pools/Pool.h"

class Asteroids : public Pool
{
  public:
    const int TOTAL = 10;
    const std::string FILE = "torus.obj";

    virtual void Init(Scene &scene) override;
};