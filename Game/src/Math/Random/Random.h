#pragma once

struct Vector3;

class Random
{
  public:
    static int GetInt(int min, int max);
    static float GetFloat(float min, float max);
    static float Distance(Vector3 a, Vector3 b);
};