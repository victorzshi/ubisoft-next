#pragma once

#include "Box/Box.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/Mesh/Mesh.h"
#include "Math/Matrix/Matrix.h"

class Scene
{
  public:
    Scene();
    ~Scene();

    void Init();

    void Update(float deltaTime);
    void Render();

  private:
    Box m_viewport;
    Camera m_camera;
    Matrix m_world;
    Matrix m_view;
    Matrix m_projection;

    Mesh m_mesh;
    std::vector<Triangle> m_triangles;

    void SetViewport();
    void SetCamera();
    void SetWorldMatrix();
    void SetViewMatrix();
    void SetProjectionMatrix();

    void HandleInput();
    void UpdateTriangles();
    void RenderTriangles();
    void RenderBorder();
    // TODO: Draw grid for visualizing 3D space.
};