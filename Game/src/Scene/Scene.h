#pragma once

#include "Graphics/Mesh/Mesh.h"
#include "Math/Matrix/Matrix.h"

struct Box
{
    float x, y, w, h;
};

struct Camera
{
    Vector3 position;
    Vector3 target;
    Vector3 up;
    float yaw;
    float pitch;
};

class Scene
{
  public:
    Scene();
    ~Scene();

    void Init(Box viewport);

    void Update(float deltaTime);
    void Render();

  private:
    Box viewport_;
    Mesh mesh_;
    Matrix projection_;
    Camera camera_;

    std::vector<Triangle> triangles_;

    void DrawBorder();
    // TODO: Draw grid for visualizing 3D space.

    void HandleInput();
};