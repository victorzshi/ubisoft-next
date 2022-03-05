#pragma once

#include <string>

#include "Math/Vector3/Vector3.h"
#include "Scene/Pools/Pool.h"

class Grid : public Pool
{
  public:
    const float WIDTH = 1.0f;
    const float HEIGHT = 1.0f;
    const int ROWS = 8;
    const int COLUMNS = 14;
    const std::string FILE = "cube.obj";

    virtual void Init(Scene &scene) override;

  private:
    std::vector<Vector3> CreatePositions();
};