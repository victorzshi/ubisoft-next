#pragma once

#include "Scene/Pools/Pool.h"

class Stars : public Pool
{
  public:
#ifdef _DEBUG
    const int TOTAL = 1000;
#else
    const int TOTAL = 5000;
#endif

    virtual void Init(Scene &scene) override;

    virtual void Update(Scene &scene) override;
};