#pragma once

#include "Scene/Pools/Pool.h"

class Ships : public Pool
{
  public:
    const int TOTAL = 1;
    const std::string FILE = "sphere.obj";

    virtual void Init(Scene &scene) override;
};