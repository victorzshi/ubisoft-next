#pragma once

#include <string>

#include "Math/Vector3/Vector3.h"
#include "Scene/Pools/Pool.h"

class Grid : public Pool
{
  public:
    const int ROWS = 20;
    const int COLUMNS = 20;
    const float COLOR_COOLDOWN = 1.0f;

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;

  private:
    std::vector<Vector3> CreatePositions();
};