#pragma once

struct Color;
struct Face;

enum class Lights
{
    BRIGHT,
    SHADOW,
    OUTLINE,
};

class Light
{
  public:
    Light();

    Lights GetLight() const;

    void SetLight(Lights light);

    void ApplyLighting(float dot, Color &color, Face &face);

  private:
    Lights m_light;
};