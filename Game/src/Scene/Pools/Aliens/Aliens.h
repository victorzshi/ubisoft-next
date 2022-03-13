#pragma once

#include "Scene/Pools/Pool.h"

struct Vector3;

class Aliens : public Pool
{
  public:
    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

  private:
    int CreateTurret(Scene &scene, Vector3 &position);

    int CreateBomber(Scene &scene, Vector3 &position);
};