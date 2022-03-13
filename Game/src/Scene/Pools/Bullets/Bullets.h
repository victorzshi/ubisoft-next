#pragma once

#include "Graphics/Color/Color.h"
#include "Scene/Pools/Pool.h"

struct Vector3;

class Bullets : public Pool
{
  public:
    const int TOTAL = 100;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

    void ShipShootAt(Scene &scene, Vector3 &from, Vector3 &to);

    void AlienShootAt(Scene &scene, Vector3 &from, Vector3 &to);
};