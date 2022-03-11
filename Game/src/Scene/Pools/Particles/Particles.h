#pragma once

#include "Scene/Pools/Pool.h"

struct Vector3;

class Particles : public Pool
{
  public:
    const int TOTAL = 1000;
    const float DURATION = 0.3f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

    void CreateExplosion(Scene &scene, int id);

    void CreateBigExplosion(Scene &scene, int id);
};