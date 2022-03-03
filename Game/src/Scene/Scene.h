#pragma once

struct Box
{
    float x, y, w, h;
};

class Scene
{
  public:
    Scene();
    ~Scene();

    void SetViewport(Box viewport);

    void Render();

  private:
    Box viewport_;

    void DrawBorder();
};