#pragma once

#include "Scene/Pools/Pool.h"

struct Vector3;

class Particles : public Pool
{
  public:
    const int TOTAL = 1000;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

    void Ricochet(Scene &scene, int id);

    void Explode(Scene &scene, int id);

    void Boost(Scene &scene, int id, Vector3 &direction);
};