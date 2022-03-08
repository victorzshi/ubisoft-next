#pragma once

#include "Scene/Pools/Pool.h"

struct Vector3;

class Bullets : public Pool
{
  public:
    const int TOTAL = 100;

    virtual void Init(Scene &scene) override;

    void CreateBullet(Vector3 position);
};