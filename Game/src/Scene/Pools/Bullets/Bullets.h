#pragma once

#include "Scene/Pools/Pool.h"

struct Vector3;

class Bullets : public Pool
{
  public:
    const int TOTAL = 100;
    const float DELTA_VELOCITY = 3.0f;
    const float DURATION = 1.0f;

    virtual void Init(Scene &scene) override;

    void CreateBullet(Scene &scene, Vector3 &position, Vector3 &direction);
};