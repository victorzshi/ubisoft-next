#pragma once

#include "Components/Mesh/Mesh.h"
#include "Components/Transform/Transform.h"
#include "Graphics/Box/Box.h"
#include "Graphics/Camera/Camera.h"
#include "Math/Matrix/Matrix.h"
#include "Pools/Asteroids/Asteroids.h"

class Scene
{
  public:
    Scene();

    void Init();
    void Shutdown();

    Mesh *GetMeshes();
    Transform *GetTransforms();

    size_t CreateEntity();

    void Update(float deltaTime);
    void Render();

  private:
    static const size_t MAX_ENTITIES = 10;
    size_t m_entity;

    // 3D graphics
    Box m_viewport;
    Camera m_camera;
    Matrix m_world;
    Matrix m_view;
    Matrix m_projection;
    std::vector<Triangle> m_triangles;

    // Component arrays
    Mesh *m_meshes;
    Transform *m_transforms;

    // Object pools
    Asteroids m_asteroids;

    // Helper functions
    void SetViewport();
    void SetCamera();
    void SetWorldMatrix();
    void SetViewMatrix();
    void SetProjectionMatrix();

    void HandleInput();
    void UpdateTriangles();
    void RenderTriangles();
    void RenderBorder();
};