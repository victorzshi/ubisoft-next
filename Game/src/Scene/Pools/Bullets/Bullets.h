#pragma once

#include "Scene/Pools/Pool.h"

struct Vector3;

class Bullets : public Pool
{
  public:
    const int TOTAL = 100;
    const float WIDTH = 0.1f;
    const float DELTA_VELOCITY = 5.0f;
    const float DURATION = 1.0f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

    void CreateBullet(Scene &scene, int id);
};