#pragma once

#include "Scene/Pools/Pool.h"

struct Vector3;

class Fuel : public Pool
{
  public:
  public:
    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

  private:
    int CreateFuel(Scene &scene, Vector3 &position);
};