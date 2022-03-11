#pragma once

struct Vector3;

class Utils
{
  public:
    static int RandomInt(int min, int max);
    static float RandomFloat(float min, float max);
    static float Distance(Vector3 from, Vector3 to);
    static float Angle(Vector3 from, Vector3 to);
};