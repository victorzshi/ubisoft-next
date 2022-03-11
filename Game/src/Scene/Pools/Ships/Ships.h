#pragma once

#include "Scene/Pools/Pool.h"

class Ships : public Pool
{
  public:
    const int TOTAL = 1;
    const float DELTA_ACCELERATION = 1.0f;
    const float BULLET_COOLDOWN = 0.05f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

    void ResetBulletCooldown(Scene& scene, int id);
};