#pragma once

#include "Graphics/Color/Color.h"
#include "Scene/Pools/Pool.h"

struct Vector3;

class Bullets : public Pool
{
  public:
    const int TOTAL = 100;
    const float WIDTH = 0.1f;
    const float DELTA_VELOCITY = 10.0f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

    void ShootAt(Scene &scene, Vector3 &from, Vector3 &to, Colors color);
};