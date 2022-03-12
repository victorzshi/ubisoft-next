#pragma once

#include "Scene/Pools/Pool.h"

#include <set>

struct Vector3;

class Planets : public Pool
{
  public:
    const int TOTAL = 5;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

  private:
    std::set<int> m_random;

    void GeneratePlanet(Scene &scene, int id, Vector3 &position);
};